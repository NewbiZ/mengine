#ifndef MENGINE_SCENE_H
#define MENGINE_SCENE_H

namespace mengine
{

class Scene
{
public:
    /*
     * Do not load resources in the Scene constructor, since Scene may
     * be created in advance but used later on. Use setup() instead
     */
    Scene();

    /*
     * Do not deallocate resources in the Scene destructor, since you have
     * no guarantee on when the destructor will be called. Use cleanup()
     * instead
     */
    virtual ~Scene();

public:
    /*
     * Allow you to setup the Scene, acquire its resources, etc.
     * This is the very first method that will be called before
     * actually using this Scene
     */
    virtual bool setup();

    /*
     * Allow you to deallocate resources request by setup()
     * This is the very last method that will be used before discarding
     * this Scene
     */
    virtual bool cleanup();

    /*
     * Allow you to process events such as keyboard and mouse inputs
     */
    virtual void handle_events();

    /*
     * Allow you to compute all the data needed to render the Scene
     * The time_delta parameter is the number of seconds since the
     * previous call to update()
     */
    virtual void update(double time_delta);

    /*
     * Allow you to render the Scene
     */
    virtual void render();
};

} // end of namespace 'mengine'

#endif // MENGINE_SCENE_H

