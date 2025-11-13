#ifndef EDGEDETECT_CANNY_PROCESSOR_H
#define EDGEDETECT_CANNY_PROCESSOR_H

#include <opencv2/opencv.hpp>
#include <vector>

class CannyProcessor {
public:
    CannyProcessor(double lowThreshold = 50.0, double highThreshold = 150.0, int kernelSize = 5);
    void process(const cv::Mat& input, cv::Mat& output);
    static void nv21ToRGBA(const std::vector<uint8_t>& nv21Data, int width, int height, cv::Mat& rgba);
    static void nv21ToGray(const std::vector<uint8_t>& nv21Data, int width, int height, cv::Mat& gray);

private:
    double m_lowThreshold;
    double m_highThreshold;
    int m_kernelSize;
    cv::Mat m_blurred;
    cv::Mat m_edges;
};

#endif
