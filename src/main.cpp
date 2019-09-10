#include <iostream>

#include <processor.h>
#include <image.h>

#include "util.cpp"

/*
* -------------- MAIN ---------------------
*/
int main(int argc, char *argv[])
{

    Image image("../data/");
    Processor proc("Processor");

    std::cout << "Image: " << image.Path() << std::endl;

    stringvec files;
    read_directory("../data/", files);
    
    for (auto f : files)
        std::cout << f << std::endl;

    // proc.AddImage(image);
    // Image processed = proc.ApplyReverse(image);
    // proc.DisplayImages(image, processed);

    exit(0);
}


