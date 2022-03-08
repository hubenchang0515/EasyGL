#ifndef EASYGL_VERTEX_BUFFER_H
#define EASYGL_VERTEX_BUFFER_H

#include <EasyGL/common.h>
#include <string>
#include <glad/glad.h>

namespace EasyGL
{

using std::string;

class VertexBuffer
{
public:
    ~VertexBuffer() noexcept;
    VertexBuffer() noexcept;

    GLuint id() const noexcept;
    void bind() const noexcept;
    void unbind() const noexcept;

private:
    std::shared_ptr<GLuint> m_id;

    static GLuint* generate() noexcept;
    static void deleter(GLuint* ptr) noexcept;

}; // class VertexBuffer
    
}; // namespace EasyGL


#endif // EASYGL_VERTEX_BUFFER_H