#include <iostream>
#include <thread>

#include <Panoramic/image.h>
#include <Panoramic/processor.h>
#include <Panoramic/utils.h>

/*
* -------------- MAIN ---------------------
*/
namespace
{
char *input = "../data/";
char *output = "../export/";

} // namespace

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Default: " << std::endl;
    }
    else if (argc == 3)
    {
        input = argv[2];
    }
    else if (argc == 4)
    {
        input = argv[2];
        output = argv[3];
    }

    // Initialise image processor
    Processor proc("Processor", output);

    // Loads names of image files
    stringvec files = load_image_names(input);

    // Start image processing
    std::cout << "-------------------------------------------------------" << std::endl;
    for (size_t i = 0; i < files.size(); i++)
    {
        Image img((input + files.at(i)).c_str());
        Image processed = proc.ApplyReverse(img);
        proc.SaveImage(processed);
    }

    // Image image2(image);
    // proc.ApplyMedianBlur(image, image2, 37);

    // cv::Size ksize(11,11);
    // Image processed = proc.ApplyGaussianBlur(image, ksize);
    // proc.DisplayImages(image, image2);

    // Image image("../data/lena.jpg");
    // Processor proc("Processor", output);

    // // Loads names of image files
    // stringvec files = load_image_names(input);
    // for (auto i = 0; i < files.size(); i++)
    // {
    //     Image img((input + files.at(i)).c_str());
    //     proc.AddImage(img);
    // }

    // proc.MakePanorama(image);

    exit(0);
}
