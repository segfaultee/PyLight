#pragma once

#include <iostream>

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
        if (tuple == nullptr)
            return nullptr;

        size_t i = 0;
        auto process_arg = [&](auto&& arg) -> bool // we do NOT decref `tuple` here, only the arg-objs we're currently processing
        {
            PyObject* obj = to_python(std::forward<decltype(arg)>(arg));
            if (obj == nullptr)
                return false;

            if (PyTuple_SetItem(tuple, i++, obj) != 0)
            {
                // Py_DECREF(obj); // PyTuple_SetItem *STEALS* a reference on both failure and success
                return false;
            }

            return true;
        };

        bool success = (process_arg(std::forward<Args>(args))&&...);

        if (!success)
        {
            Py_DECREF(tuple); // decref tuple on failure as we didn't do that in process_arg
            return nullptr;
        }

        return tuple;
    }
}