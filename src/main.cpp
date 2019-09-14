#include <iostream>
#include <thread>
#include <typeinfo>

#include <Panoramic/image.h>
#include <Panoramic/processor.h>
#include <Panoramic/utils.h>

/*
* -------------- MAIN ---------------------
*/
namespace
{
char *input = "../data/stitch/";
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
    Processor proc("Test Panorama", output);
    std::cout << "-------------------------------------------------------" << std::endl;

    // Reading directories from input dir
    const char *input_dir = "../data/Stitch_examples/";
    stringvec directories;
    read_directory(input_dir, directories);

    std::cout << "Directories inside " << input_dir << " : " << std::endl;
    for (auto d : directories)
        std::cout << d << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    // Start image processing
    std::cout << "-------------------------------------------------------" << std::endl;
    std::string curr_input;

    for (auto dir : directories)
    {
        // Loads names of image files
        curr_input = get_absolute_path(std::string(input_dir + dir).c_str());
        std::cout << "Curr dir: " << curr_input << std::endl;
        stringvec files = load_image_names(curr_input.c_str());

        // Adding images to Processor
        for (size_t i = 0; i < files.size(); i++)
        {
            std::cout << "input image: " << curr_input + files.at(i) << std::endl;
            Image img((curr_input + "/" + files.at(i)).c_str());
            proc.AddImage(img);
        }
        // Making Panorama
        proc.MakePanorama(dir + ".jpg");
        proc.ClearImages();
    }

    // Making Panorama
    // std::cout << "Image Processor: " << proc.Name() << std::endl;
    // proc.MakePanorama("test_pano.jpg");

    // Loading image names from each directory and printing it
    // stringvec img_names;
    // for (auto dir : dirs)
    // {
    //     std::cout << "Reading from: " << get_absolute_path(std::string(input_dir + dir).c_str()) << std::endl;
    //     read_files_names(std::string(input_dir + dir).c_str(), img_names);

    //     for (auto i : img_names)
    //         std::cout << i << std::endl;

    //     std::cout << "-------------------------------------------------------" << std::endl;
    //     img_names.clear();
    // }

    // Image image2(image);
    // proc.ApplyMedianBlur(image, image2, 37);

    // cv::Size ksize(11,11);
    // Image processed = proc.ApplyGaussianBlur(image, ksize);
    // proc.DisplayImages(image, image2);

    exit(0);
}
