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
    void LoadImages(const char *input_path);
    std::string Name();
    Image ApplyReverse(Image &);
    Image ApplyGaussianBlur(Image &, cv::Size);
    void MakePanorama(std::string);
    void ApplyMedianBlur(Image &, Image &, int);
    void DisplayImages(Image &orig, Image &proccessed);
    void SaveImage(Image &);
    void ClearImages();

private:
    std::vector<Image> images_;
    std::string process_name_;
    char* output_dir_;
    char* input_dir_;
};
