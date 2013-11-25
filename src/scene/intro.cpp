#include <mengine/scene/intro.h>

#include <GL/glfw.h>

#include <mengine/scene/menu.h>
#include <mengine/engine/engine.h>

namespace mengine
{

Intro::Intro()
{
}

Intro::~Intro()
{
}

bool Intro::setup()
{
    glClearColor(0.25, 0.5, 0.75, 0);
    glClearDepth(0);
    return true;
}

bool Intro::cleanup()
{
    return true;
}

void Intro::handle_events()
{
    if (glfwGetKey(GLFW_KEY_ESC)==GLFW_PRESS)
    {
        Scene* menu = new Menu();
        Engine::instance().set_scene(menu);
    }
}

void Intro::update(double time_delta)
{
}

void Intro::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

} // end of namespace 'mengine'

