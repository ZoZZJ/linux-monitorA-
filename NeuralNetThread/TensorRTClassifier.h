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

    int predict(const cv::Mat &image);   // 输入 OpenCV Mat
    int predict(const QImage &image);    // 输入 QImage
    int predict(const QPixmap &pixmap);  // 输入 QPixmap

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
