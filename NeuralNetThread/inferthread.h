#ifndef INFERTHREAD_H
#define INFERTHREAD_H
/*//神经网络开始推理的线程
#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <opencv2/opencv.hpp>
//#include "NvInfer.h" // TensorRT library
//#include <cuda_runtime_api.h>

class InferThread : public QThread
{
    Q_OBJECT
public:
    explicit InferThread(QObject *parent = nullptr);
    ~InferThread();
    void stop();
    bool loadEngine(const std::string &engineFilePath);

signals:
    void inferenceDone(const cv::Mat &outputImage);

public slots:
    void receiveFrame(const cv::Mat &frame);

protected:
    void run() override;

private:
    cv::Mat frame_;
    bool running_;
    QMutex mutex_;
    QWaitCondition condition_;

    // TensorRT related members
    nvinfer1::IRuntime* runtime_;
    nvinfer1::ICudaEngine* engine_;
    nvinfer1::IExecutionContext* context_;
    cudaStream_t stream_;

    bool loadEngineFromFile(const std::string &engineFilePath);
    void infer(const cv::Mat &inputFrame, cv::Mat &outputFrame);
};
*/

#endif // INFERTHREAD_H
