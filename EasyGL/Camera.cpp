#include <EasyGL/Camera.h>

namespace  EasyGL
{

constexpr static float DEFAULT_YAW = -90.0f;
constexpr static float DEFAULT_PITCH = 0.0f;
constexpr static float DEFAULT_ROLL = 0.0f;
constexpr static float DEFAULT_MOVE_SPEED = 1.0f;
constexpr static float DEFAULT_ROTATE_SPEED = 0.05f;
constexpr static float DEFAULT_FOV = 45.0f;

constexpr static float MAX_PITCH = 89.0f;
constexpr static float MIN_PITCH = -89.0f;
constexpr static float MAX_FOV = 179.0f;
constexpr static float MIN_FOV = 1.0f;

// static
void Camera::defaultKeyInputHandler(Camera& self, Window& window, float deltaTime) noexcept
{
    bool captureCursor = window.getKey(GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE;
    window.captureCursor(captureCursor);
    if (!captureCursor && self.m_captureCursor)
    {
        window.setCursorPos(window.width()/2.0, window.height()/2.0);
    }
    else if (captureCursor && !self.m_captureCursor)
    {
        self.m_mouseX = NAN;
        self.m_mouseY = NAN;
    }
    self.m_captureCursor = captureCursor;

    float delta = self.m_moveSpeed * deltaTime;
    if (window.getKey(GLFW_KEY_W) == GLFW_PRESS)
    {
        self.m_pos += delta * self.front();
    }

    if (window.getKey(GLFW_KEY_S) == GLFW_PRESS)
    {
        self.m_pos -= delta * self.front();
    }

    if (window.getKey(GLFW_KEY_A) == GLFW_PRESS)
    {
        self.m_pos -= delta * glm::normalize(glm::cross(self.front(), self.up()));
    }

    if (window.getKey(GLFW_KEY_D) == GLFW_PRESS)
    {
        self.m_pos += delta * glm::normalize(glm::cross(self.front(), self.up()));
    }

    if (window.getKey(GLFW_KEY_Q) == GLFW_PRESS)
    {
        self.m_roll -= 1.0f;
    }

    if (window.getKey(GLFW_KEY_E) == GLFW_PRESS)
    {
        self.m_roll += 1.0f;
    }
}


// static 
void Camera::defaultMouseMoveHandler(Camera& self, float dx, float dy) noexcept
{
    if (!self.m_captureCursor)
    {
        return;
    }

    self.m_yaw += self.m_rotateSpeed * dx;
    self.m_pitch -= self.m_rotateSpeed * dy;

    if (self.m_pitch > MAX_PITCH)
        self.m_pitch = MAX_PITCH;
    else if (self.m_pitch < MIN_PITCH)
        self.m_pitch = MIN_PITCH;
}

// static 
void Camera::defaultMouseScrollHandler(Camera& self, float dx, float dy) noexcept
{
    if (!self.m_captureCursor)
        return;

    (void)dx;
    self.m_fov -= dy;

    if (self.m_fov > MAX_FOV)
        self.m_fov = MAX_FOV;
    else if (self.m_fov < MIN_FOV)
        self.m_fov = MIN_FOV;
}

Camera::~Camera() noexcept
{

}

Camera::Camera(glm::vec3 pos) noexcept:
    m_pos{pos},
    m_yaw(DEFAULT_YAW),
    m_pitch(DEFAULT_PITCH),
    m_roll(DEFAULT_ROLL),
    m_moveSpeed{DEFAULT_MOVE_SPEED},
    m_moveTime{0.0f},
    m_rotateSpeed{DEFAULT_ROTATE_SPEED},
    m_mouseX{NAN},
    m_mouseY{NAN},
    m_fov{DEFAULT_FOV},
    m_captureCursor{false},
    m_keyInputHandler{defaultKeyInputHandler},
    m_mouseMoveHandler{defaultMouseMoveHandler},
    m_mouseScrollHandler{defaultMouseScrollHandler}
{

}

Camera::Camera(const Camera& src) noexcept:
    m_pos{src.m_pos},
    m_yaw(src.m_yaw),
    m_pitch(src.m_pitch),
    m_roll(src.m_roll),
    m_moveSpeed{src.m_moveSpeed},
    m_moveTime{src.m_moveTime},
    m_rotateSpeed{src.m_rotateSpeed},
    m_mouseX{src.m_mouseX},
    m_mouseY{src.m_mouseY},
    m_fov{src.m_fov},
    m_captureCursor{src.m_captureCursor},
    m_keyInputHandler{src.m_keyInputHandler},
    m_mouseMoveHandler{src.m_mouseMoveHandler},
    m_mouseScrollHandler{src.m_mouseScrollHandler}
{

}

void Camera::setPos(glm::vec3 pos) noexcept
{
    m_pos = std::move(pos);
}

void Camera::setYaw(float yaw) noexcept
{
    m_yaw = yaw;
}

void Camera::setPitch(float pitch) noexcept
{
    m_pitch = pitch;
}

void Camera::setRoll(float roll) noexcept
{
    m_roll = roll;
}

void Camera::setFov(float fov) noexcept
{
    m_fov = fov;
}

glm::vec3 Camera::pos() const noexcept
{
    return m_pos;
}

glm::vec3 Camera::front() const noexcept
{
    glm::vec3 m_front;
    m_front.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
    m_front.y = sin(glm::radians(m_pitch));
    m_front.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));
    return glm::normalize(m_front);
}

glm::vec3 Camera::up() const noexcept
{
    glm::vec3 m_up;
    m_up.x = sin(glm::radians(m_yaw)) * sin(glm::radians(m_roll));
    m_up.y = cos(glm::radians(m_pitch)) * cos(glm::radians(m_roll));
    m_up.z = sin(glm::radians(m_pitch));
    return glm::normalize(m_up);
}

glm::mat4 Camera::view() const noexcept
{
    return glm::lookAt(m_pos, m_pos + front(), up());
}


glm::mat4 Camera::projection(float aspect) const noexcept
{
    glm::mat4 projection{1.0f};
    return glm::perspective(glm::radians(m_fov), aspect, 0.1f, 100.0f);
}

float Camera::moveSpeed() const noexcept
{
    return m_moveSpeed;
}

void Camera::setMoveSpeed(float speed) noexcept
{
    m_moveSpeed = speed;
}

void Camera::setKeyInputHandler(KeyInputHandler func) noexcept
{
    m_keyInputHandler = func;
}

void Camera::handleKeyInput(Window& window) noexcept
{
    if (m_keyInputHandler == nullptr)
        return;

    m_keyInputHandler(*this, window, Application::getTime() - m_moveTime);
    m_moveTime = Application::getTime();
}

void Camera::setMouseMoveHandler(MouseHandler func) noexcept
{
    m_mouseMoveHandler = func;
}

void Camera::setMouseScrollHandler(MouseHandler func) noexcept
{
    m_mouseScrollHandler = func;
}


void Camera::handleMouseMove(float x, float y)
{
    if (m_mouseMoveHandler == nullptr)
        return;

    if (!glm::isnan(m_mouseX) && !glm::isnan(m_mouseY))
        m_mouseMoveHandler(*this, x - m_mouseX, y - m_mouseY);

    m_mouseX = x;
    m_mouseY = y;
}

void Camera::handleMouseScroll(float dx, float dy)
{
    if (m_mouseScrollHandler == nullptr)
        return;

    m_mouseScrollHandler(*this, dx, dy);
}

// void Camera::configMouseCallback(Window& window) noexcept
// {
//     window.setUserData(this);

//     glfwSetCursorPosCallback(window.id(), [](GLFWwindow* window, double x, double y){
//         if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
//             return;

//         Camera* self = static_cast<Camera*>(glfwGetWindowUserPointer(window));
//         if (self->m_mouseMoveHandler == nullptr)
//             return;

//         if (!glm::isnan(self->m_mouseX) && !glm::isnan(self->m_mouseY))
//             self->m_mouseMoveHandler(*self, x - self->m_mouseX, y - self->m_mouseY);

//         self->m_mouseX = x;
//         self->m_mouseY = y;
//     });

//     glfwSetScrollCallback(window.id(), [](GLFWwindow* window, double dx, double dy){
//         if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
//             return;

//         Camera* self = static_cast<Camera*>(glfwGetWindowUserPointer(window));
//         if (self->m_mouseScrollHandler == nullptr)
//             return;
//         self->m_mouseScrollHandler(*self, dx, dy);
//     });
// }
    
}; // namespace  EasyGL
