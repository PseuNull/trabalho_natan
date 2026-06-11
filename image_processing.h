#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <opencv2/opencv.hpp>
#include <string>

class ImageProcessor {
public:
    cv::Mat removeNoise(const cv::Mat& image);
    cv::Mat enhanceContrast(const cv::Mat& image);
    cv::Mat sharpenImage(const cv::Mat& image);
    cv::Mat scanDocument(const cv::Mat& image);

    bool processImage(const std::string& inputPath,
                      const std::string& outputPath);
};

#endif
