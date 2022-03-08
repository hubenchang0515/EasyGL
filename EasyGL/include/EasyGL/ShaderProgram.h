#ifndef EASYGL_SHADER_PROGRAM_H
#define EASYGL_SHADER_PROGRAM_H

#include <EasyGL/common.h>
#include <EasyGL/Shader.h>
#include <map>

namespace EasyGL
{

using std::map;

class ShaderProgram
{
public:
    ~ShaderProgram() noexcept;
    ShaderProgram() noexcept;

    GLuint id() const noexcept;
    void attach(Shader& shader) noexcept;
    void link() const noexcept;
    void use() const noexcept;

private:
    std::shared_ptr<GLuint> m_id;
    map<GLuint, Shader> m_shaders;

    static GLuint* generate() noexcept;
    static void deleter(GLuint* ptr) noexcept;

}; // class ShaderProgram
    
}; // namespace EasyGL


#endif // EASYGL_SHADER_H