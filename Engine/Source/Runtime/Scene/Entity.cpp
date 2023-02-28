#include "hnpch.h"
#include "Entity.h"

namespace Hina
{

Entity::Entity(entt::entity handle, Scene *scene)
	: m_entityHandle(handle), m_scene(scene) {}

} // namespace Hina
