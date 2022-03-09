#include <EasyGL/Texture.h>

namespace EasyGL
{
// private static 
GLuint* Texture::generate() noexcept
{
    GLuint* id = new GLuint{0};
    glGenTextures(1, id);
    return id;
}

// private static 
void Texture::deleter(GLuint* ptr) noexcept
{
    glDeleteTextures(1, ptr);
    delete ptr;
}

Texture::Texture() noexcept:
    m_target{Target::None},
    m_id{Texture::generate(), Texture::deleter}
{
    INFO("Texture ID: %u\n", *m_id);
}

GLuint Texture::id() const noexcept
{
    return *m_id;
}

void Texture::bind(Target target) noexcept
{
    glBindTexture(static_cast<GLenum>(target), *m_id);
    m_target = target;
}

void Texture::unbind() noexcept
{
    glBindTexture(static_cast<GLenum>(m_target), *m_id);
    m_target = Target::None;
}

// static
void Texture::unbind(Target target) noexcept
{
    glBindTexture(static_cast<GLenum>(target), 0);
}

}; // namespace EasyGL