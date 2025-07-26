#pragma once

#include <string>

#include <Python.h>

#include "pylight/result.hh"
#include "pylight/utils.hh"

#include "pylight/wrapped_types/py_tuple.hh"

namespace python
{
    class Module
    {
        public:
            static Result<Module> from_path(std::string path) { return Module::from_dotted(path_to_dotted(path)); }
            static Result<Module> from_dotted(std::string dotted_path);

            Result<void*> reload();
            
            Result<PyObject*> call(const char* func, PyObject* owned_args);
        private:
            PyObject* py_module = nullptr;
    };
}