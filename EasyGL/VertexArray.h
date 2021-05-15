#ifndef EASYGL_VERTEX_ARRAY_H
#define EASYGL_VERTEX_ARRAY_H

#include <EasyGL/base.h>
#include <string>

namespace EasyGL
{

using std::string;

class VertexArray
{
public:
    ~VertexArray() noexcept;
    VertexArray() noexcept;

    GLuint id() const noexcept;
    void bind() const noexcept;
    static void unbind() noexcept;
    void attribPointer(GLuint index, GLint size, GLenum type, bool normalized, GLsizei stride, const void *pointer) const noexcept;

private:
    std::shared_ptr<GLuint> m_id;

    static GLuint* generate() noexcept;
    static void deleter(GLuint* ptr) noexcept;

}; // class VertexArray

using VAO = VertexArray;
    
}; // namespace EasyGL


#endif // EASYGL_VERTEX_ARRAY_H