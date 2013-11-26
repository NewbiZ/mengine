#include <mengine/mengine.h>

#include <Python.h>

// ====================
// helpers
// ====================
typedef struct PyMemberDef {
    char *name;
    int   type;
    int   offset;
    int   flags;
    char *doc;
} PyMemberDef;

void pymengine_HandleError()
{
  PyObject* type = PyErr_Occurred();
  if (type!=0)
    PyErr_Print();
  exit(1);
}

// ====================
// mengine classes
// ====================
#include "scene.h"
#include "engine.h"

// ====================
// mengine module
// ====================

static PyMethodDef PyMEngineMethods[] = {
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef pymenginemodule = {
  PyModuleDef_HEAD_INIT,
  "_pymengine",
  "MEngine python bindings module",
  -1,
  NULL, NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC
PyInit__pymengine(void)
{
  // Module initialization
  PyObject* module = PyModule_Create(&pymenginemodule);

  // mengine::Engine
  if (PyType_Ready(&pymengine_EngineType) < 0)
        return NULL;
  Py_INCREF(&pymengine_EngineType);
  PyModule_AddObject(module, "Engine", (PyObject*)&pymengine_EngineType);

  // mengine::Scene
  if (PyType_Ready(&pymengine_SceneType) < 0)
        return NULL;
  Py_INCREF(&pymengine_SceneType);
  PyModule_AddObject(module, "Scene", (PyObject*)&pymengine_SceneType);
  
  // Add version of MEngine to the module
  PyModule_AddStringConstant(module, "__version__", mengine::version);

  return module;
}
