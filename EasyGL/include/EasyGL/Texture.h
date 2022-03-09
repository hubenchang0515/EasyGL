#ifndef EASYGL_TEXTURE_H
#define EASYGL_TEXTURE_H

#include <EasyGL/common.h>
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

    Texture() noexcept;

    GLuint id() const noexcept;
    void bind(Target target) noexcept;
    void unbind() noexcept;
    static void unbind(Target target) noexcept;

private:
    Target m_target;
    std::shared_ptr<GLuint> m_id;

    static GLuint* generate() noexcept;
    static void deleter(GLuint* ptr) noexcept;
}; // class Texture

}; // namespace EasyGL

#endif // EASYGL_TEXTURE_H