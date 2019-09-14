#pragma once

#include <sys/types.h>
#include <dirent.h>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <stdlib.h>

namespace
{
typedef std::vector<std::string> stringvec;

/**
 * Retrieve names of content in directory
 * 
*/
void read_files_names(const std::string &name, stringvec &v)
{
    DIR *dirp = opendir(name.c_str());
    struct dirent *dp;
    while ((dp = readdir(dirp)) != NULL)
    {
        if (std::string(dp->d_name).length() > 2)
        {
            v.push_back(dp->d_name);
        }
    }
    closedir(dirp);
}

/**
 * Retrieve dir names in directory
 * 
*/
void read_directory(const char* &name, stringvec &v)
{
    DIR *dirp = opendir(name);
    struct dirent *dp;
    std::string::size_type file_ext_idx;

    while ((dp = readdir(dirp)) != NULL)
    {   
        file_ext_idx = std::string(dp->d_name).rfind('.');
        if (file_ext_idx == std::string::npos)
        {
            v.push_back(dp->d_name);
        }
    }
    closedir(dirp);
}

std::string get_absolute_path(const char *path)
{
    char resolved_path[PATH_MAX];
    realpath(path, resolved_path);

    return std::string(resolved_path);
}

stringvec load_image_names(const char* input)
{
    stringvec files;
    read_files_names(input, files);
    return files;
}
} // namespace