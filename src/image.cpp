#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <string>
#include <iostream>

#include <Panoramic/image.h>
#include <Panoramic/utils.h>

Image::Image(const char *path)
{
    this->path_ = get_abs_path(path);
    this->image_ = cv::imread(path);
    auto const pos = std::string(path).find_last_of("/");
    this->name_ = std::string(path).substr(pos);
}

Image::Image(const char *path, cv::Mat &img)
{
    this->path_ = get_abs_path(path);
    this->image_ = img;
    auto const pos = std::string(path).find_last_of("/");
    this->name_ = std::string(path).substr(pos);
}

/**
 * Return CV Matrix of Image object
 */
cv::Mat Image::CVImage()
{
    return this->image_;
}

/**
 * Return path of the Image
 */
const char *Image::Path()
{
    return this->path_.c_str();
}

/**
 * Return name of the Image
 */
std::string Image::Name()
{
    return this->name_;
}