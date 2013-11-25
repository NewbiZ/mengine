#include <iostream>
#include <cstdlib>

#include <mengine/mengine.h>
#include <mengine/engine/engine.h>
#include <mengine/scene/intro.h>

int main(int argc, char** argv)
{
    mengine::Engine& engine = mengine::Engine::instance();

    engine.set_scene(new mengine::Intro);

    engine.start();

    return EXIT_SUCCESS;
}

