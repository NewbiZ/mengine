#include <iostream>
#include <cstdlib>

#include <Python.h>

#include <mengine/mengine.h>
#include <mengine/engine/engine.h>
#include <mengine/scene/intro.h>

typedef struct PyMemberDef {
    char *name;
    int   type;
    int   offset;
    int   flags;
    char *doc;
} PyMemberDef;

void pymengine_HandleError()
{
}

// ====================
// mengine::Scene
// ====================

class PySceneWrapper : public mengine::Scene
{
public:
  PySceneWrapper(PyObject* self) : self_(self) {}
  virtual ~PySceneWrapper() {}

public:
  virtual bool setup()
  {
    if (PyObject_HasAttrString(self_, "setup"))
    {
      PyObject* result = PyObject_CallMethod(self_, "setup", "");
      if (result == 0)
      {
        pymengine_HandleError();
      }
    }
    else
    {
      self_->setup();
    }
  }

  virtual bool cleanup();
  virtual void handle_events();
  virtual void update(double time_delta);
  virtual void render();

private:
  PyObject* self_;
};

typedef struct
{
  PyObject_HEAD
  mengine::Scene* w_scene_;
} pymengine_SceneObject;

static PyMemberDef pymengine_SceneObject_members[] = {
  {NULL}
};

static PyObject* pymengine_SceneObject_new(PyTypeObject* type, PyObject* args, PyObject* kwargs)
{
  pymengine_SceneObject* self;

  self = (pymengine_SceneObject*)type->tp_alloc(type, 0);

  if (self != 0)
  {
    self->w_scene_ = new mengine::Scene();
  }

  return (PyObject*)self;
}

static void pymengine_SceneObject_dealloc(pymengine_SceneObject* self)
{
  delete self->w_scene_;

  Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* pymengine_SceneObject_setup(pymengine_SceneObject* self)
{
  self->w_scene_->setup();

  Py_RETURN_NONE;
}

static PyObject* pymengine_SceneObject_cleanup(pymengine_SceneObject* self)
{
  self->w_scene_->cleanup();

  Py_RETURN_NONE;
}

static PyObject* pymengine_SceneObject_handle_events(pymengine_SceneObject* self)
{
  self->w_scene_->handle_events();

  Py_RETURN_NONE;
}

static PyObject* pymengine_SceneObject_update(pymengine_SceneObject* self)
{
  self->w_scene_->update(1);

  Py_RETURN_NONE;
}

static PyObject* pymengine_SceneObject_render(pymengine_SceneObject* self)
{
  self->w_scene_->render();

  Py_RETURN_NONE;
}

static PyMethodDef pymengine_SceneObject_methods[] = {
    {"setup", (PyCFunction)pymengine_SceneObject_setup, METH_NOARGS,
              ""},
    {"cleanup", (PyCFunction)pymengine_SceneObject_cleanup, METH_NOARGS,
                ""},
    {"handle_events", (PyCFunction)pymengine_SceneObject_handle_events, METH_NOARGS,
                      ""},
    {"update", (PyCFunction)pymengine_SceneObject_update, METH_NOARGS,
               ""},
    {"render", (PyCFunction)pymengine_SceneObject_render, METH_NOARGS,
               ""},
    {NULL}
};


static PyTypeObject pymengine_SceneType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "_pymengine.Scene",                           // tp_name
  sizeof(pymengine_SceneObject),                // tp_basicsize
  0,                                            // tp_itemsize
  (destructor)pymengine_SceneObject_dealloc,    // tp_dealloc
  0,                                            // tp_print
  0,                                            // tp_getattr
  0,                                            // tp_setattr
  0,                                            // tp_reserved
  0,                                            // tp_repr
  0,                                            // tp_as_number
  0,                                            // tp_as_sequence
  0,                                            // tp_as_mapping
  0,                                            // tp_hash
  0,                                            // tp_call
  0,                                            // tp_str
  0,                                            // tp_getattro
  0,                                            // tp_setattro
  0,                                            // tp_as_buffer
  Py_TPFLAGS_DEFAULT | Py_TPFLAGS_DEFAULT,      // tp_flags
  "Scene object",                              // tp_doc
  0,                                            // tp_traverse
  0,                                            // tp_clear
  0,                                            // tp_richcompare
  0,                                            // tp_weaklistoffset
  0,                                            // tp_iter
  0,                                            // tp_iternext
  pymengine_SceneObject_methods,                // tp_methods
  pymengine_SceneObject_members,                // tp_members
  0,                                            // tp_getset
  0,                                            // tp_base
  0,                                            // tp_dict
  0,                                            // tp_descr_get
  0,                                            // tp_descr_set
  0,                                            // tp_dictoffset
  0,                                            // tp_init
  0,                                            // tp_alloc
  pymengine_SceneObject_new,                   // tp_new
};

// ====================
// mengine::Engine
// ====================

typedef struct
{
  PyObject_HEAD
  mengine::Engine* w_engine_;
} pymengine_EngineObject;

static PyMemberDef pymengine_EngineObject_members[] = {
  {NULL}
};

static PyObject* pymengine_EngineObject_new(PyTypeObject* type, PyObject* args, PyObject* kwargs)
{
  pymengine_EngineObject* self;

  self = (pymengine_EngineObject*)type->tp_alloc(type, 0);

  if (self != 0)
  {
    self->w_engine_ = &mengine::Engine::instance();
  }

  return (PyObject*)self;
}

static void pymengine_EngineObject_dealloc(pymengine_EngineObject* self)
{
  Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* pymengine_EngineObject_start(pymengine_EngineObject* self)
{
  self->w_engine_->start();

  Py_RETURN_NONE;
}

static PyObject* pymengine_EngineObject_stop(pymengine_EngineObject* self)
{
  self->w_engine_->stop();

  Py_RETURN_NONE;
}

static PyObject* pymengine_EngineObject_set_scene(pymengine_EngineObject* self)
{
  self->w_engine_->set_scene(0);

  Py_RETURN_NONE;
}

static PyMethodDef pymengine_EngineObject_methods[] = {
    {"start", (PyCFunction)pymengine_EngineObject_start, METH_NOARGS,
              "Start the engine with the provided scene and enter the rendering loop."},
    {"stop", (PyCFunction)pymengine_EngineObject_start, METH_NOARGS,
             "Stop the engine and terminate the start() call."},
    {"set_scene", (PyCFunction)pymengine_EngineObject_set_scene, METH_NOARGS,
             "Set a scene to be played by the engine."},
    {NULL}
};


static PyTypeObject pymengine_EngineType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "_pymengine.Engine",                          // tp_name
  sizeof(pymengine_EngineObject),               // tp_basicsize
  0,                                            // tp_itemsize
  (destructor)pymengine_EngineObject_dealloc,   // tp_dealloc
  0,                                            // tp_print
  0,                                            // tp_getattr
  0,                                            // tp_setattr
  0,                                            // tp_reserved
  0,                                            // tp_repr
  0,                                            // tp_as_number
  0,                                            // tp_as_sequence
  0,                                            // tp_as_mapping
  0,                                            // tp_hash
  0,                                            // tp_call
  0,                                            // tp_str
  0,                                            // tp_getattro
  0,                                            // tp_setattro
  0,                                            // tp_as_buffer
  Py_TPFLAGS_DEFAULT | Py_TPFLAGS_DEFAULT,      // tp_flags
  "Engine object",                              // tp_doc
  0,                                            // tp_traverse
  0,                                            // tp_clear
  0,                                            // tp_richcompare
  0,                                            // tp_weaklistoffset
  0,                                            // tp_iter
  0,                                            // tp_iternext
  pymengine_EngineObject_methods,               // tp_methods
  pymengine_EngineObject_members,               // tp_members
  0,                                            // tp_getset
  0,                                            // tp_base
  0,                                            // tp_dict
  0,                                            // tp_descr_get
  0,                                            // tp_descr_set
  0,                                            // tp_dictoffset
  0,                                            // tp_init
  0,                                            // tp_alloc
  pymengine_EngineObject_new,                   // tp_new
};

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
  
  // Add version of MEngine to the module
  PyModule_AddStringConstant(module, "__version__", mengine::version);

  return module;
}
