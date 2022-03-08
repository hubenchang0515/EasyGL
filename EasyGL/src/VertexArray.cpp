#include <EasyGL/VertexArray.h>

namespace EasyGL
{

// private static 
GLuint* VertexArray::generate() noexcept
{
    GLuint* id = new GLuint{0};
    glGenVertexArrays(1, id);
    return id;
}

// private static 
void VertexArray::deleter(GLuint* ptr) noexcept
{
    glDeleteVertexArrays(1, ptr);
    delete ptr;
}

VertexArray::~VertexArray() noexcept
{

}

VertexArray::VertexArray() noexcept:
    m_id{VertexArray::generate(), VertexArray::deleter}
{
    INFO("VertexArray ID: %u\n", *m_id);
}

GLuint VertexArray::id() const noexcept
{
    return *m_id;
}

void VertexArray::bind() const noexcept
{
    glBindVertexArray(*m_id);
}

void VertexArray::unbind() const noexcept
{
    glBindVertexArray(0);
}

void VertexArray::setData(GLsizeiptr size, const void* data, Usage usage) const noexcept
{
    glBufferData(GL_ARRAY_BUFFER, size, data, static_cast<GLenum>(usage));
}

}; // namespace EasyGL