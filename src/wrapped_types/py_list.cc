#include <pylight/wrapped_types/py_list.hh>

namespace python
{
    Result<List> List::create(int size)
    {
        PyObject* py_list = PyList_New(size);
        if (py_list == nullptr)
            return Result<List>::failure("Failed to create new python list object");

        List list;
        list.py_object = py_list;

        return Result<List>::success(list);
    }

    Result<void*> List::append(PyObject* owned_value)
    {
        if (PyList_Append(py_object, owned_value) != 0)
        {
            Py_DECREF(owned_value);
            return Result<void*>::failure("Failed to append value to py_list");
        }

        Py_DECREF(owned_value); // owned_value's ref gets incremented by PyList_Append

        return Result<void*>::success(nullptr);
    }
}