#pragma once

#include <Python.h>

#include "pylight/wrapped_types/convert.hh"
#include "pylight/result.hh"

namespace python
{
    class Dict
    {
        public:
            static Result<Dict> create();

            PyObject* get() const { return py_dict; }

            template<PythonConvertible T>
            Result<void*> set_item(const char* key, T owned_value)
            {
                PyObject* py_val = to_python(owned_value);
                if (py_val == nullptr)
                    return Result<void*>::failure("Failed to convert T to python object");
                return set_item(key, py_val);
            }

            Result<void*> set_item(const char* key, PyObject* owned_value);
        private:
            PyObject* py_dict = nullptr;
    };
}