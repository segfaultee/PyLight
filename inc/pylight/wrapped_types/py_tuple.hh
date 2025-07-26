#pragma once

#include <Python.h>

#include "pylight/result.hh"

#include "convert.hh"

namespace python
{
    template<typename... Args>
    PyObject* pack_tuple(Args&&... args) 
    {
        constexpr size_t arg_count = sizeof...(Args);
        PyObject* tuple = PyTuple_New(arg_count);

        if (!tuple) 
            return nullptr;

        PyObject* items[arg_count] = { to_python(std::forward<Args>(args))... };

        for (size_t i = 0; i < arg_count; ++i) 
        {
            if (!items[i]) 
            {
                Py_DECREF(tuple);
                return nullptr;
            }
            PyTuple_SET_ITEM(tuple, i, items[i]);
        }

        return tuple;
    }
}