#include <sys/types.h>
#include <dirent.h>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>

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