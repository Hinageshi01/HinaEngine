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
	TextureType::Ambient, TextureType::Normal,
	TextureType::Occlusion, TextureType::Roughness, TextureType::Metallic,
	// TextureType::ORM_Combine,
};

} // namespace Utils

void Material::Init(const MaterialType &materialType, const aiMaterial *pMaterial) {
	HN_CORE_TRACE("");
	HN_CORE_TRACE("                Material name: {0}", pMaterial->GetName().C_Str());
	m_type = materialType;

	switch(m_type) {
		case MaterialType::BasePBR:
			for(const auto &type : Utils::basePBRTextureTypes) {
				aiTextureType assimpTextureType = Utils::GetAssimpTextureType(type);
				const size_t assimpTextureTypeCount = pMaterial->GetTextureCount(assimpTextureType);

				if(assimpTextureTypeCount == 0) {
					HN_CORE_WARN("                Can not find request texture type {0}!", GetMaterialPropertyGroupName(type));
				}

				for(size_t textureIndex = 0; textureIndex < assimpTextureTypeCount; ++textureIndex) {
					aiString aiPath;
					pMaterial->GetTexture(assimpTextureType, textureIndex, &aiPath);

					std::string texturePath = aiPath.C_Str();
					std::string key = GetMaterialPropertyTextureKey(type);
					m_propertyGroups.Add(key, texturePath);

					HN_CORE_TRACE("                Texture type {0} path: {1}", GetMaterialPropertyGroupName(type), texturePath);
				}
			}
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

} // namespace Hina
