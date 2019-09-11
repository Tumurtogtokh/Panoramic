#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <string>
#include <iostream>

#include <Panoramic/image.h>
#include <Panoramic/processor.h>
#include <Panoramic/utils.h>

Processor::Processor(const std::string &name, const char *output_dir_path)
{
    this->process_name_ = name;
    this->images_ = std::vector<Image>();
    this->output_dir_ = get_abs_path(output_dir_path);
}

Processor::Processor(const std::string &name, const char *input_path, const char *output_dir_path)
{
    this->process_name_ = name;
    this->images_ = std::vector<Image>();
    this->output_dir_ = get_abs_path(output_dir_path);

    stringvec files;
    read_directory(input_path, files);

    for (auto f : files)
        this->images_.emplace_back(Image(f.c_str()));
}

/**
 * Return output_dir
 */
std::string Processor::OutputDir()
{
    return this->output_dir_;
}

/**
 * Add an image to Processor
 */
void Processor::AddImage(Image &img)
{
    this->images_.emplace_back(img);
}

/**
 * Reverse RGB channels of an image
 */
Image Processor::ApplyReverse(Image &img)
{
    int x, y;
    cv::Vec3b pixel;
    unsigned char R, G, B;

    cv::Mat processed_image = img.CVImage().clone();

    for (y = 0; y < processed_image.rows; y++)
    {
        for (x = 0; x < processed_image.cols; x++)
        {
            // Get pixel
            pixel = processed_image.at<cv::Vec3b>(y, x);
            // get separate colours
            B = pixel[0];
            G = pixel[1];
            R = pixel[2];

            pixel[0] = 255 - B;
            pixel[1] = 255 - G;
            pixel[2] = 255 - R;

            // write processed pixel
            processed_image.at<cv::Vec3b>(y, x) = pixel;
        }
    }

    return Image(img.Path(), processed_image);
}

/**
 * Save an image to output dir
 */
void Processor::SaveImage(Image &img)
{
    cv::imwrite(this->output_dir_ + img.Name(), img.CVImage());
}

void Processor::DisplayImages(Image &orig, Image &proccessed)
{
    cv::namedWindow("Image");
    cv::namedWindow("Processed Image");
    cv::imshow("Image", orig.CVImage());
    cv::imshow("Processed Image", proccessed.CVImage());
    cv::waitKey(0);
}
