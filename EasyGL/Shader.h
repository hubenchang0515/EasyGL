#ifndef EASYGL_SHADER_H
#define EASYGL_SHADER_H

#include <EasyGL/base.h>
#include <string>

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

    static GLuint* generate(Type type) noexcept;
    static void deleter(GLuint* ptr) noexcept;
}; // class Shader

template<Shader::Type type>
struct SpecificShader : public Shader
{
    SpecificShader(const string& src) noexcept : Shader(type, src){}
};

using VertexShader = SpecificShader<Shader::Type::VertexShader>;
using GeometryShader = SpecificShader<Shader::Type::GeometryShader>;
using FragmentShader = SpecificShader<Shader::Type::FragmentShader>;
    
}; // namespace EasyGL


#endif // EASYGL_SHADER_H