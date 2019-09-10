#pragma once
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <string>

class Image{
    public:
        Image(const char* path);
        Image(const char* path, cv::Mat& img);
        cv::Mat CVImage();
        const char* Path();
    private:
        cv::Mat image;
        std::string path;
};
