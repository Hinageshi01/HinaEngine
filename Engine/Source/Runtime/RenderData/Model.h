#pragma once

#include "RenderData/Mesh.h"

#include "Core/Timer.h"
#include "RenderData/AABB.h"

#include <assimp/scene.h>

namespace Hina
{

class Model final
{
public:
	// TODO : The granularity of the material should be per mesh rather than per model.
	Model(const std::string &name, const MaterialType &type, const std::string &path);
	Model(std::string &&name, const MaterialType &type, std::string &&path);

	Model() = default;
	Model(const Model &) = default;
	Model &operator=(const Model &) = default;
	Model(Model &&) = default;
	Model &operator=(Model &&) = default;
	~Model() = default;

	void Draw(const std::shared_ptr<Shader> &pShader, const glm::mat4 &trans = glm::identity<glm::mat4>()) const;

	const bool &IsLoaded() { return m_isLoaded; }
	const std::string &GetName() const { return m_name; }
	const std::string &GetPath() const { return m_path; }
	const AABB &GetAABB() const { return m_aabb; }
	const MaterialType &GetMaterialType() const { return m_materialType; }

private:
	void ImportScene(const std::string &path);
	void ProcessScene(const aiScene *pScene);
	void ProcessNode(const aiScene *pScene, const aiNode *pNode);
	void ProcessMesh(const aiScene *pScene, const aiMesh *pMesh);

	Timer m_timer;

	bool m_isLoaded = false;
	std::string m_name;
	std::string m_path;

	AABB m_aabb;
	std::vector<Mesh> m_meshs;
	MaterialType m_materialType = MaterialType::None;
};

} // namespace Hina
