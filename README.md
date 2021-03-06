# Panoramic
Creates Panoramic picture from raw photos using OpenCV.

## Dependencies for Running Locally
* cmake >= 3.0
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 7.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* OpenCV >= 4.1
  * Installation instructions are there [OpenCV](hhttps://opencv.org/)

## Basic Build Instructions
1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `../bin/panoramic`.

## Class structures
All header files are in include directory. Implementations of those are in src directory. Include directory also has util header which has a few file I/O functions. 
* Image
  * image_ holds opencv mat
  * path_ is a path to an image
  * name_ is a name of the image
* Processor
  * process_name_ is a name of the image processor. It is not really important as it is only used for logging.
  * images_ is a vector of Image.
  * output_dir_ is a path to export directory.
  * input_dir_ is a path to load images to the image processor.
* Util.h
  * get_abs_path converts a relative path to an absolute path
  * read_directory is a function to read and saves names of images.
  * load_image_names uses read_directory to create a vector of image names.
  * dir_exists checks if a directory exists
