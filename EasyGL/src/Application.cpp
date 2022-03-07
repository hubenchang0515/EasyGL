#include <EasyGL/Application.h>

namespace EasyGL
{

/*****************************************************************************
 * @brief [static] init
 * @return true for success, false for failed
 * ***************************************************************************/
void Application::init() noexcept
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

/*****************************************************************************
 * @brief [static] terminate
 * ***************************************************************************/
void Application::terminate() noexcept
{
    glfwTerminate();
}
/*****************************************************************************
 * @brief [private static] framebuffer resize callback
 *        to resize the view port
 * ***************************************************************************/
void Application::m_framebufferResizeCallback(GLFWwindow* window, int width, int height) noexcept
{
    (void)(window);
    glViewport(0, 0, width, height);
}

Application::Application(const string& title, int width, int height) noexcept:
    m_window{glfwCreateWindow(width, height, title.c_str(), NULL, NULL), glfwDestroyWindow}
{
    glfwMakeContextCurrent(m_window.get());
    glfwSetFramebufferSizeCallback(m_window.get(), Application::m_framebufferResizeCallback);

    if (!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress))
    {
        ERROR("gladLoadGLLoader failed\n");
    }
}

Application::~Application() noexcept
{
    
}

void Application::clear(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) const noexcept
{
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

GLboolean Application::update() const noexcept
{
    glfwSwapBuffers(m_window.get());
    glfwPollEvents();
    return !glfwWindowShouldClose(m_window.get());
}

}; // namespace EasyGL