#include <EasyGL/VertexBuffer.h>

namespace EasyGL
{

// private static 
GLuint VertexBuffer::generate() noexcept
{
    GLuint id;
    glGenBuffers(1, &id);
    return id;
}

// private static 
void VertexBuffer::deleter(GLuint* ptr) noexcept
{
    glDeleteBuffers(1, ptr);
    delete ptr;
}

VertexBuffer::~VertexBuffer() noexcept
{

}

VertexBuffer::VertexBuffer() noexcept:
    m_id{new GLuint{VertexBuffer::generate()}, VertexBuffer::deleter}
{
    INFO("VertexBuffer ID: %u\n", *m_id);
}

GLuint VertexBuffer::id() const noexcept
{
    return *m_id;
}

void VertexBuffer::bind() const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, *m_id);
}

void VertexBuffer::unbind() const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}; // namespace EasyGL