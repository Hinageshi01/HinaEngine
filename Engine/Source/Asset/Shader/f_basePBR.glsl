#version 330 core

#define PI 3.1415926535897932
#define PI2 9.8696044010893586
#define INV_PI 0.3183098861837907
#define INV_PI2 0.1013211836423378

#define D_LIGHT_COUNT 4 // define
#define T_POINT_LIGHT 0 // type
#define T_DIRECTIONAL_LIGHT 1 // type

out vec4 fragColor;

in vec3 v_worldPos;
in vec3 v_normal;
in vec3 v_tangent;
in vec3 v_bitangent;
in vec2 v_uv0;

uniform sampler2D s_albedo;
uniform sampler2D s_normal;
uniform sampler2D s_ORM;
uniform sampler2D s_emissive;

uniform sampler2D s_IBL_BRDF_LUT;
uniform samplerCube s_cube;
uniform samplerCube s_cubeIrr;

uniform vec3 u_cameraPos;

// -------------------- Color Space -------------------- //

// approximation sRGB to linear
float Pow2p2(in float num) {
	return pow(num, 2.2);
}
vec3 aprSRGBToLinear(in vec3 sRGB) {
	return vec3(Pow2p2(sRGB.x), Pow2p2(sRGB.y), Pow2p2(sRGB.z));
}
vec4 aprSRGBToLinear(in vec4 sRGB) {
	return vec4(Pow2p2(sRGB.x), Pow2p2(sRGB.y), Pow2p2(sRGB.z), Pow2p2(sRGB.w));
}

// approximation linear to sRGB
float PowN2p2(in float num) {
	return pow(num, (1.0 / 2.2));
}
vec3 aprLinearToSRGB(in vec3 linear) {
	return vec3(PowN2p2(linear.x), PowN2p2(linear.y), PowN2p2(linear.z));
}
vec4 aprLinearToSRGB(in vec4 linear) {
	return vec4(PowN2p2(linear.x), PowN2p2(linear.y), PowN2p2(linear.z), PowN2p2(linear.w));
}

// accurate sRGB to linear
float ToLinear(in float num) {
	float lo = num / 12.92;
	float hi = pow((num + 0.055) / 1.055 , 2.4);
	return (num <= 0.04045) ? lo : hi;
}
vec3 SRGBToLinear(in vec3 sRGB) {
	return vec3(ToLinear(sRGB.x), ToLinear(sRGB.y), ToLinear(sRGB.z));
}
vec4 SRGBToLinear(in vec4 sRGB) {
	return vec4(ToLinear(sRGB.x), ToLinear(sRGB.y), ToLinear(sRGB.z), ToLinear(sRGB.w));
}

// accurate linear to sRGB
float ToSRGB(in float num) {
	float lo = num * 12.92;
	float hi = (pow(abs(num), 1.0/2.4) * 1.055) - 0.055;
	return (num <= 0.0031308) ? lo : hi;
}
vec3 LinearToSRGB(in vec3 linear) {
	return vec3(ToSRGB(linear.x), ToSRGB(linear.y), ToSRGB(linear.z));
}
vec4 LinearToSRGB(in vec4 linear) {
	return vec4(ToSRGB(linear.x), ToSRGB(linear.y), ToSRGB(linear.z), ToSRGB(linear.w));
}

// -------------------- Material -------------------- //

struct Material
{
	vec3 albedo;
	vec3 normal;
	float occlusion;
	float roughness;
	float metallic;
	vec3 F0;
	float opacity;
	vec3 emissive;
};

Material CreateDefaultMaterial() {
	Material material;
	material.albedo = vec3(0.99, 0.99, 0.99);
	material.normal = vec3(0.0, 1.0, 0.0);
	material.occlusion = 1.0;
	material.roughness = 0.9;
	material.metallic = 0.1;
	material.F0 = vec3(0.135, 0.135, 0.135);
	material.opacity = 1.0;
	material.emissive = vec3(0.0);
	return material;
}

vec3 SampleAlbedoTexture(in vec2 uv) {
	return SRGBToLinear(texture(s_albedo, uv).xyz);
}

vec3 SampleNormalTexture(in vec2 uv, in vec3 tangent, in vec3 bitangent, in vec3 normal) {
	// We assume that normal texture is already in linear space.
	mat3 TBN = mat3(tangent, bitangent, normal);
	vec3 textureNormal = normalize(texture(s_normal, uv).xyz * 2.0 - 1.0);
	return normalize(TBN * textureNormal);
}

vec3 SampleORMTexture(in vec2 uv) {
	// We assume that ORM texture is already in linear space.
	vec3 orm = texture(s_ORM, uv).xyz;
	orm.y = clamp(orm.y, 0.04, 1.0); // roughness
	return orm;
}

vec3 CalcuateF0(in vec3 albedo, in float metallic) {
	return mix(vec3(0.04), albedo, vec3(metallic));
}

// -------------------- BRDF -------------------- //

// Fresnel
vec3 FresnelSchlick(in float cosTheta, in vec3 F0) {
	return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

// Distribution
float DistributionGGX(in float NdotH, in float rough) {
	float a  = rough * rough;
	float a2 = a * a;
	float denom = (NdotH * NdotH * (a2 - 1.0) + 1.0);
	denom = PI * denom * denom;
	return a2 / denom;
}

// Geometry
float Visibility(in float NdotV, in float NdotL, in float rough) {
	// Specular BRDF = (F * D * G) / (4 * NdotV * NdotL)
	// = (F * D * (NdotV / (NdotV * (1 - K) + K)) * (NdotL / (NdotL * (1 - K) + K))) / (4 * NdotV * NdotL)
	// = (F * D * (1 / (NdotV * (1 - K) + K)) * (1 / (NdotL * (1 - K) + K))) / 4
	// = F * D * Vis
	// Vis = 1 / (NdotV * (1 - K) + K) / (NdotL * (1 - K) + K) / 4
	
	float f = rough + 1.0;
	float k = f * f * 0.125;
	float ggxV  = 1.0 / (NdotV * (1.0 - k) + k);
	float ggxL  = 1.0 / (NdotL * (1.0 - k) + k);
	return ggxV * ggxL * 0.25;
}

// -------------------- Light -------------------- //

struct Light 
{
	int type;
	vec3 position;
	vec3 direction;
	vec3 color;
	float intensity;
	float range;
};

uniform Light u_lights[D_LIGHT_COUNT];

float SmoothDistanceAtt(in float squaredDistance, in float invSqrAttRadius) {
	float factor = squaredDistance * invSqrAttRadius;
	float smoothFactor = clamp(1.0 - factor * factor, 0.0, 1.0);
	return smoothFactor * smoothFactor;
}

float GetDistanceAtt(in float sqrDist, in float invSqrAttRadius) {
	float attenuation = 1.0 / (max(sqrDist , 0.0001));
	attenuation *= SmoothDistanceAtt(sqrDist, invSqrAttRadius);
	return attenuation;
}

vec3 CalculatePointLight(Light light, Material material, vec3 worldPos, vec3 viewDir, vec3 diffuseBRDF) {
	vec3 lightDir = normalize(light.position - worldPos);
	vec3 harfDir  = normalize(lightDir + viewDir);
	
	float NdotV = max(dot(material.normal, viewDir), 0.0);
	float NdotL = max(dot(material.normal, lightDir), 0.0);
	float NdotH = max(dot(material.normal, harfDir), 0.0);
	float HdotV = max(dot(harfDir, viewDir), 0.0);
	
	float distance = length(light.position - worldPos);
	float attenuation = GetDistanceAtt(distance * distance, 1.0 / (light.range * light.range));
	vec3 radiance = light.color * light.intensity * 0.25 * INV_PI * attenuation;
	
	vec3  Fre = FresnelSchlick(HdotV, material.F0);
	float NDF = DistributionGGX(NdotH, material.roughness);
	float Vis = Visibility(NdotV, NdotL, material.roughness);
	vec3 specularBRDF = Fre * NDF * Vis;
	
	vec3 KD = mix(1.0 - Fre, vec3(0.0), material.metallic);
	return (KD * diffuseBRDF + specularBRDF) * radiance * NdotL;
}

vec3 CalculateDirectionalLight(Light light, Material material, vec3 worldPos, vec3 viewDir, vec3 diffuseBRDF) {
	vec3 lightDir = -light.direction;
	vec3 harfDir  = normalize(lightDir + viewDir);
	
	float NdotV = max(dot(material.normal, viewDir), 0.0);
	float NdotL = max(dot(material.normal, lightDir), 0.0);
	float NdotH = max(dot(material.normal, harfDir), 0.0);
	float HdotV = max(dot(harfDir, viewDir), 0.0);
	
	vec3  Fre = FresnelSchlick(HdotV, material.F0);
	float NDF = DistributionGGX(NdotH, material.roughness);
	float Vis = Visibility(NdotV, NdotL, material.roughness);
	vec3 specularBRDF = Fre * NDF * Vis;
	
	vec3 KD = mix(1.0 - Fre, vec3(0.0), material.metallic);
	vec3 irradiance = light.color * light.intensity;
	return (KD * diffuseBRDF + specularBRDF) * irradiance * NdotL;
}

vec3 CalculateLights(Material material, vec3 worldPos, vec3 viewDir, vec3 diffuseBRDF) {
	vec3 color = vec3(0.0);
	for(int lightIndex = 0; lightIndex < D_LIGHT_COUNT; ++lightIndex) {
		Light light = u_lights[lightIndex];
		switch(light.type) {
			case T_POINT_LIGHT:
				color += CalculatePointLight(light, material, worldPos, viewDir, diffuseBRDF);
				break;
			case T_DIRECTIONAL_LIGHT:
				color += CalculateDirectionalLight(light, material, worldPos, viewDir, diffuseBRDF);
				break;
			default:
				color += vec3(0.0);
		}
	}
	return color;
}

// -------------------- Tone Mapping -------------------- //

// approximation
vec3 ACES(vec3 v) {
	v *= 0.6f;
	float a = 2.51f;
	float b = 0.03f;
	float c = 2.43f;
	float d = 0.59f;
	float e = 0.14f;
	return clamp((v * (a * v + b)) / (v * (c * v + d) + e), 0.0f, 1.0f);
}

// -------------------- main -------------------- //

void main()
{
	Material material = CreateDefaultMaterial();
	material.albedo = SampleAlbedoTexture(v_uv0);
	material.normal = SampleNormalTexture(v_uv0, v_tangent, v_bitangent, v_normal);
	vec3 orm = SampleORMTexture(v_uv0);
	material.occlusion = orm.x;
	material.roughness = orm.y;
	material.metallic = orm.z;
	material.F0 = CalcuateF0(material.albedo, material.metallic);
	
	vec3 viewDir  = normalize(u_cameraPos - v_worldPos);
	vec3 diffuseBRDF = material.albedo * INV_PI;
	float NdotV = max(dot(material.normal, viewDir), 0.0);
	
	// -------------------- Directional Light -------------------- //
	
	vec3 dirColor = CalculateLights(material, v_worldPos, viewDir, diffuseBRDF);
	
	// -------------------- Environment Light -------------------- //
	
	// Environment Prefiltered Irradiance
	vec3 envIrradiance = vec3(0.4);
	
	// Environment Specular BRDF
	vec2 lut = texture(s_IBL_BRDF_LUT, vec2(NdotV, 1.0 - material.roughness)).xy;
	vec3 envSpecularBRDF = (material.F0 * lut.x + lut.y);
	
	// Environment Specular Radiance
	vec3 reflectDir = normalize(reflect(-viewDir, material.normal));
	vec3 envRadiance = vec3(0.4);
	
	// Occlusion
	float specularOcclusion = mix(pow(material.occlusion, 4.0), 1.0, clamp(-0.3 + NdotV * NdotV, 0.0, 1.0));
	float horizonOcclusion = clamp(1.0 + 1.2 * dot(reflectDir, v_normal), 0.0, 1.0);
	horizonOcclusion *= horizonOcclusion;
	
	vec3 Fre = FresnelSchlick(NdotV, material.F0);
	vec3 KD = mix(1.0 - Fre, vec3(0.0), material.metallic);
	
	vec3 envColor = KD * material.albedo * envIrradiance * material.occlusion +
		envSpecularBRDF * envRadiance * min(specularOcclusion, horizonOcclusion);
	
	// -------------------- Fragment Color -------------------- //
	
	vec3 color = dirColor + envColor;
	color = ACES(color);
	color = aprLinearToSRGB(color);
	
	fragColor = vec4(color, 1.0);
	// fragColor = vec4(u_lights[1].position, 1.0);
}
