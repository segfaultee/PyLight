#pragma once

#include <string>

#include "module/module.hh"

#include "wrapped_types/py_dict.hh"
#include "wrapped_types/py_list.hh"
#include "wrapped_types/py_tuple.hh"

#include "result.hh"

namespace python
{
    bool init();
    void deinit();

    Result<void*> insert_path(std::string path);
}