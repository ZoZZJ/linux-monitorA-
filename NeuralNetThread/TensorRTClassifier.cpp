#include "TensorRTClassifier.h"
#include <NvInferRuntime.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <algorithm> // std::max_element

// 定义全局 Logger
Logger gLogger;

TensorRTClassifier::TensorRTClassifier(const std::string &enginePath) {
    // 加载 TensorRT 引擎
    std::ifstream file(enginePath, std::ios::binary);
    if (!file.good()) {
        throw std::runtime_error("无法打开 TensorRT 引擎文件");
    }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> engineData(size);
    file.read(engineData.data(), size);
    file.close();

    // 创建 TensorRT 运行时
    nvinfer1::IRuntime *runtime = nvinfer1::createInferRuntime(gLogger);
    engine = runtime->deserializeCudaEngine(engineData.data(), size, nullptr);
    context = engine->createExecutionContext();

    auto inputDims = engine->getBindingDimensions(0);
    auto outputDims = engine->getBindingDimensions(1);

    // 输入维度是 [N, C, H, W]
    if (inputDims.nbDims == 4) {
        input_height = inputDims.d[2];
        input_width = inputDims.d[3];
    } else {
        throw std::runtime_error("❌ 输入维度格式不符合 NCHW");
    }

    num_classes = outputDims.d[1];

    std::cout << "�� 输入维度 (" << inputDims.nbDims << "D): ";
    for (int i = 0; i < inputDims.nbDims; ++i) {
        std::cout << inputDims.d[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "�� 输出维度 (" << outputDims.nbDims << "D): ";
    for (int i = 0; i < outputDims.nbDims; ++i) {
        std::cout << outputDims.d[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "✅ Input size: " << input_width << "x" << input_height << std::endl;
    std::cout << "✅ Number of classes: " << num_classes << std::endl;


    // 分配 GPU 内存 3通道是如果按 3 * H * W 分配的
    cudaMalloc(&buffers[0], input_width * input_height * sizeof(float));  // 输入
    cudaMalloc(&buffers[1], num_classes * sizeof(float));  // 输出
    cudaStreamCreate(&stream);
}

TensorRTClassifier::~TensorRTClassifier() {
    cudaFree(buffers[0]);
    cudaFree(buffers[1]);
    cudaStreamDestroy(stream);
    context->destroy();
    engine->destroy();
}



void TensorRTClassifier::preprocessImage(const cv::Mat &image, float *gpuInputBuffer) {
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    // 裁剪上下各 5%
    int cropHeight = static_cast<int>(gray.rows * 0.05);
    cv::Rect roi(0, cropHeight, gray.cols, gray.rows - 2 * cropHeight);
    cv::Mat cropped = gray(roi);

    cv::Mat resized;
    cv::resize(cropped, resized, cv::Size(input_width, input_height));

    cv::Mat floatImg;
    resized.convertTo(floatImg, CV_32FC1, 1.0 / 255.0);

    const float mean = 0.602348f;
    const float std = 0.296226f;
    floatImg = (floatImg - mean) / std;

    // 确保内存连续
    if (!floatImg.isContinuous()) {
        floatImg = floatImg.clone();
    }

    // 复制到 GPU
    cudaMemcpy(gpuInputBuffer, floatImg.data, input_width * input_height * sizeof(float), cudaMemcpyHostToDevice);
}



std::pair<int, float> TensorRTClassifier::predict(const cv::Mat &image) {
    preprocessImage(image, (float *)buffers[0]);

    // 推理
    context->enqueueV2(buffers, stream, nullptr);
    cudaStreamSynchronize(stream);

    // 获取输出结果
    std::vector<float> output(num_classes);
    cudaMemcpy(output.data(), buffers[1], num_classes * sizeof(float), cudaMemcpyDeviceToHost);

    // ✅ 添加 softmax
    float maxLogit = *std::max_element(output.begin(), output.end());
    float sumExp = 0.0f;
    for (auto &val : output) {
        val = std::exp(val - maxLogit);  // 避免exp爆炸
        sumExp += val;
    }
    for (auto &val : output) {
        val /= sumExp;
    }

    // 找到最大概率的类别和对应置信度
    auto maxIt = std::max_element(output.begin(), output.end());
    int classId = std::distance(output.begin(), maxIt);
    float confidence = *maxIt;

    return {classId, confidence};
}


std::pair<int, float> TensorRTClassifier::predict(const QImage &image) {
    // 转换 QImage 到 cv::Mat
    cv::Mat mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void *)image.bits(), image.bytesPerLine()).clone();
    cv::cvtColor(mat, mat, cv::COLOR_RGB2BGR);

    return predict(mat);
}

std::pair<int, float> TensorRTClassifier::predict(const QPixmap &pixmap) {
    return predict(pixmap.toImage());
}


void TensorRTClassifier::testImage(const std::string &imagePath) {
    cv::Mat image = cv::imread(imagePath);
    if (image.empty()) {
        std::cerr << "❌ 无法读取图片：" << imagePath << std::endl;
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();
    auto [classIndex, confidence] = predict(image);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;

    std::cout << "✅ 图片: " << imagePath
              << " | 分类结果: " << classIndex
              << " | 置信度: " << confidence
              << " | 推理时间: " << duration.count() << " 秒" << std::endl;
}

