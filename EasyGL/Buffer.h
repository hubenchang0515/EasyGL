#ifndef EASYGL_BUFFER_H
#define EASYGL_BUFFER_H

#include <EasyGL/base.h>
#include <string>
#include <functional>

namespace EasyGL
{

using std::string;

class Buffer
{
public:
    enum class Type
    {
        Array = GL_ARRAY_BUFFER,
        ElementArray = GL_ELEMENT_ARRAY_BUFFER,
    };

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

    ~Buffer() noexcept;
    Buffer(Type type) noexcept;

    GLuint id() const noexcept;
    void bind() const noexcept;
    void unbind() const noexcept;
    static void unbind(Type type) noexcept;
    void setData(GLsizeiptr size, const void* data, Usage usage) const noexcept;

private:
    Type m_type;
    std::shared_ptr<GLuint> m_id;

    static GLuint* generate() noexcept;
    static void deleter(GLuint* ptr) noexcept;

}; // class Buffer

template<Buffer::Type type>
struct SpecificBuffer : public Buffer
{
    SpecificBuffer() noexcept : Buffer(type){}
};

using VertexBuffer = SpecificBuffer<Buffer::Type::Array>;
using IndexBuffer = SpecificBuffer<Buffer::Type::ElementArray>;
using ElementBuffer = IndexBuffer;

using VBO = VertexBuffer;
using IBO = IndexBuffer;
using EBO = ElementBuffer;

}; // namespace EasyGL


#endif // EASYGL_BUFFER_H