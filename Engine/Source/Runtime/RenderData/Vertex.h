#pragma once

#include "RenderCore/BufferLayout.h"

#include <glm/glm.hpp>
#include <cstdint>

namespace Hina
{

namespace
{

constexpr uint8_t MAX_BONE = 4;

}

class Vertex final
{
public:
    static BufferLayout GetLayOut();

public:
    Vertex() = default;
    Vertex(const Vertex &) = default;
    Vertex &operator=(const Vertex &) = default;
    Vertex(Vertex &&) = default;
    Vertex &operator=(Vertex &&) = default;
    ~Vertex() = default;

    // Return the pointer of the start position of Vertex in memory.
    const float *Data() const { return &m_position.x; }

    void SetPosition(const glm::vec3 &postion) { m_position = postion; }
    glm::vec3 &GetPosition() { return m_position; }
    const glm::vec3 &GetPosition() const { return m_position; }

    void SetNormal(const glm::vec3 &normal) { m_normal = normal; }
    glm::vec3 &GetNormal() { return m_normal; }
    const glm::vec3 &GetNormal() const { return m_normal; }

    void SetTangent(const glm::vec3 &tangent) { m_tangent = tangent; }
    glm::vec3 &GetTangent() { return m_tangent; }
    const glm::vec3 &GetTangent() const { return m_tangent; }

    void SetUV(const glm::vec2 &uv) { m_uv = uv; }
    glm::vec2 &GetUV() { return m_uv; }
    const glm::vec2 &GetUV() const { return m_uv; }

    void SetBone(const size_t index, const uint32_t bone) { m_bones[index] = bone; }
    uint32_t &GetBone(const size_t index) { return m_bones[index]; }
    const uint32_t &GetBone(const size_t index) const { return m_bones[index]; }
    
    void SetWeight(const size_t index, const float bone) { m_weights[index] = bone; }
    float &GetWeight(const size_t index) { return m_weights[index]; }
    const float &GetWeight(const size_t index) const { return m_weights[index]; }

private:
    glm::vec3 m_position;
    glm::vec3 m_normal;
    glm::vec3 m_tangent;
    glm::vec2 m_uv;
    uint32_t m_bones[MAX_BONE];
    float m_weights[MAX_BONE];

    static_assert(sizeof(glm::vec3) == sizeof(float) * 3);
};

} // namespace Hina
