#ifndef EASYGL_TEXTURE_H
#define EASYGL_TEXTURE_H

#include <EasyGL/base.h>
namespace EasyGL
{

class Texture
{
public:
    enum class Target
    {
        None = 0,
        Texture1D = GL_TEXTURE_1D,
        Texture2D = GL_TEXTURE_2D,
        Texture3D = GL_TEXTURE_3D,
    };

    enum class Wrap
    {
        Repeat = GL_REPEAT,
        MirrorRepeat = GL_MIRRORED_REPEAT,
        ClampEdge = GL_CLAMP_TO_EDGE,
        ClampBorder = GL_CLAMP_TO_BORDER,
    };

    enum class PixelFormat
    {
        RGB = GL_RGB,
        BGR = GL_BGR,
        RGBA = GL_RGBA,
        BGRA = GL_BGRA,
    };

    enum class PixelType
    {
        Byte = GL_BYTE,
        UByte = GL_UNSIGNED_BYTE,
        Short = GL_SHORT,
        UShort = GL_UNSIGNED_SHORT,
        Int = GL_INT,
        UInt = GL_UNSIGNED_INT,
        Float = GL_FLOAT,
        Double = GL_DOUBLE,
    };

    enum class FilterType
    {
        Minify = GL_TEXTURE_MIN_FILTER,
        Magnify = GL_TEXTURE_MAG_FILTER,
    };

    enum class FilterMethod
    {
        Nearest = GL_NEAREST,
        Linear = GL_LINEAR,
    };

    enum class WrapAxis
    {
        S = GL_TEXTURE_WRAP_S,
        T = GL_TEXTURE_WRAP_T,
        R = GL_TEXTURE_WRAP_R,

        X = S,
        Y = T,
        Z = R,
    };

    enum class WrapMethod
    {
        Repeat = GL_REPEAT,
        Mirror = GL_MIRRORED_REPEAT,
        ClampToEdge = GL_CLAMP_TO_EDGE,
        ClampToBorder = GL_CLAMP_TO_BORDER,
    };

    ~Texture() noexcept;
    Texture() noexcept;

    GLuint id() const noexcept;
    void bind(Target target) noexcept;
    void unbind() noexcept;
    static void unbind(Target target) noexcept;

    void setFilterMethod2D(FilterType type, FilterMethod method) noexcept;
    void setWrapMethod2D(WrapAxis axis, WrapMethod method) noexcept;
    void setImage2D(int width, int height, PixelFormat format, PixelType type, const void * pixels) noexcept;

private:
    Target m_target;
    std::shared_ptr<GLuint> m_id;

    static GLuint* generate() noexcept;
    static void deleter(GLuint* ptr) noexcept;
}; // class Texture

}; // namespace EasyGL

#endif // EASYGL_TEXTURE_H