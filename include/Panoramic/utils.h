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

void read_directory(const std::string &name, stringvec &v)
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

std::string get_absolute_path(const char *path)
{
    char resolved_path[PATH_MAX];
    realpath(path, resolved_path);

    return std::string(resolved_path);
}

stringvec load_image_names(const char* input)
{
    stringvec files;
    read_directory(input, files);
    return files;
}
} // namespace