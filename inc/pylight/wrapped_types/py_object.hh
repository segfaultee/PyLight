#pragma once

#include <Python.h>

#include "pylight/result.hh"

namespace python
{
    template <typename Child>
    class Object 
    {
        public:
            template <typename... Args>
            static Result<Child> create(Args&&... args) { return Child::create(std::forward<Args>(args)...); }

            static Result<Child> from_object(PyObject* object) 
            {
                Child obj;
                obj.py_object = object;
                return Result<Child>::success(obj);
            }

            void decref() const { Py_DECREF(py_object); }
            void incref() const { Py_INCREF(py_object); }
            size_t refcnt() const { return Py_REFCNT(py_object); }

            PyObject* get() const { return py_object; }
            PyObject* ref() const 
            {
                Py_INCREF(py_object);
                return py_object;
            }
        protected:
            PyObject* py_object = nullptr;
    };
}