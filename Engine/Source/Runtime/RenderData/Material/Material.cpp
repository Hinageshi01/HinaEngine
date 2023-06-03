#include "hnpch.h"
#include "Material.h"

#include "Path/Path.h"

namespace Hina
{

namespace Utils
{

inline aiTextureType GetAssimpTextureType(const TextureType &type){
	switch(type) {
		case TextureType::Albedo:
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

inline std::string GetSamplerName(const TextureType &type) {
	switch(type) {
		case TextureType::Albedo:
			return "s_albedo";
		case TextureType::Normal:
			return "s_normal";
		case TextureType::ORM_Combine:
			return "s_ORM";
		case TextureType::Emissive:
			return "s_emissive";
		case TextureType::IBL_BRDF_LUT:
			return "s_IBL_BRDF_LUT";

		default:
			return "s_unknow";
	}
}

const std::vector<TextureType> basePBRTextureTypes = {
	TextureType::Albedo, TextureType::Normal, TextureType::ORM_Combine,
	// TextureType::Occlusion, TextureType::Roughness, TextureType::Metallic,
};

} // namespace Utils

void Material::SubmitTextures(const std::shared_ptr<Shader> &pShader) const {
	HN_CORE_ASSERT(m_textures.size() == m_loadTextureTypes.size(), "Loaded texture type mismatch!");

	pShader->Bind();

	int slot = 0;
	for(size_t textureIndex = 0; textureIndex < m_textures.size(); ++textureIndex) {
		const auto &texture = m_textures.at(textureIndex);
		const auto &type = m_loadTextureTypes.at(textureIndex);

		texture->Bind(slot);
		pShader->SetInt(Utils::GetSamplerName(type), slot);

		++slot;
	}

	pShader->Unbind();
}

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
			m_propertyGroups.Add(std::move(key), texturePath);

			LoadTexture(textureType, texturePath);
		}
	}

	m_textures.push_back(Texture2D::Create(Path::FromAsset("Texture/ibl_brdf_lut.png")));
	m_loadTextureTypes.push_back(TextureType::IBL_BRDF_LUT);
}

void Material::LoadTexture(const TextureType &textureType, const std::string &relativePath) {
	// TODO : Not sure if the texture will be load repeatedly.

	m_loadTextureTypes.push_back(textureType);

	std::string absolutePath = (std::filesystem::path(m_modelPath).parent_path() / relativePath).string();
	m_textures.push_back(Texture2D::Create(std::move(absolutePath)));
}

} // namespace Hina
