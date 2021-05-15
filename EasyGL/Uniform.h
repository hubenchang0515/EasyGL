#ifndef EASYGL_UNIFORM_SETTER_HPP
#define EASYGL_UNIFORM_SETTER_HPP

#include <EasyGL/base.h>
#include <string>

namespace EasyGL
{

template<typename... T>
struct ValueUniformSetter{};

template<int N, typename T>
struct VectorUniformSetter{};

template<int R, int C, typename T>
struct MatrixUniformSetter{};

template<typename... T>
struct Uniform
{
    static GLint getLocation(GLuint programId, const std::string& name)
    {
        return glGetUniformLocation(programId, name.c_str());
    }

    template<typename... Args>
    static void set(GLint location, Args&&... value)
    {
        (*ValueUniformSetter<Args...>::setter)(location, value...);
    }

    template<typename... Args>
    static void set(GLuint programId, const std::string& name, Args&&... value)
    {
        (*ValueUniformSetter<Args...>::setter)(getLocation(programId, name), value...);
    }
};

template<int N, typename T>
struct VectorUniform
{
    static GLint getLocation(GLuint programId, const std::string& name)
    {
        return glGetUniformLocation(programId, name.c_str());
    }

    static void set(GLint location, GLsizei count, const T* ptr)
    {
        (*VectorUniformSetter<N, T>::setter)(location, count, ptr);
    }

    static void set(GLuint programId, const std::string& name, GLsizei count, const T* ptr)
    {
        set(getLocation(programId, name), count, ptr);
    }
};

template<int R, int C, typename T>
struct MatrixUniform
{
    static GLint getLocation(GLuint programId, const std::string& name)
    {
        return glGetUniformLocation(programId, name.c_str());
    }

    static void set(GLint location, GLsizei count, GLboolean transpose, const T* ptr)
    {
        (*MatrixUniformSetter<R, C, T>::setter)(location, count, transpose, ptr);
    }

    static void set(GLuint programId, const std::string& name, GLsizei count, GLboolean transpose, const T* ptr)
    {
        set(getLocation(programId, name), count, transpose, ptr);
    }

    static void set(GLuint programId, const std::string& name, GLsizei count, const T* ptr)
    {
        set(programId, name, count, GL_FALSE, ptr);
    }

    static void set(GLuint programId, const std::string& name, const T* ptr)
    {
        set(programId, name, 1, GL_FALSE, ptr);
    }
};

template<>
struct ValueUniformSetter<GLint>
{
    constexpr static auto setter = &glUniform1i;
};

template<>
struct ValueUniformSetter<GLint, GLint>
{
    constexpr static auto setter = &glUniform2i;
};

template<>
struct ValueUniformSetter<GLint, GLint, GLint>
{
    constexpr static auto setter = &glUniform3i;
};

template<>
struct ValueUniformSetter<GLint, GLint, GLint, GLint>
{
    constexpr static auto setter = &glUniform4i;
};

template<>
struct ValueUniformSetter<GLfloat>
{
    constexpr static auto setter = &glUniform1f;
};

template<>
struct ValueUniformSetter<GLfloat, GLfloat>
{
    constexpr static auto setter = &glUniform2f;

};

template<>
struct ValueUniformSetter<GLfloat, GLfloat, GLfloat>
{
    constexpr static auto setter = &glUniform3f;

};

template<>
struct ValueUniformSetter<GLfloat, GLfloat, GLfloat, GLfloat>
{
    constexpr static auto setter = &glUniform4f;
};

template<>
struct VectorUniformSetter<1, GLint>
{
    constexpr static auto setter = &glUniform1iv;
};

template<>
struct VectorUniformSetter<2, GLint>
{
    constexpr static auto setter = &glUniform2iv;
};

template<>
struct VectorUniformSetter<3, GLint>
{
    constexpr static auto setter = &glUniform3iv;
};

template<>
struct VectorUniformSetter<4, GLint>
{
    constexpr static auto setter = &glUniform4iv;
};

template<>
struct VectorUniformSetter<1, GLfloat>
{
    constexpr static auto setter = &glUniform1fv;
};

template<>
struct VectorUniformSetter<2, GLfloat>
{
    constexpr static auto setter = &glUniform2fv;
};

template<>
struct VectorUniformSetter<3, GLfloat>
{
    constexpr static auto setter = &glUniform3fv;
};

template<>
struct VectorUniformSetter<4, GLfloat>
{
    constexpr static auto setter = &glUniform4fv;
};

template<>
struct MatrixUniformSetter<2, 2, GLfloat>
{
    constexpr static auto setter = &glUniformMatrix2fv;
};

template<>
struct MatrixUniformSetter<2, 3, GLfloat>
{
    constexpr static auto setter = &glUniformMatrix2x3fv;
};

template<>
struct MatrixUniformSetter<2, 4, GLfloat>
{
    constexpr static auto setter = &glUniformMatrix2x4fv;
};

template<>
struct MatrixUniformSetter<3, 3, GLfloat>
{
    constexpr static auto setter = &glUniformMatrix3fv;
};

template<>
struct MatrixUniformSetter<3, 2, GLfloat>
{
    constexpr static auto setter = &glUniformMatrix3x2fv;
};

template<>
struct MatrixUniformSetter<3, 4, GLfloat>
{
    constexpr static auto setter = &glUniformMatrix3x4fv;
};

template<>
struct MatrixUniformSetter<4, 4, GLfloat>
{
    constexpr static auto setter = &glUniformMatrix4fv;
};

template<>
struct MatrixUniformSetter<4, 3, GLfloat>
{
    constexpr static auto setter = &glUniformMatrix4x3fv;
};

template<>
struct MatrixUniformSetter<4, 2, GLfloat>
{
    constexpr static auto setter = &glUniformMatrix4x2fv;
};

}; // namespace EasyGL

#endif // EASYGL_UNIFORM_SETTER_HPP