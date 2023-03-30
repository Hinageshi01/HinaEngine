#include "hnpch.h"
#include "Material.h"

namespace Hina
{

namespace Utils
{

inline aiTextureType GetAssimpTextureType(const TextureType &type){
	switch(type) {
		case TextureType::Ambient:
			return aiTextureType_BASE_COLOR;
		case TextureType::Normal:
			return aiTextureType_NORMALS;
		case TextureType::Occlusion:
			return aiTextureType_LIGHTMAP;
		case TextureType::Roughness:
			return aiTextureType_DIFFUSE_ROUGHNESS;
		case TextureType::Metallic:
			return aiTextureType_METALNESS;
		case TextureType::Emissive:
			return aiTextureType_EMISSIVE;

		default:
			return aiTextureType_UNKNOWN;
	}
}

const std::vector<TextureType> basePBRTextureTypes = {
	TextureType::Ambient, TextureType::Normal, TextureType::ORM_Combine,
	// TextureType::Occlusion, TextureType::Roughness, TextureType::Metallic,
};

} // namespace Utils

void Material::Load(const std::string &path, const aiMaterial *pMaterial) {
	HN_CORE_TRACE("");
	HN_CORE_TRACE("                Material name: {0}", pMaterial->GetName().C_Str());

	m_modelPath = path;

	switch(m_type) {
		case MaterialType::BasePBR:
			InitBasePBR(pMaterial);
			return;

		case MaterialType::None:
			HN_CORE_ERROR("Unsupport Material type!");
			return;
	}

	HN_CORE_ERROR("Unknow Material type!");
}

std::optional<std::string> Material::GetTexture(TextureType type) const {
	return m_propertyGroups.Get<std::string>(GetMaterialPropertyTextureKey(type));
}

void Material::InitBasePBR(const aiMaterial *pMaterial) {
	for(const auto &textureType : Utils::basePBRTextureTypes) {
		aiTextureType assimpTextureType = Utils::GetAssimpTextureType(textureType);
		const size_t assimpTextureTypeCount = pMaterial->GetTextureCount(assimpTextureType);

		if(assimpTextureTypeCount == 0) {
			HN_CORE_WARN("                Can not find required texture type {0}!", GetMaterialPropertyGroupName(textureType));
		}

		for(size_t textureIndex = 0; textureIndex < assimpTextureTypeCount; ++textureIndex) {
			aiString aiPath;
			pMaterial->GetTexture(assimpTextureType, textureIndex, &aiPath);
			std::string texturePath = aiPath.C_Str();
			HN_CORE_TRACE("                Texture type {0} path: {1}", GetMaterialPropertyGroupName(textureType), texturePath);

			std::string key = GetMaterialPropertyTextureKey(textureType);
			m_propertyGroups.Add(key, texturePath);

			LoadTexture(textureType, texturePath);
		}
	}
}

void Material::LoadTexture(const TextureType &textureType, const std::string &relativePath) {
	// TODO : Not sure if the texture will be load repeatedly.

	m_loadTextureTypes.push_back(textureType);

	std::string absolutePath = (std::filesystem::path(m_modelPath).parent_path() / relativePath).string();
	m_textures.push_back(Texture2D::Create(absolutePath));
}

} // namespace Hina
