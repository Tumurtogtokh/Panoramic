#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <stdlib.h>
#include <Panoramic/utils.h>

/**
 * Retrieve names of content in directory
 * 
*/
void Utils::read_files_names(const std::string &name, stringvec &v)
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
void Utils::read_directory(const char *&name, stringvec &v)
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

std::string Utils::get_absolute_path(const char *path)
{
    char resolved_path[PATH_MAX];
    realpath(path, resolved_path);

    return std::string(resolved_path);
}

Utils::stringvec Utils::load_image_names(const char *input)
{
    stringvec files;
    read_files_names(input, files);
    return files;
}

int Utils::dir_exists(const char *path)
{
    struct stat info;

    if (stat(path, &info) != 0)
        return 0;
    else if (info.st_mode & S_IFDIR)
        return 1;
    else
        return 0;
}
