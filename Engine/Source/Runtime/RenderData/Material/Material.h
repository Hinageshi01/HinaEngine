#pragma once

#include "RenderData/Material/MaterialDefines.h"
#include "RenderData/Material/PropertyMap.hpp"

#include <assimp/material.h>

namespace Hina
{

enum class MaterialType
{
	None = 0,
	BasePBR,
	// StandardPBR,
};

class Material final
{
public:
	Material() = default;
	Material(const Material &) = default;
	Material &operator=(const Material &) = default;
	Material(Material &&) = default;
	Material &operator=(Material &&) = default;
	~Material() = default;

	void Init(const MaterialType &materialType, const aiMaterial *pMaterial);

	std::optional<std::string> GetTexture(TextureType type) const;

	template<class T>
	std::optional<T> Get(const PropertyMapKey &key) {
		return m_propertyGroups.Get<T>(key);
	}

	const MaterialType &GetType() const { return m_type; }

private:
	MaterialType m_type = MaterialType::None;
	PropertyMap m_propertyGroups;
};

} // namespace Hina
