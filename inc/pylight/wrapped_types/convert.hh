#pragma once

#include <string>
#include <concepts>
#include <type_traits>

#include <Python.h>

#include "py_object.hh"
namespace python
{
    template<typename T>
    concept PythonConvertible = 
        std::same_as<T, int> || 
        std::same_as<T, double> || 
        std::same_as<T, const char*> || 
        std::same_as<T, std::string> ||
        std::same_as<T, Object<T>>;

    template<PythonConvertible T>
    inline PyObject* to_python(T value);

    template<>
    inline PyObject* to_python<int>(int value) { return PyLong_FromLong(value); }

    template<>
    inline PyObject* to_python<double>(double value) { return PyFloat_FromDouble(value); }

    template<>
    inline PyObject* to_python<const char*>(const char* value) { return PyUnicode_FromString(value); }

    template<>
    inline PyObject* to_python<std::string>(std::string value) { return PyUnicode_FromString(value.c_str()); }

    template<typename T>
    inline PyObject* to_python(const Object<T>& value) { return value.get(); }
}