#pragma once

#include <Python.h>

#include "pylight/wrapped_types/convert.hh"
#include "pylight/result.hh"

#include "py_object.hh"

namespace python
{
    class Dict: public Object<Dict>
    {
        public:
            static Result<Dict> create();

            template<PythonConvertible T>
            Result<void*> set_item(const char* key, T owned_value)
            {
                PyObject* py_val = to_python(owned_value);
                if (py_val == nullptr)
                    return Result<void*>::failure("Failed to convert T to python object");
                return set_item(key, py_val);
            }

            Result<void*> set_item(const char* key, PyObject* owned_value);
    };
}