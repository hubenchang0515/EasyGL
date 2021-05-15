#ifndef EASYGL_WINDOW_H
#define EASYGL_WINDOW_H

#include <EasyGL/base.h>
#include <string>

namespace EasyGL
{

using std::string;

class Window
{
public:
    using MouseHandler = std::function<void(Window&, double, double)>;

    ~Window() noexcept;
    Window(const string& title, int width, int height) noexcept;
    Window(const Window&) = delete;
    Window(Window&&) = delete;

    GLFWwindow* id() const noexcept;
    void makeCurrent() const noexcept;
    void clear(float red=0.0f, float green=0.0f, float blue=0.0f, float alpha=0.0f) const noexcept;
    void update(double fps=60.0) noexcept;
    bool shouldClose() const noexcept;
    int width() const noexcept;
    int height() const noexcept;
    void* userData() const noexcept;
    void setUserData(void* userdata) noexcept;
    int getKey(int key) const noexcept;
    void getCursorPos(double* x, double* y) const noexcept;
    void setCursorPos(double x, double y) const noexcept;
    void captureCursor(bool enable) const noexcept;
    void setMouseMoveCallback(MouseHandler callback) noexcept;
    void setMouseScrollCallback(MouseHandler callback) noexcept;

private:
    std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)> m_window;
    double m_updateTime;
    void* m_userData;
    MouseHandler m_mouseMoveCallback;
    MouseHandler m_mouseScrollCallback;

    static GLFWwindow* generate(const string& title, int width, int height) noexcept;
    static void deleter(GLFWwindow* ptr) noexcept;
    static void resizeCallback(GLFWwindow* window, int width, int height) noexcept;
}; // class Window

}; // namespace EasyGL

#endif // EASYGL_WINDOW_H