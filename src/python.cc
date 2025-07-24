#include <Python.h>

#include <pylight/python.hh>

namespace python
{
    bool init()
    {
        Py_Initialize();
        return true;
    }

    void deinit()
    {
        Py_Finalize();
    }
}