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
    m_id{Texture::generate(), Texture::deleter}
{

}

}; // namespace EasyGL