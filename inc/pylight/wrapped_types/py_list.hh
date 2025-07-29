#pragma once

#include <Python.h>

#include "pylight/wrapped_types/convert.hh"
#include "pylight/result.hh"

#include "py_object.hh"

namespace python
{
    class List: public Object<List>
    {
        public:
            static Result<List> create(int size = 0);

            template<PythonConvertible T>
            Result<void*> append(T owned_value)
            {
                PyObject* py_val = to_python(owned_value);
                if (py_val == nullptr)
                    return Result<void*>::failure("Failed to convert T to python object");
                return append(py_val);
            }

            Result<void*> append(PyObject* owned_value);
    };
}