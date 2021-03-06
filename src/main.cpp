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
const char *input = "../data/Stitch_examples/";
const char *output = "../export/";
} // namespace

int main(int argc, char *argv[])
{
    if (argc == 2)
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
    if (!Utils::dir_exists(output))
    {
        const int dir_err = mkdir(output, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (-1 == dir_err)
        {
            std::cout << "Error creating output directory at: " << output << std::endl;
            exit(1);
        }
    }

    // Reading directories from input dir
    const char *input_dir = input;
    Utils::stringvec directories;
    Utils::read_directory(input_dir, directories);

    std::cout << "Directories inside " << input_dir << " : " << std::endl;
    for (auto d : directories)
        std::cout << d << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    // Checking available cores
    unsigned int nCores = std::thread::hardware_concurrency();
    std::cout << "This machine supports concurrency with " << nCores << " cores available" << std::endl;

    // Start image processing
    std::string curr_input;
    std::thread runners[directories.size()];

    for (size_t i = 0; i < directories.size(); i++)
    {
        // Loads names of image files
        curr_input = Utils::get_absolute_path(std::string(input_dir + directories.at(i)).c_str());
        std::cout << "\nCurr dir: " << curr_input << std::endl;
        Utils::stringvec files = Utils::load_image_names(curr_input.c_str());
        std::string dir = directories.at(i);

        // starting a thread with lambda
        auto run_processor = [dir, curr_input, files]() {
            // Initialise image processor
            auto thread_id = std::this_thread::get_id();
            std::stringstream ss;
            ss << thread_id;
            Processor proc("Img Processor thread - " + ss.str(), output);
            std::cout << proc.Name() << std::endl;

            // Adding images to Processor
            for (size_t i = 0; i < files.size(); i++)
            {
                Image img((curr_input + "/" + files.at(i)).c_str());
                proc.AddImage(img);
            }

            // Making Panorama
            proc.MakePanorama(dir + ".jpg");
        };

        runners[i] = std::thread(run_processor);
    }

    //Join the threads with the main thread
    for (size_t i = 0; i < directories.size(); ++i)
    {
        runners[i].join();
    }

    exit(0);
}
