#pragma once

#include <string>

#include <Python.h>

#include "pylight/result.hh"
#include "pylight/utils.hh"

namespace python
{
    class Module
    {
        public:
            static Result<Module> from_path(std::string path) { return Module::from_dotted(path_to_dotted(path)); }
            static Result<Module> from_dotted(std::string dotted_path);

            Result<void*> reload();
        private:
            PyObject* py_module = nullptr;
    };
}