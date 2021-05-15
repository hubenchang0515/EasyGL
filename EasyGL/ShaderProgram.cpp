#include <EasyGL/ShaderProgram.h>

namespace EasyGL
{

// private static 
GLuint* ShaderProgram::generate() noexcept
{
    return new GLuint{glCreateProgram()};
}

// private static 
void ShaderProgram::deleter(GLuint* ptr) noexcept
{
    glDeleteProgram(*ptr); 
    delete ptr;
}

ShaderProgram::~ShaderProgram() noexcept
{

}

ShaderProgram::ShaderProgram() noexcept:
    m_id(ShaderProgram::generate(), ShaderProgram::deleter)
{
    INFO("ShaderProgram ID: %u\n", *m_id);
}

GLuint ShaderProgram::id() const noexcept
{
    return *m_id;
}

void ShaderProgram::attach(Shader& shader) noexcept
{
    glAttachShader(*m_id, shader.id());
    m_shaders.emplace(shader.id(), shader);
}

void ShaderProgram::link() const noexcept
{
    glLinkProgram(*m_id);

    int success;
    glGetProgramiv(*m_id, GL_LINK_STATUS, &success);
    if (!success) {
        char info[EASYGL_TEMP_BUFF_MAX];
        glGetProgramInfoLog(*m_id, EASYGL_TEMP_BUFF_MAX, NULL, info);
        ERROR("%s\n", info);
    }
}

void ShaderProgram::use() const noexcept
{
    glUseProgram(*m_id);
}

}; // namespace EasyGL
