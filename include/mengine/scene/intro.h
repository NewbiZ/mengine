#ifndef MENGINE_SCENE_INTRO_H
#define MENGINE_SCENE_INTRO_H

#include <mengine/scene/scene.h>

namespace mengine
{

class Intro : public Scene
{
public:
    Intro();
    virtual ~Intro();

public:
    virtual bool setup();
    virtual bool cleanup();
    virtual void handle_events();
    virtual void update(double time_delta);
    virtual void render();
};

} // end of namespace 'mengine'

#endif // MENGINE_SCENE_INTRO_H

