#ifndef PYMENGINE_SCENE_H
#define PYMENGINE_SCENE_H

#include <map>

#include <mengine/scene/scene.h>

class PySceneWrapper : public mengine::Scene
{
public:
  PySceneWrapper(PyObject* self) : self_(self) {}
  virtual ~PySceneWrapper() {}

public:
  virtual bool setup()
  {
    bool r = false;
    if (PyObject_HasAttrString(self_, "setup"))
    {
      PyObject* result = PyObject_CallMethod(self_, (char*)"setup", (char*)"");
      if (result==0)
        pymengine_HandleError();
      r = PyObject_IsTrue(result);
    }
    else
      r = this->mengine::Scene::setup();
    return r;
  }

  virtual bool cleanup()
  {
    bool r = false;
    if (PyObject_HasAttrString(self_, "cleanup"))
    {
      PyObject* result = PyObject_CallMethod(self_, (char*)"cleanup", (char*)"");
      if (result==0)
        pymengine_HandleError();
      r = PyObject_IsTrue(result);
    }
    else
      r = this->mengine::Scene::cleanup();
    return r;
  }

  virtual void handle_events()
  {
    if (PyObject_HasAttrString(self_, "handle_events"))
    {
      PyObject* result = PyObject_CallMethod(self_, (char*)"handle_events", (char*)"");
      if (result==0)
        pymengine_HandleError();
    }
    else
      this->mengine::Scene::handle_events();
  }

  virtual void update(double time_delta)
  {
    if (PyObject_HasAttrString(self_, "update"))
    {
      PyObject* result = PyObject_CallMethod(self_, (char*)"update", (char*)"d", time_delta);
      if (result==0)
        pymengine_HandleError();
    }
    else
      this->mengine::Scene::update(time_delta);
  }

  virtual void render()
  {
    if (PyObject_HasAttrString(self_, "render"))
    {
      PyObject* result = PyObject_CallMethod(self_, (char*)"render", (char*)"");
      if (result==0)
        pymengine_HandleError();
    }
    else
      this->mengine::Scene::render();
  }

private:
  PyObject* self_;
};

std::map<PySceneWrapper*, PyObject*> sceneWrappers;

typedef struct
{
  PyObject_HEAD
  PySceneWrapper* w_scene_;
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
    self->w_scene_ = new PySceneWrapper((PyObject*)self);
    sceneWrappers[self->w_scene_] = (PyObject*)self;
  }
  else
    pymengine_HandleError();

  return (PyObject*)self;
}

static void pymengine_SceneObject_dealloc(pymengine_SceneObject* self)
{
  sceneWrappers.erase(self->w_scene_);
  delete self->w_scene_;

  Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* pymengine_SceneObject_setup(pymengine_SceneObject* self)
{
  PyObject* result = PyBool_FromLong(self->w_scene_->mengine::Scene::setup());

  Py_INCREF(result);

  return result;
}

static PyObject* pymengine_SceneObject_cleanup(pymengine_SceneObject* self)
{
  PyObject* result = PyBool_FromLong(self->w_scene_->mengine::Scene::cleanup());

  Py_INCREF(result);

  return result;
}

static PyObject* pymengine_SceneObject_handle_events(pymengine_SceneObject* self)
{
  self->w_scene_->mengine::Scene::handle_events();

  Py_RETURN_NONE;
}

static PyObject* pymengine_SceneObject_update(pymengine_SceneObject* self, PyObject* args, PyObject* kwargs)
{
  double time_delta;

  if (!PyArg_ParseTuple(args, "d", &time_delta))
    pymengine_HandleError();

  self->w_scene_->mengine::Scene::update(time_delta);

  Py_RETURN_NONE;
}

static PyObject* pymengine_SceneObject_render(pymengine_SceneObject* self)
{
  self->w_scene_->mengine::Scene::render();

  Py_RETURN_NONE;
}

static PyMethodDef pymengine_SceneObject_methods[] = {
    {"setup", (PyCFunction)pymengine_SceneObject_setup, METH_NOARGS,
              "Initialize the scene. Called by Engine before the scene gets displayed."},
    {"cleanup", (PyCFunction)pymengine_SceneObject_cleanup, METH_NOARGS,
              "Cleanup the scene, after it has been deactivated by the Engine."},
    {"handle_events", (PyCFunction)pymengine_SceneObject_handle_events, METH_NOARGS,
              "Handle input events during Engine's main loop."},
    {"update", (PyCFunction)pymengine_SceneObject_update, METH_VARARGS,
              "Update scene objects during Engine's main loop."},
    {"render", (PyCFunction)pymengine_SceneObject_render, METH_NOARGS,
              "Render the scene during Engine's main loop."},
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
  Py_TPFLAGS_DEFAULT | Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,      // tp_flags
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

#endif // PYMENGINE_SCENE_H

