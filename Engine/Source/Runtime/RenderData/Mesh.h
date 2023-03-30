#pragma once

#include "RenderCore/VertexArray.h"
#include "RenderCore/Shader.h"
#include "RenderData/Vertex.h"
#include "RenderData/Material/Material.h"

namespace Hina
{

class Mesh final
{
public:
	Mesh() = default;
	Mesh(const Mesh &) = default;
	Mesh &operator=(const Mesh &) = default;
	Mesh(Mesh &&) = default;
	Mesh &operator=(Mesh &&) = default;
	~Mesh() = default;

	void Draw(const std::shared_ptr<Shader> &pShader, const glm::mat4 &trans) const;

	void CreateVertexArray();
	VertexArray &GetVertexArray() { return *m_pVertexArray; }
	const VertexArray &GetVertexArray() const { return *m_pVertexArray; }

	void Setmaterial(Material &&material) { m_material = std::move(material); }
	Material &GetMaterial() { return m_material; }
	const Material &GetMaterial() const { return m_material; }

	void SetVertices(std::vector<Vertex> &&vertices) { m_vertices = std::move(vertices); }
	void SetVertices(const std::vector<Vertex> &vertices) { m_vertices = vertices; }
	void SetVertex(const size_t index, const Vertex &vertex) { m_vertices[index] = vertex; }
	void AddVertex(const Vertex &vertex) { m_vertices.push_back(vertex); }
	void AddVertex(Vertex &&vertex) { m_vertices.emplace_back(std::move(vertex)); }
	std::vector<Vertex> &GetVertices() { return m_vertices; }
	const std::vector<Vertex> &GetVertices() const { return m_vertices; }
	Vertex &GetVertex(const size_t index) { return m_vertices[index]; }
	const Vertex &GetVertex(const size_t index) const { return m_vertices.at(index); }
	size_t GetVerticesCount() const { return m_vertices.size(); }

	void SetIndices(std::vector<Index> &&indices) { m_indices = std::move(indices); }
	void SetIndices(const std::vector<Index> &indices) { m_indices = indices; }
	void SetIndex(const size_t _index, const Index &index) { m_indices[_index] = index; }
	void AddIndex(const Index &index) { m_indices.push_back(index); }
	void AddIndex(Index &&index) { m_indices.emplace_back(std::move(index)); }
	std::vector<Index> &GetIndices() { return m_indices; }
	const std::vector<Index> &GetIndices() const { return m_indices; }
	Index &GetIndex(const size_t index) { return m_indices[index]; }
	const Index &GetIndex(const size_t index) const { return m_indices.at(index); }
	size_t GetIndicesCount() const { return m_indices.size(); }

private:
	const float *GetVerticesData() const;

	std::shared_ptr<VertexArray> m_pVertexArray;

	std::vector<Vertex> m_vertices;
	std::vector<Index> m_indices;
	Material m_material;
};

} // namespace Hina
