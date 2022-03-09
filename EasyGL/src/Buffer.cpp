#include <EasyGL/Buffer.h>

namespace EasyGL
{

// private static 
GLuint* Buffer::generate() noexcept
{
    GLuint* id = new GLuint{0};
    glGenBuffers(1, id);
    return id;
}

// private static 
void Buffer::deleter(GLuint* ptr) noexcept
{
    glDeleteBuffers(1, ptr);
    delete ptr;
}

Buffer::~Buffer() noexcept
{

}

Buffer::Buffer(Type type) noexcept:
    m_type(type),
    m_id{Buffer::generate(), Buffer::deleter}
{
    INFO("Buffer ID: %u\n", *m_id);
}

GLuint Buffer::id() const noexcept
{
    return *m_id;
}

void Buffer::bind() const noexcept
{
    glBindBuffer(static_cast<GLenum>(m_type), *m_id);
}

void Buffer::unbind() const noexcept
{
    glBindBuffer(static_cast<GLenum>(m_type), 0);
}

// static 
void Buffer::unbind(Type type) noexcept
{
    glBindBuffer(static_cast<GLenum>(type), 0);
}

void Buffer::setData(GLsizeiptr size, const void* data, Usage usage) const noexcept
{
    this->bind();
    glBufferData(static_cast<GLenum>(m_type), size, data, static_cast<GLenum>(usage));
}

}; // namespace EasyGL