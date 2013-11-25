#ifndef MENGINE_TEXT_H
#define MENGINE_TEXT_H

#include <string>

#include <GL/glfw.h>

#include <mengine/mengine.h>

namespace mengine
{

class Text
{

public:
    Text(); 
    Text(const std::string& text); 
    ~Text();

public:
    void resize(float size);
    void set_text(const std::string& text);
    void set_color(float r, float g, float b);
    void set_position(float x, float y);

public:
    const float        size() const;
    const std::string& text() const;
    const vec3f_t&     color() const;
    const vec2f_t&     position() const;

public:
    void render(bool with_shadow=true) const;

private:
    vec2f_t     position_;
    vec3f_t     color_;
    float       size_;
    std::string text_;   
    
};

} // end of namespace 'mengine'

#endif // MENGINE_TEXT_H

