#pragma once

#include "Scene/Scene.h"
#include "Scene/Component/NameComponent.h"
#include "Scene/Component/CameraComponent.h"
#include "Scene/Component/TransformComponent.h"

#include <entt/entt.hpp>

namespace Hina
{

class Entity
{
public:
	Entity(entt::entity handle, Scene *scene);

	Entity() = default;
	Entity &operator=(const Entity &) = default;
	Entity(const Entity &) = default;
	Entity &operator=(Entity &&) = default;
	Entity(Entity &&) = default;
	~Entity() = default;

	template<typename T>
	bool HasComponent() const {
		return m_scene->GetRegistry().any_of<T>(m_entityHandle);
	}

	template<typename T, typename... Args>
	T &AddComponent(Args&&... args) {
		assert(!HasComponent<T>(), "Entity already has component!");
		T &component = m_scene->GetRegistry().emplace<T>(m_entityHandle, std::forward<Args>(args)...);
		return component;
	}

	template<typename T, typename... Args>
	T &AddOrReplaceComponent(Args&&... args) {
		T &component = m_scene->GetRegistry().emplace_or_replace<T>(m_entityHandle, std::forward<Args>(args)...);
		return component;
	}

	template<typename T>
	T &GetComponent() const {
		assert(HasComponent<T>(), "Entity does not have component!");
		return m_scene->GetRegistry().get<T>(m_entityHandle);
	}

	template<typename T>
	void RemoveComponent() {
		assert(HasComponent<T>(), "Entity does not have component!");
		m_scene->GetRegistry().remove<T>(m_entityHandle);
	}

	entt::entity GetID() const { return m_entityHandle; }
	uint32_t GetIDu32() const { return static_cast<uint32_t>(m_entityHandle); }
	bool IsValid() const { return m_entityHandle != entt::null; }

	std::string &GetName() { return GetComponent<NameComponent>().GetName(); }
	const std::string &GetName() const { return GetComponent<NameComponent>().GetName(); }

	bool operator==(const Entity &other) const {
		return m_entityHandle == other.m_entityHandle && m_scene == other.m_scene;
	}

	bool operator!=(const Entity &other) const {
		return !(*this == other);
	}

private:
	entt::entity m_entityHandle = entt::null;
	Scene *m_scene = nullptr;
};

} // namespace Hina
