#ifndef MENGINE_ENGINE_H
#define MENGINE_ENGINE_H

#include <functional>

namespace mengine
{

class Scene;

/*
 * This is the main entry point of the game. The Engine class
 * manages the windowing subsystem along with the setup of the
 * event loop.
 * This class is a singleton, if you whish to use it, just use
 * the instance() method.
 */
class Engine
{
public:
    typedef std::function<void(Scene*)> scene_unset_handler_t;
    static const scene_unset_handler_t scene_destroy;
    static const scene_unset_handler_t scene_forget;

public:
    static Engine& instance();

public:
    void start();
    void stop();

public:
    void set_scene(Scene* scene, scene_unset_handler_t handler=scene_destroy);

private:
    Engine();
    ~Engine();

private:
    void init();

private:
    bool running_;
    Scene* scene_;
    scene_unset_handler_t handler_;
    Scene* pending_scene_;
    scene_unset_handler_t pending_handler_;
    static Engine* instance_;
};

} // end of namespace 'mengine'

#endif // MENGINE_ENGINE_H

