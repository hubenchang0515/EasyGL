#ifndef EASYGL_SHADER_PROGRAM_H
#define EASYGL_SHADER_PROGRAM_H

#include <EasyGL/base.h>
#include <EasyGL/Shader.h>
#include <EasyGL/Uniform.h>
#include <map>

namespace EasyGL
{

using std::map;

class ShaderProgram
{
public:
    ~ShaderProgram() noexcept;
    ShaderProgram() noexcept;

    GLuint id() const noexcept;
    void attach(Shader& shader) noexcept;
    void link() const noexcept;
    void use() const noexcept;
    
    template<typename... T>
    void setValue(const std::string& name, T&&... value...)
    {
        Uniform<T...>::set(id(), name, value...);
    }

    template<int N, typename T>
    void setVector(const std::string& name, const T* ptr)
    {
        VectorUniform<N,T>::set(id(), name, 1, ptr);
    }

    template<int N, typename T>
    void setVector(const std::string& name, size_t count, const T* ptr)
    {
        VectorUniform<N,T>::set(id(), name, count, ptr);
    }

    template<int R, int C=R, typename T>
    void setMatrix(const std::string& name, GLsizei count, GLboolean transpose, const T* ptr)
    {
        MatrixUniform<R,C,T>::set(id(), name, count, transpose, ptr);
    }

    template<int R, int C=R, typename T>
    void setMatrix(const std::string& name, GLsizei count, const T* ptr)
    {
        MatrixUniform<R,C,T>::set(id(), name, count, ptr);
    }

    template<int W, int H=W, typename T>
    void setMatrix(const std::string& name, const T* ptr)
    {
        MatrixUniform<W,H,T>::set(id(), name, ptr);
    }

private:
    std::shared_ptr<GLuint> m_id;
    map<GLuint, Shader> m_shaders;

    static GLuint* generate() noexcept;
    static void deleter(GLuint* ptr) noexcept;

}; // class ShaderProgram
    
}; // namespace EasyGL


#endif // EASYGL_SHADER_H