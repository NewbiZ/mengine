#ifndef MENGINE_LOADER_TGA_H
#define MENGINE_LOADER_TGA_H

#include <string>

#include <GL/glfw.h>

#include <mengine/mengine.h>

namespace mengine
{

struct TextureInfo
{
    GLenum   target;
    GLint    level;
    GLint    internalFormat;
    GLsizei  width;
    GLsizei  height;
    GLenum   format;
    GLenum   type;
    uint8_t* data;
};

void* load_tga(const std::string& filename, TextureInfo& ti);

} // end of namespace 'mengine'

#endif // MENGINE_LOADER_TGA_H

