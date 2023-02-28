#include "hnpch.h"
#include "Scene.h"

#include "Scene/Entity.h"

namespace Hina
{

Entity Scene::CreateEntity(const std::string &name, const glm::vec3 &translation) {
	Entity entity = { m_registry.create(), this };

	std::string entityName = name.empty() ? "Empty Entity" : name;
	entity.AddComponent<NameComponent>(std::move(entityName));

	entity.AddComponent<TransformComponent>(translation);

	return entity;
}

void Scene::DestroyEntity(Entity entity) {
	m_registry.destroy(entity.GetID());
}

void Scene::OnUpdate(DeltaTime time) {

}

} // namespace Hina
