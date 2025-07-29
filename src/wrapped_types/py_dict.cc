#include <pylight/wrapped_types/py_dict.hh>

namespace python
{
    Result<Dict> Dict::create()
    {
        PyObject* py_dict = PyDict_New();
        if (py_dict == nullptr)
            return Result<Dict>::failure("Failed to create new python dictionary object");

        Dict dict;
        dict.py_object = py_dict;

        return Result<Dict>::success(dict);
    }

    Result<void*> Dict::set_item(const char* key, PyObject* owned_value)
    {
        if (PyDict_SetItemString(py_object, key, owned_value) != 0)
        {
            Py_DECREF(owned_value);
            return Result<void*>::failure(std::format("Failed to set {}", key));
        }
        
        Py_DECREF(owned_value); 
        // Note we decref here because of the following:
        // 1. We own this object (hence the owned_ prefix)
        // 2. PyDict_SetItemString takes a *ref* to this object meaning it 
        //    increase the ref count so that it could hang on to it. 
        return Result<void*>::success(nullptr);
    }
}