#pragma once

#include "RenderCore/Texture2D.h"
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
	Material(const MaterialType &type) : m_type(type) {}

	Material() = default;
	Material(const Material &) = default;
	Material &operator=(const Material &) = default;
	Material(Material &&) = default;
	Material &operator=(Material &&) = default;
	~Material() = default;

	void Load(const std::string &path, const aiMaterial *pMaterial);

	std::optional<std::string> GetTexture(TextureType type) const;

	template<class T>
	std::optional<T> Get(const PropertyMapKey &key) {
		return m_propertyGroups.Get<T>(key);
	}

	const MaterialType &GetType() const { return m_type; }

private:
	void InitBasePBR(const aiMaterial *pMaterial);

	void LoadTexture(const TextureType &textureType, const std::string &relativePath);

	std::string m_modelPath;
	MaterialType m_type = MaterialType::None;
	
	PropertyMap m_propertyGroups;
	std::vector<std::shared_ptr<Texture2D>> m_textures;
	std::vector<TextureType> m_loadTextureTypes;
};

} // namespace Hina
