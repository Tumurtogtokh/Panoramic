#include <image.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <linux/limits.h>

Image::Image(const char *path)
{
    char resolved_path[PATH_MAX];
    realpath(path, resolved_path);

    this->path = std::string(resolved_path);
    this->image = cv::imread(path);
}

Image::Image(const char *path, cv::Mat &img)
{
    char resolved_path[PATH_MAX];
    realpath(path, resolved_path);
    
    this->path = std::string(resolved_path);
    this->image = img;
}

cv::Mat Image::CVImage()
{
    return this->image;
}

const char *Image::Path()
{
    return this->path.c_str();
}