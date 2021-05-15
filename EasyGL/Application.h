#ifndef EASYGL_APPLICATION_H
#define EASYGL_APPLICATION_H

#include <EasyGL/base.h>

namespace EasyGL
{

class Application
{
public:
    static Application& instance() noexcept;
    static void enable(int e) noexcept;
    static void disable(int e) noexcept;
    static double getTime() noexcept;
    static void setTime(double time) noexcept;
    static void sleep(double seconds) noexcept;

    ~Application() noexcept;
    Application(const Application&) noexcept = default;
    Application(Application&&) noexcept = default;

private:
    static bool m_init;
    static void init() noexcept;
    static void terminate() noexcept;
    Application() noexcept;
};
    
}; // namespace EasyGL

#endif // EASYGL_APPLICATION_H