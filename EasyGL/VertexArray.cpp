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

void VertexArray::unbind() noexcept
{
    glBindVertexArray(0);
}

void VertexArray::attribPointer(GLuint index, GLint size, GLenum type, bool normalized, GLsizei stride, const void *pointer) const noexcept
{
    this->bind();
    glVertexAttribPointer(index, size, type, static_cast<GLboolean>(normalized), stride, pointer);
    glEnableVertexAttribArray(index);
}

}; // namespace EasyGL