#pragma once

#include <string>
#include <filesystem>
#include <algorithm>


namespace python
{
    inline std::string path_to_dotted(std::string path)
    {
        std::replace(path.begin(), path.end(), '\\', '.');
        if (path.ends_with(".py"))
            path = path.substr(0, path.size() - 3);
        return path;
    }
}