#include <pylight/module/module.hh>
#include <pylight/utils.hh>

namespace python
{
    Result<Module> Module::from_dotted(std::string path)
    {
        Module mod;

        PyObject* py_path = PyUnicode_FromString(path.c_str());
        if (py_path == NULL)
            return Result<Module>::failure(std::format("Failed to convert path to Python string: {}", path));

        PyObject* py_module = PyImport_Import(py_path);
        if (py_module == NULL)
            return Result<Module>::failure(std::format("Failed to import {}", path));

        Py_DECREF(py_path);

        return Result<Module>::success(mod);
    }

    Result<void*> Module::reload()
    {
        if (!py_module)
            return Result<void*>::failure("Attempted to reload a module that wasn't loaded (properly?)");
        PyObject* new_ref = PyImport_ReloadModule(py_module);
        if (new_ref == NULL)
            return Result<void*>::failure("Failed to reload module");
        
        Py_DECREF(py_module);
        py_module = new_ref;
        
        return Result<void*>::success(nullptr);
    }
}