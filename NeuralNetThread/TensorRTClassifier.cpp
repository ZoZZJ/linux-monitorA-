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


    // 获取输入输出形状
    auto inputDims = engine->getBindingDimensions(0);
    auto outputDims = engine->getBindingDimensions(1);

    input_height = inputDims.d[1];
    input_width = inputDims.d[2];
    num_classes = outputDims.d[1];  // 获取分类数量

    std::cout << "Input size: " << input_width << "x" << input_height << std::endl;
    std::cout << "Number of classes: " << num_classes << std::endl;

    // 分配 GPU 内存
    cudaMalloc(&buffers[0], 3 * input_width * input_height * sizeof(float));  // 输入
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
    cv::Mat resized;
    cv::resize(image, resized, cv::Size(input_width, input_height));

    cv::Mat floatImg;
    resized.convertTo(floatImg, CV_32FC3, 1.0 / 255.0);

    cudaMemcpy(gpuInputBuffer, floatImg.data, 3 * input_width * input_height * sizeof(float), cudaMemcpyHostToDevice);
}

int TensorRTClassifier::predict(const cv::Mat &image) {
    preprocessImage(image, (float *)buffers[0]);

    // 推理
    context->enqueueV2(buffers, stream, nullptr);
    cudaStreamSynchronize(stream);

    // 获取输出结果
    std::vector<float> output(num_classes);
    cudaMemcpy(output.data(), buffers[1], num_classes * sizeof(float), cudaMemcpyDeviceToHost);

    // 找到最大概率的类别
    return std::distance(output.begin(), std::max_element(output.begin(), output.end()));
}

int TensorRTClassifier::predict(const QImage &image) {
    // 转换 QImage 到 cv::Mat
    cv::Mat mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void *)image.bits(), image.bytesPerLine()).clone();
    cv::cvtColor(mat, mat, cv::COLOR_RGB2BGR);

    return predict(mat);
}

int TensorRTClassifier::predict(const QPixmap &pixmap) {
    return predict(pixmap.toImage());
}


void TensorRTClassifier::testImage(const std::string &imagePath) {
    cv::Mat image = cv::imread(imagePath);
    if (image.empty()) {
        std::cerr << "❌ 无法读取图片：" << imagePath << std::endl;
        return;
    }

    // ⏳ 计算推理时间
    auto start = std::chrono::high_resolution_clock::now();
    int classIndex = predict(image);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;

    std::cout << "✅ 图片: " << imagePath
              << " | 分类结果: " << classIndex
              << " | 推理时间: " << duration.count() << " 秒" << std::endl;
}
