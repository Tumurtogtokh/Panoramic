#pragma once

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <string>
#include <Panoramic/image.h>

class Processor
{
public:
    Processor(const std::string &name, const char *output_dir_path);
    Processor(const std::string &name, const char *input_path, const char *output_dir_path);
    std::string OutputDir();
    void AddImage(Image &);
    Image ApplyReverse(Image &);
    Image ApplyGaussianBlur(Image &, cv::Size);
    void MakePanorama(Image&);
    void ApplyMedianBlur(Image &, Image &, int);
    void DisplayImages(Image &orig, Image &proccessed);
    void SaveImage(Image &);

private:
    std::vector<Image> images_;
    std::string process_name_;
    std::string output_dir_;
    std::string input_dir_;
};
