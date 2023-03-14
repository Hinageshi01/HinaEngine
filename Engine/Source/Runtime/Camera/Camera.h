#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Hina
{

struct CameraInitializer
{
    CameraInitializer() = default;
    CameraInitializer(const CameraInitializer &) = default;
    CameraInitializer &operator=(const CameraInitializer &) = default;
    CameraInitializer(CameraInitializer &&) = default;
    CameraInitializer &operator=(CameraInitializer &&) = default;
    ~CameraInitializer() = default;

    glm::vec3 m_position = { 0.0f, 0.0f, -5.0f };

    // Means that m_front will be inlitialied as (0.0f, 1.0f, 0.0f).
    float m_yaw = 90.0f;
    float m_pitch = 0.0f;
    float m_zoom = 45.0f;
    float m_near = 0.01f;
    float m_far = 10000.0f;
};

class Camera final
{
public:
    static constexpr glm::vec3 m_worldUp = { 0.0f, 1.0f, 0.0f };

public:
    explicit Camera(const CameraInitializer &init = CameraInitializer());
    
    Camera(const Camera &) = default;
    Camera &operator=(const Camera &) = default;
    Camera(Camera &&) = default;
    Camera &operator=(Camera &&) = default;
    ~Camera() = default;

    void Init(const CameraInitializer &init);

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix(const uint32_t width, const uint32_t height) const;
    glm::mat4 GetViewProjectionMatrix(const uint32_t width, const uint32_t height) const;

    void CalculateDirections();

    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;

    float m_near;
    float m_far;

    float m_yaw;
    float m_pitch;
    float m_zoom;
};

} // namespace Hina
