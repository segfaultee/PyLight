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

    Result<void*> insert_path(std::string path)
    {
        PyObject* sys_path = PySys_GetObject("path");

        if (sys_path == nullptr)
            return Result<void*>::failure("Failed to get `path` object from sys.");

        PyObject* py_path = PyUnicode_FromString(path.c_str());
        if (py_path == nullptr)
            return Result<void*>::failure(std::format("Failed to convert path to Python string: {}", path));
        
        bool res = PyList_Insert(sys_path, 0, py_path) == 0;
        Py_DECREF(py_path);

        if (!res)
            return Result<void*>::failure(std::format("Failed to insert path {} into sys.path", path));
        return Result<void*>::success(nullptr);
    }
}