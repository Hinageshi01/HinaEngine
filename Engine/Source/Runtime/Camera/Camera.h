#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Hina
{

enum class CameraMovement
{
    FORWARD, BACKWARD,
    LEFT, RIGHT,
    UP, DOWN,
};

struct CameraInitializer
{
    const glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
    const glm::vec3 m_worldUp = { 0.0f, 1.0f, 0.0f };
    const float m_yaw = 0.0f;
    const float m_pitch = 0.0f;
    const float m_zoom = 45.0f;
    const float m_speed = 2.5f;
    const float m_sensitivity = 0.1f;
};

class Camera
{
public:
    Camera(const CameraInitializer &init = CameraInitializer());
    void Init(const CameraInitializer &init);

    const glm::mat4 GetViewMatrix() const;
    const glm::mat4 GetProjectionMatrix(const uint32_t width, const uint32_t height) const;
    const glm::mat4 GetViewProjectionMatrix(const uint32_t width, const uint32_t height) const;

    void ProcessKeyboard(CameraMovement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset);
    void ProcessMouseScroll(float yoffset);

    glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
    glm::vec3 m_front = { 0.0f, 0.0f, 1.0f };
    glm::vec3 m_up = { 0.0f, 1.0f, 0.0f };
    glm::vec3 m_right = { 1.0f, 0.0f, 0.0f };
    glm::vec3 m_worldUp = { 0.0f, 1.0f, 0.0f };

    float m_yaw;
    float m_pitch;
    float m_zoom;

    float m_speed;
    float m_sensitivity;

private:
    void Update();
};

} // namespace Hina
