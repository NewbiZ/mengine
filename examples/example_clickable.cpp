#include <iostream>
#include <cstdlib>
#include <cstring>

#include <mengine/mengine.h>
#include <mengine/engine/engine.h>
#include <mengine/scene/scene.h>
#include <mengine/engine/text.h>
#include <mengine/engine/clickable.h>

class MyTestButton : public mengine::Clickable
{
public:
    MyTestButton()    
    {        
    }   

    virtual ~MyTestButton()
    {
    }

public:
    virtual void render() const
    {

    }

    virtual void execute() const
    {
        std::cout << "test" << std::endl;
        //engine.stop();
    }
};

class MyTestScene : public mengine::Scene
{
public:
    MyTestScene()
    {
    }

public:
    virtual bool setup()
    {
        // Clear values
        glClearColor(0.25, 0.5, 0.75, 0);
        glClearDepth(0);

        // Setup projection matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho (0.0, 1024, 0.0, 768, -1.0, 1.0);

        // Setup modelview matrix
        glMatrixMode(GL_MODELVIEW);

        // Setup the text and button properties
        text1_.set_text("Quitter");
        text1_.set_position(0, 0.);
        text1_.set_color(1., 0., 0.);  

        return true;
    }

    virtual bool cleanup()
    {
        return true;
    }

    virtual void handle_events()
    {
        // Exit when we press Escape
        if (glfwGetKey(GLFW_KEY_ESC)==GLFW_PRESS)
            mengine::Engine::instance().stop();
    }

    virtual void update(double time_delta)
    {
    }

    virtual void render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        text1_.render();        
        
    }

private:
    mengine::Text text1_;
    MyTestButton button_;
};

int main(int argc, char** argv)
{
    mengine::Engine& engine = mengine::Engine::instance();

    engine.set_scene(new MyTestScene);
	
    engine.start();

    return EXIT_SUCCESS;
}

