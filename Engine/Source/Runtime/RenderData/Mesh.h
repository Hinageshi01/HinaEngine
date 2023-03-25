#pragma once

#include "RenderCore/VertexArray.h"
#include "RenderCore/Shader.h"
#include "RenderData/Vertex.h"

namespace Hina
{

class Mesh final
{
public:
	void Draw(const std::shared_ptr<Shader> &pShader) const;

	void CreateVertexArray();
	VertexArray &GetVertexArray() { return *m_pVertexArray; }
	const VertexArray &GetVertexArray() const { return *m_pVertexArray; }

	void SetVertices(std::vector<Vertex> &&vertices) { m_vertices = vertices; }
	void SetVertices(const std::vector<Vertex> &vertices) { m_vertices = vertices; }
	void SetVertex(const size_t index, const Vertex &vertex) { m_vertices[index] = vertex; }
	void AddVertex(const Vertex &vertex) { m_vertices.push_back(vertex); }
	void AddVertex(Vertex &&vertex) { m_vertices.emplace_back(vertex); }
	std::vector<Vertex> &GetVertices() { return m_vertices; }
	const std::vector<Vertex> &GetVertices() const { return m_vertices; }
	Vertex &GetVertex(const size_t index) { return m_vertices[index]; }
	const Vertex &GetVertex(const size_t index) const { return m_vertices.at(index); }
	size_t GetVerticesCount() const { return m_vertices.size(); }

	void SetIndices(std::vector<uint32_t> &&indices) { m_indices = indices; }
	void SetIndices(const std::vector<uint32_t> &indices) { m_indices = indices; }
	void SetIndex(const size_t _index, const uint32_t &index) { m_indices[_index] = index; }
	void AddIndex(const uint32_t &index) { m_indices.push_back(index); }
	void AddIndex(uint32_t &&index) { m_indices.emplace_back(index); }
	std::vector<uint32_t> &GetIndices() { return m_indices; }
	const std::vector<uint32_t> &GetIndices() const { return m_indices; }
	uint32_t &GetIndex(const size_t index) { return m_indices[index]; }
	const uint32_t &GetIndex(const size_t index) const { return m_indices.at(index); }
	size_t GetIndicesCount() const { return m_indices.size(); }

private:
	const float *GetVerticesData() const;

	std::shared_ptr<VertexArray> m_pVertexArray;

	std::vector<Vertex> m_vertices;
	std::vector<uint32_t> m_indices;
	// material
};

} // namespace Hina
