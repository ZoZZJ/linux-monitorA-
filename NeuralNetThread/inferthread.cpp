#include "inferthread.h"
#include <iostream>
#include <fstream>

// TensorRT related includes
//#include "NvInfer.h"
//#include "NvOnnxParser.h"
/*InferThread::InferThread(QObject *parent) : QThread(parent), running_(false), runtime_(nullptr), engine_(nullptr), context_(nullptr), stream_(nullptr)
{
}

InferThread::~InferThread()
{
    stop();

    /*if (context_)
        context_->destroy();
    if (engine_)
        engine_->destroy();
    if (runtime_)
        runtime_->destroy();
    if (stream_)
        cudaStreamDestroy(stream_);
}

bool InferThread::loadEngine(const std::string &engineFilePath)
{
    return loadEngineFromFile(engineFilePath);
}

bool InferThread::loadEngineFromFile(const std::string &engineFilePath)
{
    std::ifstream engineFile(engineFilePath, std::ios::binary);
    if (!engineFile)
    {
        std::cerr << "Failed to open engine file: " << engineFilePath << std::endl;
        return false;
    }

    // Load the engine file into memory
    engineFile.seekg(0, engineFile.end);
    size_t fileSize = engineFile.tellg();
    engineFile.seekg(0, engineFile.beg);
    std::vector<char> engineData(fileSize);
    engineFile.read(engineData.data(), fileSize);

    // Create the TensorRT engine
    runtime_ = nvinfer1::createInferRuntime(gLogger);
    if (!runtime_)
    {
        std::cerr << "Failed to create TensorRT runtime." << std::endl;
        return false;
    }

    engine_ = runtime_->deserializeCudaEngine(engineData.data(), fileSize, nullptr);
    if (!engine_)
    {
        std::cerr << "Failed to create TensorRT engine." << std::endl;
        return false;
    }

    context_ = engine_->createExecutionContext();
    if (!context_)
    {
        std::cerr << "Failed to create TensorRT execution context." << std::endl;
        return false;
    }

    cudaStreamCreate(&stream_);

    return true;
}

void InferThread::receiveFrame(const cv::Mat &frame)
{
    QMutexLocker locker(&mutex_);
    frame_ = frame.clone();
    condition_.wakeOne();
}

void InferThread::run()
{
    running_ = true;
    while (running_)
    {
        QMutexLocker locker(&mutex_);
        if (frame_.empty())
        {
            condition_.wait(&mutex_);
        }

        cv::Mat outputFrame;
        infer(frame_, outputFrame);

        emit inferenceDone(outputFrame);
    }
}

void InferThread::infer(const cv::Mat &inputFrame, cv::Mat &outputFrame)
{
    // 1. 将输入帧从 CPU 转换为 GPU 上的张量
    // 假设 engine 和 context 是你在 InferThread 类中初始化的 TensorRT 引擎和上下文

    // 将输入图像转换为浮点型并调整大小（假设 TensorRT 模型要求 640x640 输入）
    /*cv::Mat resizedFrame;
    cv::resize(inputFrame, resizedFrame, cv::Size(640, 640));
    resizedFrame.convertTo(resizedFrame, CV_32FC3, 1.0 / 255.0);  // 归一化

    // 分配 GPU 上的输入/输出缓冲区
    float* gpuInput;
    float* gpuOutput;
    cudaMalloc(&gpuInput, sizeof(float) * 3 * 640 * 640);  // 假设输入尺寸为 3x640x640
    cudaMalloc(&gpuOutput, sizeof(float) * OUTPUT_SIZE);  // 具体的输出大小根据模型决定

    // 将输入帧从 CPU 复制到 GPU
    cudaMemcpy(gpuInput, resizedFrame.ptr<float>(), sizeof(float) * 3 * 640 * 640, cudaMemcpyHostToDevice);

    // 2. 执行 TensorRT 推理
    // 设置输入/输出缓冲区
    void* buffers[] = { gpuInput, gpuOutput };

    // 开始计时
    auto start = std::chrono::high_resolution_clock::now();

    // 推理执行 (假设 context 是已经配置好的 TensorRT 执行上下文)
    context->enqueueV2(buffers, 0, nullptr);  // 执行异步推理

    // 结束计时
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;
    std::cout << "Inference Time: " << duration.count() * 1000 << " ms" << std::endl;

    // 3. 将推理结果从 GPU 复制回 CPU
    float outputData[OUTPUT_SIZE];  // 根据模型输出大小调整
    cudaMemcpy(outputData, gpuOutput, sizeof(float) * OUTPUT_SIZE, cudaMemcpyDeviceToHost);

    // 4. 处理输出（这里假设输出为边界框等信息）
    // 假设 outputData 包含检测的框等信息，进行后处理
    // 将结果绘制到 outputFrame 上
    outputFrame = inputFrame.clone();  // 复制原始输入图像用于显示结果
    for (int i = 0; i < numDetections; ++i) {
        // 解析并绘制检测框
        int x1 = static_cast<int>(outputData[i * 6 + 0] * inputFrame.cols);
        int y1 = static_cast<int>(outputData[i * 6 + 1] * inputFrame.rows);
        int x2 = static_cast<int>(outputData[i * 6 + 2] * inputFrame.cols);
        int y2 = static_cast<int>(outputData[i * 6 + 3] * inputFrame.rows);
        cv::rectangle(outputFrame, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 255, 0), 2);
    }

    // 5. 释放 GPU 缓冲区
    cudaFree(gpuInput);
    cudaFree(gpuOutput);
}

void InferThread::stop()
{
    QMutexLocker locker(&mutex_);
    running_ = false;
    condition_.wakeOne();
}
*/
