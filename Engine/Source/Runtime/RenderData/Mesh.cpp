#include "hnpch.h"
#include "Mesh.h"

#include "RenderCore/RenderCore.h"

namespace Hina
{

void Mesh::Draw(const std::shared_ptr<Shader> &pShader, const glm::mat4 &trans) const {
	HN_PROFILE_FUNCTION();

	RenderCore::Submit(pShader, m_pVertexArray, trans);
}

void Mesh::CreateVertexArray() {
	HN_PROFILE_FUNCTION();

	assert(!m_vertices.empty() && !m_indices.empty() && "Empty buffers!");

	std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(m_vertices.size() * sizeof(Vertex), GetVerticesData());
	vertexBuffer->SetLayout(Vertex::GetLayOut());
	std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(m_indices.size() * sizeof(Index), m_indices.data());

	m_pVertexArray = VertexArray::Create();
	m_pVertexArray->AddVertexBuffer(vertexBuffer);
	m_pVertexArray->SetIndexBuffer(indexBuffer);

	m_vertices.clear();
	m_vertices.shrink_to_fit();
	m_indices.clear();
	m_indices.shrink_to_fit();
}

const float *Mesh::GetVerticesData() const {
	assert(!m_vertices.empty() && "Empty vertex buffer!");
	return m_vertices.data()->Data();
}

} // namespace Hina
