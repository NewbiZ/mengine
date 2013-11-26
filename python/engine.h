#ifndef PYMENGINE_ENGINE_H
#define PYMENGINE_ENGINE_H

#include <mengine/engine/engine.h>

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
    self->w_engine_ = &mengine::Engine::instance();

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

static PyObject* pymengine_EngineObject_set_scene(pymengine_EngineObject* self, PyObject* args, PyObject* kwargs)
{
  PyObject* scene;

  if (!PyArg_ParseTuple(args, "O", &scene))
    pymengine_HandleError();

  self->w_engine_->set_scene(((pymengine_SceneObject*)scene)->w_scene_, mengine::Engine::scene_forget);

  Py_RETURN_NONE;
}

static PyMethodDef pymengine_EngineObject_methods[] = {
    {"start", (PyCFunction)pymengine_EngineObject_start, METH_NOARGS,
              "Start the engine with the provided scene and enter the rendering loop."},
    {"stop", (PyCFunction)pymengine_EngineObject_start, METH_NOARGS,
             "Stop the engine and terminate the start() call."},
    {"set_scene", (PyCFunction)pymengine_EngineObject_set_scene, METH_VARARGS,
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

#endif // PYMENGINE_ENGINE_H

