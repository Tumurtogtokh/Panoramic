#include <vector>
#include <string>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/stitching.hpp>

#include <Panoramic/image.h>
#include <Panoramic/processor.h>
#include <Panoramic/utils.h>

Processor::Processor(const std::string &name, const char *output_dir_path)
{
    this->process_name_ = name;
    this->images_ = std::vector<Image>();
    this->output_dir_ = get_absolute_path(output_dir_path);
    this->input_dir_ = "";
}
// Processor(const std::string &name, const char *input_path, const char *output_dir_path);
Processor::Processor(const std::string &name, const char *input_path, const char *output_dir_path)
{
    this->process_name_ = name;
    this->images_ = std::vector<Image>();
    this->output_dir_ = get_absolute_path(output_dir_path);
    this->input_dir_ = get_absolute_path(input_path);

    stringvec files;
    read_files_names(input_dir_, files);

    for (auto f : files)
    {
        // this->images_.emplace_back(Image(f.c_str()));
        std::cout << "Proc In path: " << f << std::endl;
    }

    // stringvec files = load_image_names(input);

    // // Adding images to Processor
    // for (size_t i = 0; i < files.size(); i++)
    // {
    //     Image img((input + files.at(i)).c_str());
    //     proc.AddImage(img);
    // }
}

void Processor::ClearImages()
{
    this->images_.clear();
}

/**
 * Return output_dir
 */
std::string Processor::OutputDir()
{
    return this->output_dir_;
}

std::string Processor::Name()
{
    return this->process_name_;
}

/**
 * Add an image to Processor
 */
void Processor::AddImage(Image &img)
{
    this->images_.emplace_back(img);
}

void Processor::LoadImages(const char *input)
{

    // Loads names of image files
    stringvec files = load_image_names(input);

    // Adding images to Processor
    for (size_t i = 0; i < files.size(); i++)
    {
        Image img((input + files.at(i)).c_str());
        this->AddImage(img);
    }
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

Image Processor::ApplyGaussianBlur(Image &img, cv::Size ksize)
{
    cv::Mat blurred_image;
    cv::GaussianBlur(img.CVImage(), blurred_image, ksize, 0, 0, cv::BORDER_DEFAULT);
    return Image(img.Path(), blurred_image);
}

void Processor::ApplyMedianBlur(Image &src, Image &dest, int ksize)
{
    cv::medianBlur(src.CVImage(), dest.CVImage(), ksize);
}

void Processor::MakePanorama(std::string pano_name)
{
    std::vector<cv::Mat> raw_imgs;
    for (auto image : this->images_)
    {
        raw_imgs.emplace_back(image.CVImage());
    }

    std::cout << "[LOG] Making Panorama by : " << this->Name() << std::endl;

    cv::Mat pano;
    // bool try_use_gpu = false;
    // bool divide_images = false;
    cv::Stitcher::Mode mode = cv::Stitcher::PANORAMA;

    cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(mode);
    cv::Stitcher::Status status = stitcher->stitch(raw_imgs, pano);
    if (status != cv::Stitcher::OK)
    {
        std::cout << "Can't stitch images, error code = " << int(status) << std::endl;
    }
    else
    {
        std::cout << "[LOG] Stitching completed successfully" << std::endl;
        cv::imwrite(this->OutputDir() + "/" + pano_name, pano);
        std::cout << "[LOG] Panomara is saved to: " << this->OutputDir() + "/" + pano_name << std::endl;
    }
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
