#pragma once

namespace Hina
{

enum class PropertyGroup
{
	None = 0,

	Albedo,
	Normal,
	Occlusion,
	Roughness,
	Metallic,
	ORM_Combine,

	Emissive,

	Count,
};

using TextureType = PropertyGroup;

enum class Property
{
	None = 0,

	Factor,
	Color,
	Texture,

	Count,
};

////////////////////////////// Utils //////////////////////////////

constexpr const char *PropertyGroupName[] =
{
	"None",
	"Ambient",
	"Normal",
	"Occlusion",
	"Roughness",
	"Metallic",
	"ORM_Combine",
	"Emissive",
};

constexpr const char *PropertyName[] =
{
	"None",
	"Factor",
	"Color",
	"Texture",
};

inline const char *GetMaterialPropertyGroupName(PropertyGroup propertyGroup) {
	return PropertyGroupName[static_cast<size_t>(propertyGroup)];
}

inline const char *GetMaterialPropertyName(Property property) {
	return PropertyName[static_cast<size_t>(property)];
}

inline std::string GetMaterialPropertyKey(PropertyGroup propertyGroup, Property property) {
	std::stringstream ss;
	ss << GetMaterialPropertyGroupName(propertyGroup) << "_" << GetMaterialPropertyName(property);

	return ss.str();
}

inline std::string GetMaterialPropertyTextureKey(PropertyGroup propertyGroup) {
	return GetMaterialPropertyKey(propertyGroup, Property::Texture);
}

static_assert(static_cast<size_t>(PropertyGroup::Count) == sizeof(PropertyGroupName) / sizeof(char *) && "Material property group and names mismatch.");
static_assert(static_cast<int>(Property::Count) == sizeof(PropertyName) / sizeof(char *), "Material property and names mismatch.");

} // namespace Hina
