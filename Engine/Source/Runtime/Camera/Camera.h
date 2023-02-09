#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Hina
{

struct CameraInitializer
{
    const glm::vec3 m_position = { 0.0f, 0.0f, -5.0f };
    const glm::vec3 m_worldUp = { 0.0f, 1.0f, 0.0f };
    // Means that m_front will be inlitialied as (0.0f, 1.0f, 0.0f).
    const float m_yaw = 90.0f;
    const float m_pitch = 0.0f;
    const float m_zoom = 45.0f;
    const float m_moveSensitive = 2.5f;
    const float m_rotateSensitive = 0.2f;
    const float m_scrollSensitive = 1.0f;
};

class Camera
{
public:
    Camera(const CameraInitializer &init = CameraInitializer());
    void Init(const CameraInitializer &init);

    const glm::mat4 GetViewMatrix() const;
    const glm::mat4 GetProjectionMatrix(const uint32_t width, const uint32_t height) const;
    const glm::mat4 GetViewProjectionMatrix(const uint32_t width, const uint32_t height) const;

    void CalculateDirections();

    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;

    float m_yaw;
    float m_pitch;
    float m_zoom;

    float m_moveSensitive;
    float m_rotateSensitive;
    float m_scrollSensitive;
};

} // namespace Hina
