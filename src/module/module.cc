#include <format>

#include <pylight/module/module.hh>
#include <pylight/utils.hh>

namespace python
{
    Result<Module> Module::from_dotted(std::string path)
    {
        Module mod;

        PyObject* py_path = PyUnicode_FromString(path.c_str());
        if (py_path == nullptr)
            return Result<Module>::failure(std::format("Failed to convert path to Python string: {}", path));

        PyObject* py_module = PyImport_Import(py_path);
        if (py_module == nullptr)
        {
            Py_DECREF(py_path);
            return Result<Module>::failure(std::format("Failed to import {}", path));
        }

        Py_DECREF(py_path);

        mod.py_module = py_module;
        return Result<Module>::success(mod);
    }

    Result<Module> Module::from_object(PyObject* owned_module_obj)
    {
        Module mod;
        mod.py_module = owned_module_obj;
        return Result<Module>::success(mod);
    }

    Result<void*> Module::reload()
    {
        if (!py_module)
            return Result<void*>::failure("Attempted to reload a module that wasn't loaded (properly?)");
        PyObject* new_ref = PyImport_ReloadModule(py_module);
        if (new_ref == nullptr)
            return Result<void*>::failure("Failed to reload module");
        
        Py_DECREF(py_module);
        py_module = new_ref;
        
        return Result<void*>::success(nullptr);
    }

    Result<void*> Module::add_object(const char* name, PyObject* owned_obj)
    {
        if (PyModule_Add(py_module, name, owned_obj) != 0) // stolen, we do not decref owned_obj, PyModule_Add does.
            return Result<void*>::failure(std::format("Failed to add object to {}", name));
        return Result<void*>::success(nullptr);
    }

    Result<void*> Module::add_to_sys_modules(const char* name)
    {
        PyObject* sys_modules = PyImport_GetModuleDict(); // borrowed
        if (sys_modules == nullptr)
            return Result<void*>::failure("Failed to get sys.modules");

        if (auto res = PyDict_ContainsString(sys_modules, name); res == 1)
            return Result<void*>::success(nullptr);
        else if (res == -1)
            return Result<void*>::failure("PyDict_ContainsString failed");

        if (PyDict_SetItemString(sys_modules, name, py_module) != 0) // borrows py_module from us, no internal decreffing
            return Result<void*>::failure(std::format("Failed to set {} in sys.modules dict", name));

        return Result<void*>::success(nullptr);
    }

    Result<PyObject*> Module::call(const char* func, PyObject* owned_args)
    {
        PyObject* callable = PyObject_GetAttrString(py_module, func); // new reference
        if (callable == nullptr)
        {
            Py_XDECREF(owned_args);
            return Result<PyObject*>::failure(std::format("Failed to get attribute {}", func));
        }

        if (!PyCallable_Check(callable))
        {
            Py_DECREF(callable);
            Py_XDECREF(owned_args);
            return Result<PyObject*>::failure(std::format("{} is not a callable", func));   
        }

        PyObject* ret_val = PyObject_CallObject(callable, owned_args);
        Py_DECREF(callable);
        Py_XDECREF(owned_args);

        if (ret_val == nullptr)
            return Result<PyObject*>::failure(std::format("{} failed", func));
            
        return Result<PyObject*>::success(ret_val);
    }
}