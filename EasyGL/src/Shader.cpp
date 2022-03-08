#include <EasyGL/Shader.h>

namespace EasyGL
{

// private static 
GLuint* Shader::generate(Type type) noexcept
{
    return new GLuint{glCreateShader(static_cast<GLenum>(type))};
}

// private static 
void Shader::deleter(GLuint* ptr) noexcept
{
    glDeleteShader(*ptr); 
    delete ptr;
}
    
Shader::~Shader() noexcept
{

}

Shader::Shader(Type type, const string& src) noexcept:
    m_id{Shader::generate(type), Shader::deleter}
{
    INFO("Shader ID: %u\n", *m_id);
    const char * const ptr = src.data();
    glShaderSource(*m_id, 1, &ptr, NULL);
    glCompileShader(*m_id);

    int success;
    glGetShaderiv(*m_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char info[EASYGL_TEMP_BUFF_MAX];
        glGetShaderInfoLog(*m_id, EASYGL_TEMP_BUFF_MAX, NULL, info);
        ERROR("%s\n", info);
    }
}

GLuint Shader::id() const noexcept
{
    return *m_id;
}

}; // namespace EasyGL
