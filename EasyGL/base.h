#ifndef EASYGL_LOG_HPP
#define EASYGL_LOG_HPP

#include <cstdio>
#include <cstdlib>
#include <memory>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <EasyGL/log.h>

namespace EasyGL
{

#ifdef _MSC_VER
    #define EASYGL_EXPORT __declspec(dllexport)
    #define EASYGL_IMPORT __declspec(dllimport)
#else
    #define EASYGL_EXPORT
    #define EASYGL_IMPORT
#endif // _MSC_VER

#ifdef EASYGL_BUILD_LIB
    #define EASYGL_API EASYGL_EXPORT
#else
    #define EASYGL_API EASYGL_IMPORT
#endif

#ifndef EASYGL_TEMP_BUFF_MAX
    #define EASYGL_TEMP_BUFF_MAX 256
#endif // EASYGL_TEMP_BUFF_MAX

} // namespace EasyGL

#endif // EASYGL_LOG_HPP