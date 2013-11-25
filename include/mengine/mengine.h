#ifndef MENGINE_H
#define MENGINE_H

#include <GL/glfw.h>

namespace mengine
{

typedef GLfloat vec2f_t[2];
typedef GLfloat vec3f_t[3];
typedef GLfloat vec4f_t[4];

typedef   signed char int8_t;
typedef unsigned char uint8_t;

typedef   signed short int16_t;
typedef unsigned short uint16_t;

typedef   signed int int32_t;
typedef unsigned int uint32_t;

typedef   signed long long int64_t;
typedef unsigned long long uint64_t;

typedef float  float32_t;
typedef double float64_t;

} // end of namespace 'mengine'

#include <mengine/config.h>

#endif // MENGINE_H

