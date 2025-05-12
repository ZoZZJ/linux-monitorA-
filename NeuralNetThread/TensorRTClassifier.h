#ifndef TENSORRTCLASSIFIER_H
#define TENSORRTCLASSIFIER_H
#include <QImage>
#include <QPixmap>
#include <NvInfer.h>
#include <cuda_runtime_api.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

// 创建 TensorRT 的 Logger
class Logger : public nvinfer1::ILogger {
public:
    void log(Severity severity, const char* msg) noexcept override {
        // 只打印警告及以上级别的日志
        if (severity != Severity::kINFO)
            std::cout << "[TensorRT] " << msg << std::endl;
    }
};

// 声明全局 Logger
extern Logger gLogger;

class TensorRTClassifier {
public:
    explicit TensorRTClassifier(const std::string &enginePath);
    ~TensorRTClassifier();

    std::pair<int, float> predict(const cv::Mat &image);   // 输入 OpenCV Mat
    std::pair<int, float> predict(const QImage &image);    // 输入 QImage
    std::pair<int, float> predict(const QPixmap &pixmap);  // 输入 QPixmap

    void testImage(const std::string &imagePath = "/home/jetson/Monitor-Linux-monitor0306/VisionDataset/Right/133.png");  // ➕ 测试函数

private:
    void preprocessImage(const cv::Mat &image, float *gpuInputBuffer);
    void infer();

    nvinfer1::ICudaEngine *engine;
    nvinfer1::IExecutionContext *context;
    void *buffers[2];  // 输入 + 输出缓冲区
    cudaStream_t stream;

    int input_width;
    int input_height;
    int num_classes;
};



#endif // TENSORRTCLASSIFIER_H
