#include "canny_processor.h"
#include <android/log.h>

#define TAG "CannyProcessor"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)

CannyProcessor::CannyProcessor(double lowThreshold, double highThreshold, int kernelSize)
    : m_lowThreshold(lowThreshold), m_highThreshold(highThreshold), m_kernelSize(kernelSize) {
    LOGD("CannyProcessor initialized");
}

void CannyProcessor::process(const cv::Mat& input, cv::Mat& output) {
    try {
        cv::GaussianBlur(input, m_blurred, cv::Size(m_kernelSize, m_kernelSize), 0);
        cv::Canny(m_blurred, m_edges, m_lowThreshold, m_highThreshold);
        cv::cvtColor(m_edges, output, cv::COLOR_GRAY2RGBA);
    } catch (const cv::Exception& e) {
        LOGD("OpenCV error: %s", e.what());
    }
}

void CannyProcessor::nv21ToRGBA(const std::vector<uint8_t>& nv21Data, 
                                int width, int height, cv::Mat& rgba) {
    try {
        cv::Mat nv21(height + height / 2, width, CV_8UC1, (void*)nv21Data.data());
        cv::cvtColor(nv21, rgba, cv::COLOR_YUV2RGBA_NV21);
    } catch (const cv::Exception& e) {
        LOGD("Error: %s", e.what());
    }
}

void CannyProcessor::nv21ToGray(const std::vector<uint8_t>& nv21Data, 
                                int width, int height, cv::Mat& gray) {
    try {
        gray = cv::Mat(height, width, CV_8UC1, (void*)nv21Data.data()).clone();
    } catch (const cv::Exception& e) {
        LOGD("Error: %s", e.what());
    }
}
