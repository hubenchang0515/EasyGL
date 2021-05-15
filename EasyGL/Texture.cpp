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

Texture::~Texture() noexcept
{

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
    glBindTexture(static_cast<GLenum>(m_target), 0);
    m_target = Target::None;
}

// static
void Texture::unbind(Target target) noexcept
{
    glBindTexture(static_cast<GLenum>(target), 0);
}


void Texture::setFilterMethod2D(FilterType type, FilterMethod method) noexcept
{
    bind(Target::Texture2D);
    glTexParameteri(GL_TEXTURE_2D, static_cast<GLenum>(type), static_cast<GLint>(method));
}

void Texture::setWrapMethod2D(WrapAxis axis, WrapMethod method) noexcept
{
    bind(Target::Texture2D);
    glTexParameteri(GL_TEXTURE_2D, static_cast<GLenum>(axis), static_cast<GLint>(method));
}

void Texture::setImage2D(int width, int height, PixelFormat format, PixelType type, const void * pixels) noexcept
{
    bind(Target::Texture2D);
    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLenum>(format), width, height, 0, static_cast<GLenum>(format), static_cast<GLenum>(type), pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
}

}; // namespace EasyGL