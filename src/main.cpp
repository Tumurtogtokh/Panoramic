#include <iostream>
#include <thread>
#include <sys/stat.h>

#include <Panoramic/image.h>
#include <Panoramic/processor.h>
#include <Panoramic/utils.h>

/*
* -------------- MAIN ---------------------
*/
namespace
{
char *input;
char *output = "../export/";
} // namespace

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        input = "../data/Stitch_examples/";
    }
    else if (argc == 2)
    {
        input = argv[1];
    }
    else if (argc == 3)
    {
        input = argv[1];
        output = argv[2];
    }
    std::cout << "\nInput dir: " << input << "  "
              << "Output dir: " << output << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    // Making export directory
    const int dir_err = mkdir(output, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if (-1 == dir_err)
    {
        std::cout << "Error creating output directory!\n" << std::endl;
        exit(1);
    }

    // Reading directories from input dir
    const char *input_dir = input;
    stringvec directories;
    read_directory(input_dir, directories);

    std::cout << "Directories inside " << input_dir << " : " << std::endl;
    for (auto d : directories)
        std::cout << d << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    // Start image processing
    std::string curr_input;
    unsigned int nCores = std::thread::hardware_concurrency();
    std::cout << "This machine supports concurrency with " << nCores << " cores available" << std::endl;

    for (auto dir : directories)
    {
        // Loads names of image files
        curr_input = get_absolute_path(std::string(input_dir + dir).c_str());
        std::cout << "\nCurr dir: " << curr_input << std::endl;
        stringvec files = load_image_names(curr_input.c_str());

        // Initialise image processor
        auto thread_id = std::this_thread::get_id();
        std::stringstream ss;
        ss << thread_id;

        Processor proc("Img Processor thread - " + ss.str(), output);

        // Adding images to Processor
        for (size_t i = 0; i < files.size(); i++)
        {
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
