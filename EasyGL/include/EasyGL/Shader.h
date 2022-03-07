#ifndef EASYGL_SHADER_H
#define EASYGL_SHADER_H

#include <EasyGL/common.h>
#include <string>
#include <glad/glad.h>

namespace EasyGL
{

using std::string;

class Shader
{
public:
    enum class Type
    {
        VertexShader = GL_VERTEX_SHADER,
        GeometryShader = GL_GEOMETRY_SHADER,
        FragmentShader = GL_FRAGMENT_SHADER,
    };
    ~Shader() noexcept;
    Shader(Type type, const string& src) noexcept;

    GLuint id() const noexcept;

private:
    std::shared_ptr<GLuint> m_id;

    static void deleter(GLuint* ptr) noexcept;
}; // class Shader
    
}; // namespace EasyGL


#endif // EASYGL_SHADER_H