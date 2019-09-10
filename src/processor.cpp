#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <string>
#include <image.h>
#include <processor.h>

Processor::Processor(const std::string &name)
{
    this->process_name = name;
    this->images = std::vector<Image>();
}

void Processor::AddImage(Image &img)
{
    this->images.emplace_back(img);
}

Image Processor::ApplyReverse(Image& img)
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

void Processor::DisplayImages(Image& orig, Image& proccessed)
{
    cv::namedWindow("Image");
    cv::namedWindow("Processed Image");
    cv::imshow("Image", orig.CVImage());
    cv::imshow("Processed Image", proccessed.CVImage());
    cv::waitKey(0);
}
