#include <EasyGL/Window.h>
#include <EasyGL/Application.h>

namespace EasyGL
{

// static 
GLFWwindow* Window::generate(const string& title, int width, int height) noexcept
{
    static Application app = Application::instance();
    return glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
}

// static 
void Window::deleter(GLFWwindow* window) noexcept
{
    glfwDestroyWindow(window);
}

// static
void Window::resizeCallback(GLFWwindow* window, int width, int height) noexcept
{
    if (window == glfwGetCurrentContext())
        glViewport(0, 0, width, height);
}

Window::Window(const string& title, int width, int height) noexcept:
    m_window{generate(title, width, height), deleter},
    m_updateTime{0.0},
    m_userData{nullptr},
    m_mouseMoveCallback{nullptr},
    m_mouseScrollCallback{nullptr}
{
    if (m_window == nullptr)
    {
        ERROR("failed to create window\n");
        return;
    }

    INFO("Window ID: %p\n", m_window.get());
    glfwMakeContextCurrent(m_window.get());
    glfwSetFramebufferSizeCallback(m_window.get(), Window::resizeCallback);

    if (gladLoadGL(glfwGetProcAddress) == 0)
    {
        ERROR("gladLoadGLLoader failed\n");
    }

    glfwSetWindowUserPointer(m_window.get(), this);
}

Window::~Window() noexcept
{
    
}


GLFWwindow* Window::id() const noexcept
{
    return m_window.get();
}

void Window::makeCurrent() const noexcept
{
    glfwMakeContextCurrent(m_window.get());
    int width, height;
    glfwGetWindowSize(m_window.get(), &width, &height);
    glViewport(0, 0, width, height);
}

void Window::clear(float red, float green, float blue, float alpha) const noexcept
{
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update(double fps) noexcept
{
    if (Application::getTime() < m_updateTime)
    {
        Application::sleep(m_updateTime - Application::getTime());
    }
    glfwSwapBuffers(m_window.get());
    glfwPollEvents();
    m_updateTime += 1.0 / fps;
}

bool Window::shouldClose() const noexcept
{
    return glfwWindowShouldClose(m_window.get());
}


int Window::width() const noexcept
{
    int w, h;
    glfwGetWindowSize(m_window.get(), &w, &h);
    return w;
}

int Window::height() const noexcept
{
    int w, h;
    glfwGetWindowSize(m_window.get(), &w, &h);
    return h;
}


void* Window::userData() const noexcept
{
    
    return m_userData;
}


void Window::setUserData(void* userdata) noexcept
{
    m_userData = userdata;
}

void Window::getCursorPos(double* x, double* y) const noexcept
{
    glfwGetCursorPos(m_window.get(), x, y);
}

void Window::setCursorPos(double x, double y) const noexcept
{
    glfwSetCursorPos(m_window.get(), x, y);
}

int Window::getKey(int key) const noexcept
{
    return glfwGetKey(m_window.get(), key);
}


void Window::captureCursor(bool enable) const noexcept
{
    glfwSetInputMode(m_window.get(), GLFW_CURSOR, enable ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void Window::setMouseMoveCallback(MouseHandler callback) noexcept
{
    m_mouseMoveCallback = callback;
    if (m_mouseMoveCallback == nullptr)
    {
        glfwSetCursorPosCallback(m_window.get(), nullptr);
        return;
    }

    glfwSetCursorPosCallback(m_window.get(), [](GLFWwindow* window, double x, double y){
        Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (self == nullptr)
        {
            ERROR("Window is nullptr\n");
            return;
        }

        self->m_mouseMoveCallback(*self, x, y);
    });
}

void Window::setMouseScrollCallback(MouseHandler callback) noexcept
{
    m_mouseScrollCallback = callback;
    if (m_mouseScrollCallback == nullptr)
    {
        glfwSetScrollCallback(m_window.get(), nullptr);
        return;
    }

    glfwSetScrollCallback(m_window.get(), [](GLFWwindow* window, double dx, double dy){
        Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (self == nullptr)
        {
            ERROR("Window is nullptr\n");
            return;
        }


        self->m_mouseScrollCallback(*self, dx, dy);
    });
}

}; // namespace EasyGL