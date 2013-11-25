#include <mengine/scene/scene.h>

#include <GL/glfw.h>

namespace mengine
{

Scene::Scene()
{
}

Scene::~Scene()
{
}

bool Scene::setup()
{
    glClearColor(0.25, 0.5, 0.75, 0);
    glClearDepth(0);
    return true;
}

bool Scene::cleanup()
{
    return true;
}

void Scene::handle_events()
{
}

void Scene::update(double time_delta)
{
}

void Scene::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

} // end of namespace 'mengine'

