#pragma once

#include "Core/DeltaTime.h"

#include <entt/entt.hpp>
#include <glm/glm.hpp>

namespace Hina
{

class Entity;

class Scene
{
public:
	Scene() = default;
	Scene &operator=(const Scene &) = default;
	Scene(const Scene &) = default;
	Scene &operator=(Scene &&) = default;
	Scene(Scene &&) = default;
	~Scene() = default;

	Entity CreateEntity(const std::string &name = "New Entity");
	void DestroyEntity(Entity entity);

	void OnUpdate(DeltaTime time);

	entt::registry &GetRegistry() { return m_registry; }
	const entt::registry &GetRegistry() const { return m_registry; }

private:
	entt::registry m_registry;
};

} // namespace Hina
