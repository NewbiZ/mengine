#include <mengine/engine/clickable.h>

#include <iostream>
#include <cstdlib>
#include <cstring>

namespace mengine
{

Clickable::Clickable()   
{   
}


Clickable::~Clickable()
{
}

void Clickable::resize(float scale)
{
    //TODO
}

void Clickable::set_height(float height)
{
    height_ = height;
}

void Clickable::set_width(float width)
{
    width_ = width;
}

void Clickable::set_text(const std::string& text)
{
    textItem_.set_text(text);
}

void Clickable::set_color(float r, float g, float b)
{
  color_[0] = r;
  color_[1] = g;
  color_[2] = b;
}

void Clickable::set_text_color(float r, float g, float b)
{
    textItem_.set_color(r, g, b);
}

void Clickable::set_position(float x, float y)
{
    position_[0] = x;
    position_[1] = y;
}

const float Clickable::width() const
{
    return width_;
}

const float Clickable::height() const
{
    return height_;
}

const std::string& Clickable::text() const
{
    return textItem_.text();
}

const vec3f_t& Clickable::color() const
{
    return color_;
}

const vec3f_t& Clickable::text_color() const
{
    return textItem_.color();
}

const vec2f_t& Clickable::position() const
{
    return position_;
}

const vec2f_t& Clickable::text_position() const
{
    return textItem_.position();
}

/*
void Clickable::render() const
{
    textItem_.render();    
}*/

} // end of namespace 'mengine'

