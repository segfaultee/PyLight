#pragma once

#include <string>

#include "module/module.hh"
#include "result.hh"

namespace python
{
    bool init();
    void deinit();

    Result<void*> insert_path(std::string path);
}