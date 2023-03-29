#pragma once

#include "RenderData/Mesh.h"

#include "Core/Timer.h"
#include "RenderData/AABB.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Hina
{

class Model final
{
public:
	explicit Model(const std::string &path);
	explicit Model(std::string &&path);

	Model() = default;
	Model(const Model &) = default;
	Model &operator=(const Model &) = default;
	Model(Model &&) = default;
	Model &operator=(Model &&) = default;
	~Model() = default;

	void Draw(const std::shared_ptr<Shader> &pShader, const glm::mat4 &trans = glm::identity<glm::mat4>()) const;

	const std::string &GetPath() { return m_path; }

private:
	void ImportScene(const std::string &path);
	void ProcessScene(const aiScene *pScene);
	void ProcessNode(const aiScene *pScene, const aiNode *pNode);
	void ProcessMesh(const aiMesh *pMesh);

	Timer m_timer;
	std::string m_path;

	AABB m_aabb;
	std::vector<Mesh> m_meshs;
};

} // namespace Hina
