#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream>

cv::Mat image;
cv::Mat processed_image;

void ProcessImage();
void DisplayImage();

int main(int argc, char* argv[])
{
    cv::namedWindow("Image");
    cv::namedWindow("Processed Image");

    if (argc > 1)
    {
        image = cv::imread(argv[1]);
    } else
    {
        image = cv::imread("../data/lena.jpg");
    }

    if (image.empty()) exit(1);

    ProcessImage();
    DisplayImage();
    cv::waitKey(0);

    exit(0);
}

void DisplayImage()
{
    cv::imshow("Image", image);
    cv::imshow("Processed Image", processed_image);
}

void ProcessImage()
{
    int x,y;
    cv::Vec3b pixel;
    unsigned char R,G,B;

    processed_image = image.clone();

    for (y=0; y<processed_image.rows; y++){
        for (x=0; x<processed_image.cols; x++) {
            // Get pixel
            pixel = processed_image.at<cv::Vec3b>(y,x);
            // get separate colours
            B = pixel[0];
            G = pixel[1];
            R = pixel[2];

            pixel[0] = 255 - B;
            pixel[1] = 255 - G;
            pixel[2] = 255 - R;

            // write processed pixel
            processed_image.at<cv::Vec3b>(y,x) = pixel;
        }
    }
}
