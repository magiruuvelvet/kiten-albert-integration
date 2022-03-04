#include <Python.h>

#include <memory>

#include "kiten.hpp"

std::shared_ptr<Kiten> kiten;

static PyObject *kiten_lookup(PyObject *self, PyObject *args)
{
    const char *query;
    unsigned int limit = 15;

    if (!PyArg_ParseTuple(args, "sI", &query, &limit))
    {
        return nullptr;
    }

    const auto results = kiten->lookup(query, limit);

    PyObject *py_list = PyList_New(results.size());
    for (int i = 0U; i < results.size(); ++i)
    {
        PyObject *py_str = Py_BuildValue("s", results.at(i).c_str());
        PyList_SetItem(py_list, i, py_str);
    }

    return py_list;
}

static PyMethodDef kitenpy_methods[] = {
    {"lookup", kiten_lookup, METH_VARARGS, nullptr},

    {nullptr, nullptr, 0, nullptr},
};

static struct PyModuleDef kitenpy_module = {
    PyModuleDef_HEAD_INIT,
    "kitenpy", // module name
    nullptr,   // module documentation
    -1,
    kitenpy_methods,
};

PyMODINIT_FUNC PyInit_libkitenpy(void)
{
    kiten = std::make_shared<Kiten>();
    return PyModule_Create(&kitenpy_module);
}
