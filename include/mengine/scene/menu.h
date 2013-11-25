#ifndef MENGINE_SCENE_MENU_H
#define MENGINE_SCENE_MENU_H

#include <mengine/scene/scene.h>

namespace mengine
{

class Menu : public Scene
{
public:
    Menu();
    virtual ~Menu();

public:
    virtual bool setup();
    virtual bool cleanup();
    virtual void handle_events();
    virtual void update(double time_delta);
    virtual void render();
};

} // end of namespace 'mengine'

#endif // MENGINE_SCENE_MENU_H

