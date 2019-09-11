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
        std::string Name();
    private:
        cv::Mat image_;
        std::string path_;
        std::string name_;
};
