#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cassert>
#include <cstring>

#include <mengine/loaders/tga_loader.h>

void check_texture(const std::string& input, const std::string& output)
{
    mengine::TextureInfo ti;
    mengine::load_tga(input, ti);

    std::ifstream ifs(output.c_str(), std::ios::binary);

    std::size_t header_size = sizeof(ti.target) + sizeof(ti.level) +
                              sizeof(ti.internalFormat) + sizeof(ti.width) +
                              sizeof(ti.height) + sizeof(ti.format) +
                              sizeof(ti.type);
    std::size_t data_size = ti.width*ti.height*(ti.format==GL_RGBA?4:3);

    ifs.seekg(0, std::ios::end);
    std::size_t size = ifs.tellg();

    assert(size == header_size + data_size &&
           "error: reference and loaded tga have different sizes");
    ifs.seekg(0);
    
    GLenum   target;
    GLint    level;
    GLint    internalFormat;
    GLsizei  width;
    GLsizei  height;
    GLenum   format;
    GLenum   type;

    ifs.read((char*)&target,         sizeof(GLenum));
    ifs.read((char*)&level,          sizeof(GLint));
    ifs.read((char*)&internalFormat, sizeof(GLint));
    ifs.read((char*)&width,          sizeof(GLsizei));
    ifs.read((char*)&height,         sizeof(GLsizei));
    ifs.read((char*)&format,         sizeof(GLenum));
    ifs.read((char*)&type,           sizeof(GLenum));

    assert(ti.target         == target &&
           ti.level          == level &&
           ti.internalFormat == internalFormat &&
           ti.width          == width &&
           ti.height         == height &&
           ti.format         == format &&
           ti.type           == type &&
           "error: header reference and loaded are different");

    mengine::uint8_t* data = new uint8_t[data_size];
    ifs.read((char*)data, data_size);
    assert(std::memcmp(ti.data, data, data_size)==0 &&
           "error: data reference and data loaded are different");

    delete [] data;
    delete [] ti.data;
}

int main( int argc, char** argv )
{
    check_texture("tests/data/test_tga_ctc24.tga",
                  "tests/data/test_tga_ctc24.tga.out");

    check_texture("tests/data/test_tga_ctc32.tga",
                  "tests/data/test_tga_ctc32.tga.out");
    
    check_texture("tests/data/test_tga_utc24.tga",
                  "tests/data/test_tga_utc24.tga.out");
    
    check_texture("tests/data/test_tga_utc32.tga",
                  "tests/data/test_tga_utc32.tga.out");
  
    return EXIT_SUCCESS;
}

