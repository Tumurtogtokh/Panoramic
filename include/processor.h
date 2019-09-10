#pragma once

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <string>
#include <image.h>

class Processor
{
public:
    Processor(const std::string &);
    void AddImage(Image&);
    Image ApplyReverse(Image&);
    void DisplayImages(Image& orig, Image& proccessed);

private:
    std::vector<Image> images;
    std::string process_name;
};
