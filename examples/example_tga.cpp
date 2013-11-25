#include <iostream>
#include <cstdlib>

#include <GL/glfw.h>

#include <mengine/engine/text.h>
#include <mengine/engine/engine.h>
#include <mengine/scene/scene.h>
#include <mengine/loaders/tga_loader.h>

GLuint load_texture(const std::string& filename)
{
    GLuint texture;
    glGenTextures(1, &texture);

    mengine::TextureInfo texture_info;
    mengine::load_tga(filename, texture_info);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(texture_info.target,
                 texture_info.level,
                 texture_info.internalFormat,
                 texture_info.width,
                 texture_info.height,
                 0,
                 texture_info.format,
                 texture_info.type,
                 texture_info.data);

    delete [] texture_info.data;

    return texture;
}

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

        glEnable(GL_TEXTURE_2D);

        texture_ctc24_ = load_texture("examples/data/test_tga_ctc24.tga");
        texture_ctc32_ = load_texture("examples/data/test_tga_ctc32.tga");
        texture_utc24_ = load_texture("examples/data/test_tga_utc24.tga");
        texture_utc32_ = load_texture("examples/data/test_tga_utc32.tga");

        text_ctc24_.set_text("Compressed - True color - 24bpp");
        text_ctc32_.set_text("Compressed - True color - 32bpp");
        text_utc24_.set_text("Uncompressed - True color - 24bpp");
        text_utc32_.set_text("Uncompressed - True color - 32bpp");

        text_ctc24_.set_position(0.01, 0.51);
        text_ctc32_.set_position(0.51, 0.51);
        text_utc24_.set_position(0.01, 0.01);
        text_utc32_.set_position(0.51, 0.01);

        return true;
    }

    virtual bool cleanup()
    {
        glDeleteTextures(1, &texture_ctc24_);
        glDeleteTextures(1, &texture_ctc32_);
        glDeleteTextures(1, &texture_utc24_);
        glDeleteTextures(1, &texture_utc32_);
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
        glClear(GL_COLOR_BUFFER_BIT);

        glLoadIdentity();

        // Align on (0;0) on lower left corner
        //          (1;1) on top right corner
        glPushMatrix();
        glTranslatef(-1.0, -1.0, 0.0);
        glScalef(2.0, 2.0, 1.0);

        // Top left
        // Compressed - True colors - 24bpp
        glBindTexture(GL_TEXTURE_2D, texture_ctc24_);
        glBegin(GL_QUADS);
             glTexCoord2f(0.0, 0.0);
             glVertex2f(0.01, 0.53);

             glTexCoord2f(1.0, 0.0);
             glVertex2f(0.49, 0.53);

             glTexCoord2f(1.0, 1.0);
             glVertex2f(0.49, 0.99);

             glTexCoord2f(0.0, 1.0);
             glVertex2f(0.01, 0.99);
        glEnd();

        // Top right
        // Compressed - True colors - 32bpp
        glBindTexture(GL_TEXTURE_2D, texture_ctc32_);
        glBegin(GL_QUADS);
             glTexCoord2f(0.0, 0.0);
             glVertex2f(0.51, 0.53);

             glTexCoord2f(1.0, 0.0);
             glVertex2f(0.99, 0.53);

             glTexCoord2f(1.0, 1.0);
             glVertex2f(0.99, 0.99);

             glTexCoord2f(0.0, 1.0);
             glVertex2f(0.51, 0.99);
        glEnd();

        // Bottom left
        // Uncompressed - True colors - 24bpp
        glBindTexture(GL_TEXTURE_2D, texture_utc24_);
        glBegin(GL_QUADS);
             glTexCoord2f(0.0, 0.0);
             glVertex2f(0.01, 0.03);

             glTexCoord2f(1.0, 0.0);
             glVertex2f(0.49, 0.03);

             glTexCoord2f(1.0, 1.0);
             glVertex2f(0.49, 0.49);

             glTexCoord2f(0.0, 1.0);
             glVertex2f(0.01, 0.49);
        glEnd();

        // Bottom right
        // Uncompressed - True colors - 32bpp
        glBindTexture(GL_TEXTURE_2D, texture_utc32_);
        glBegin(GL_QUADS);
             glTexCoord2f(0.0, 0.0);
             glVertex2f(0.51, 0.03);

             glTexCoord2f(1.0, 0.0);
             glVertex2f(0.99, 0.03);

             glTexCoord2f(1.0, 1.0);
             glVertex2f(0.99, 0.49);

             glTexCoord2f(0.0, 1.0);
             glVertex2f(0.51, 0.49);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
            glVertex2f(0.5, 0.0);
            glVertex2f(0.5, 1.0);

            glVertex2f(0.0, 0.5);
            glVertex2f(1.0, 0.5);
        glEnd();

        text_ctc24_.render();
        text_ctc32_.render();
        text_utc24_.render();
        text_utc32_.render();

        glPopMatrix();
    }

private:
    GLuint texture_ctc24_;
    GLuint texture_ctc32_;
    GLuint texture_utc24_;
    GLuint texture_utc32_;

    mengine::Text text_ctc24_;
    mengine::Text text_ctc32_;
    mengine::Text text_utc24_;
    mengine::Text text_utc32_;
};

int main( int argc, char** argv )
{
    mengine::Engine& engine = mengine::Engine::instance();

    engine.set_scene(new MyTestScene);

    engine.start();
  
    return EXIT_SUCCESS;
}

