#ifndef EASYGL_CAMERA_H
#define EASYGL_CAMERA_H

#include <EasyGL/base.h>
#include <EasyGL/Application.h>
#include <EasyGL/Window.h>
#include <functional>

namespace EasyGL
{

class Camera
{
public:
    using KeyInputHandler = std::function<void(Camera&, Window&, float)>;
    using MouseHandler = std::function<void(Camera&, float, float)>;

    ~Camera() noexcept;
    Camera(glm::vec3 pos=glm::vec3{0.0f, 0.0f, 0.0f}) noexcept;
    Camera(const Camera& src) noexcept;

    
    void setPos(glm::vec3 pos) noexcept;
    void setYaw(float yaw) noexcept;
    void setPitch(float pitch) noexcept;
    void setRoll(float roll) noexcept;
    void setFov(float fov) noexcept;

    glm::vec3 pos() const noexcept;
    glm::vec3 front() const noexcept;
    glm::vec3 up() const noexcept;
    glm::mat4 view() const noexcept;
    glm::mat4 projection(float aspect) const noexcept;

    float moveSpeed() const noexcept;
    void setMoveSpeed(float speed) noexcept;

    void setKeyInputHandler(KeyInputHandler func) noexcept;
    void handleKeyInput(Window& window) noexcept;

    void setMouseMoveHandler(MouseHandler func) noexcept;
    void setMouseScrollHandler(MouseHandler func) noexcept;
    void handleMouseMove(float x, float y);
    void handleMouseScroll(float dx, float dy);

private:
    glm::vec3 m_pos;
    float m_yaw;
    float m_pitch;
    float m_roll;
    
    float m_moveSpeed;
    float m_moveTime;

    float m_rotateSpeed;
    float m_mouseX;
    float m_mouseY;

    float m_fov;

    bool m_captureCursor;

    KeyInputHandler m_keyInputHandler;
    MouseHandler m_mouseMoveHandler;
    MouseHandler m_mouseScrollHandler;
    
    static void defaultKeyInputHandler(Camera& self, Window& window, float deltaTime) noexcept;
    static void defaultMouseMoveHandler(Camera& self, float dx, float dy) noexcept;
    static void defaultMouseScrollHandler(Camera& self, float dx, float dy) noexcept;
};

}; // namespace EasyGL

#endif // EASYGL_CAMERA_H