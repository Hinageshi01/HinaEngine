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

    glm::vec3 m_position = { 0.0f, 0.0f, 5.0f };

    // Means that m_front will be inlitialied as (0.0f, 0.0f, -1.0f).
    float m_yaw = glm::radians(-90.0f);
    float m_pitch = glm::radians(0.0f);
    float m_zoom = glm::radians(45.0f);
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

    void LookAt(const glm::vec3 &target);
    void RecalculateDirections(const bool reCalculateFront = true);

    void SetPosition(const glm::vec3 &pos) { m_position = pos; }
    glm::vec3 &GetPosition() { return m_position; }
    const glm::vec3 &GetPosition() const { return m_position; }
    void UpdatePosition(const glm::vec3 &trans) { m_position += trans; }

    void SetFront(const glm::vec3 &front) { m_front = front; }
    glm::vec3 &GetFront() { return m_front; }
    const glm::vec3 &GetFront() const { return m_front; }

    void SetRight(const glm::vec3 &right) { m_right = right; }
    glm::vec3 &GetRight() { return m_right; }
    const glm::vec3 &GetRight() const { return m_right; }

    void SetYaw(const float yaw) { m_yaw = yaw; }
    float &GetYaw() { return m_yaw; }
    const float &GetYaw() const { return m_yaw; }
    void UpdateYaw(const float yaw) { m_yaw += yaw; }

    void SetPitch(const float pitch) { m_pitch = pitch; }
    float &GetPitch() { return m_pitch; }
    const float &GetPitch() const { return m_pitch; }
    void UpdatePitch(const float pitch) { m_pitch += pitch; }

    void SetZoom(const float zoom) { m_zoom = zoom; }
    float &GetZoom() { return m_zoom; }
    const float &GetZoom() const { return m_zoom; }
    void UpdateZoom(const float zoom) { m_zoom += zoom; }

    void SetNear(const float _near) { m_near = _near; }
    float &GetNear() { return m_near; }
    const float &GetNear() const { return m_near; }

    void SetFar(const float _far) { m_far = _far; }
    float &GetFar() { return m_far; }
    const float &GetFar() const { return m_far; }

private:
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_right;
    glm::vec3 m_up;

    // Store as radians.
    float m_yaw;
    float m_pitch;

    float m_zoom;
    float m_near;
    float m_far;
};

} // namespace Hina
