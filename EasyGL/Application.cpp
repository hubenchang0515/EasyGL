#include <EasyGL/Application.h>
#include <thread>
#include <chrono>

namespace EasyGL
{

#ifndef EASYGL_USE_BETTER_GPU
#define EASYGL_USE_BETTER_GPU 1
#endif // EASYGL_USE_BETTER_GPU

#ifdef __cplusplus
extern "C" {
#endif

EASYGL_EXPORT uint32_t NvOptimusEnablement = EASYGL_USE_BETTER_GPU;
EASYGL_EXPORT int AmdPowerXpressRequestHighPerformance = EASYGL_USE_BETTER_GPU;

#ifdef __cplusplus
}
#endif

// private static 
bool Application::m_init = false;

// static 
Application& Application::instance() noexcept
{
    static Application app;
    return app;
}

// private static 
void Application::init() noexcept
{
    if (!m_init)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        m_init = true;
    }
}

// private static 
void Application::terminate() noexcept
{
    if (m_init)
    {
        glfwTerminate();
        m_init = false;
    }
}

// static 
void Application::enable(int e) noexcept
{
    glEnable(e);
}

// static 
void Application::disable(int e) noexcept
{
    glDisable(e);
}

// static 
double Application::getTime() noexcept
{
    return glfwGetTime();
}

// static 
void Application::setTime(double time) noexcept
{
    glfwSetTime(time);
}

// static 
void Application::sleep(double seconds) noexcept
{
    std::this_thread::sleep_for(std::chrono::duration<double>(seconds));
}

// private
Application::Application() noexcept
{ 
    Application::init();
}

Application::~Application() noexcept
{
    Application::terminate();
}

}; // namespace EasyGL