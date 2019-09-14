#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <stdlib.h>

namespace Utils
{
typedef std::vector<std::string> stringvec;

/**
 * Retrieve names of content in directory
 * 
*/
void read_files_names(const std::string &name, stringvec &v);

/**
 * Retrieve dir names in directory
 * 
*/
void read_directory(const char *&name, stringvec &v);

std::string get_absolute_path(const char *path);

stringvec load_image_names(const char *input);

int dir_exists(const char *path);

} // namespace