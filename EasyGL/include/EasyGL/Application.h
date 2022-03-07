#ifndef EASYGL_APPLICATION_H
#define EASYGL_APPLICATION_H

#include <EasyGL/common.h>
#include <string>

namespace EasyGL
{

using std::string;

class Application
{
public:
    static void init() noexcept;
    static void terminate() noexcept;

    ~Application() noexcept;
    Application(const string& title, int width, int height) noexcept;
    Application(const Application&) = delete;
    Application(Application&&) = delete;

    void clear(GLfloat red=0.0f, GLfloat green=0.0f, GLfloat blue=0.0f, GLfloat alpha=0.0f) const noexcept;
    GLboolean update() const noexcept;

private:
    std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)> m_window;

    static void m_framebufferResizeCallback(GLFWwindow* window, int width, int height) noexcept;
}; // class Application

}; // namespace EasyGL

#endif // EASYGL_APPLICATION_H