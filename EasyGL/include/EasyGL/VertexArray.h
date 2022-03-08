#ifndef EASYGL_VERTEX_ARRAY_H
#define EASYGL_VERTEX_ARRAY_H

#include <EasyGL/common.h>
#include <EasyGL/VertexBuffer.h>
#include <string>

namespace EasyGL
{

using std::string;

class VertexArray
{
public:
    enum class Usage
    {
        StreamDraw  = GL_STREAM_DRAW,
        StreamRead  = GL_STREAM_READ,
        StreamCopy  = GL_STREAM_COPY,
        StaticDraw  = GL_STATIC_DRAW,
        StaticRead  = GL_STATIC_READ,
        StaticCopy  = GL_STATIC_COPY,
        DynamicDraw = GL_DYNAMIC_DRAW,
        DynamicRead = GL_DYNAMIC_READ,
        DynamicCopy = GL_DYNAMIC_COPY,
    };

    ~VertexArray() noexcept;
    VertexArray() noexcept;

    GLuint id() const noexcept;
    void bind() const noexcept;
    void unbind() const noexcept;
    void setData(GLsizeiptr size, const void* data, Usage usage) const noexcept;

private:
    std::shared_ptr<GLuint> m_id;

    static GLuint* generate() noexcept;
    static void deleter(GLuint* ptr) noexcept;

}; // class VertexArray
    
}; // namespace EasyGL


#endif // EASYGL_VERTEX_ARRAY_H