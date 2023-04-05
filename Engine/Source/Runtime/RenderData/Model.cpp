#include "hnpch.h"
#include "Model.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace Hina
{

namespace Utils
{

inline glm::vec3 GetAABBMax(const aiAABB &aabb) {
    return { aabb.mMax.x, aabb.mMax.y, aabb.mMax.x };
}

inline glm::vec3 GetAABBMin(const aiAABB &aabb) {
    return { aabb.mMin.x, aabb.mMin.y, aabb.mMin.x };
}

} // namespace Utils

Model::Model(const std::string &name, const MaterialType &type, const std::string &path)
    : m_materialType(type), m_name(name), m_path(path) {

    HN_PROFILE_FUNCTION();

    ImportScene(m_path);
}

Model::Model(std::string &&name, const MaterialType &type, std::string &&path)
    : m_materialType(type), m_name(std::move(name)), m_path(std::move(path)) {

    HN_PROFILE_FUNCTION();

    ImportScene(m_path);
}

void Model::Draw(const std::shared_ptr<Shader> &pShader, const glm::mat4 &trans) const {
    HN_PROFILE_FUNCTION();

    if(m_isLoaded) {
        for(const auto &mesh : m_meshs) {
            mesh.Draw(pShader, trans);
        }
    }
}

void Model::ImportScene(const std::string &path) {
    HN_PROFILE_FUNCTION();

    m_timer.Reset();

    Assimp::Importer importer;
    const aiScene *pScene = nullptr;

    {
        HN_PROFILE_SCOPE("const aiScene *Importer::ReadFile(const std::string &pFile, unsigned int pFlags)");
        pScene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_GenBoundingBoxes | aiProcess_PreTransformVertices);
    }

    if(pScene) {
        ProcessScene(pScene);

        m_isLoaded = true;

        HN_CORE_TRACE("");
        HN_CORE_TRACE("    Loading model used {0} seconds", m_timer.ElapsedSeconds());
        HN_CORE_TRACE("    {0} aabb max: {1}", m_name, m_aabb.GetMax());
        HN_CORE_TRACE("    {0} aabb min: {1}", m_name, m_aabb.GetMin());
    }
    else {
        HN_CORE_ERROR("Import model failed at {0}", path);
    }
}

void Model::ProcessScene(const aiScene *pScene) {
    HN_CORE_INFO("Loading model {0} at {1}", m_name, m_path);
    HN_CORE_TRACE("Model details:");
    HN_CORE_TRACE("    Scene name: {0}", pScene->mName.C_Str());
    HN_CORE_TRACE("    Mesh count: {0}", pScene->mNumMeshes);
    HN_CORE_TRACE("    Material count: {0}", pScene->mNumMaterials);

    // Init m_aabb by the first AABB of meshes.
    const auto &aiAABB = pScene->mMeshes[0]->mAABB;
    m_aabb.SetMax(Utils::GetAABBMax(aiAABB));
    m_aabb.SetMin(Utils::GetAABBMin(aiAABB));

    m_meshs.reserve(pScene->mNumMeshes);
    ProcessNode(pScene, pScene->mRootNode);
}

void Model::ProcessNode(const aiScene *pScene, const aiNode *pNode) {
    HN_CORE_TRACE("");
    HN_CORE_TRACE("        Node name: {0}", pNode->mName.C_Str());
    HN_CORE_TRACE("        Children count: {0}", pNode->mNumChildren);
    HN_CORE_TRACE("        Mesh count: {0}", pNode->mNumMeshes);

    for(size_t meshIndex = 0; meshIndex < pNode->mNumMeshes; ++meshIndex) {
        aiMesh *mesh = pScene->mMeshes[pNode->mMeshes[meshIndex]];
        ProcessMesh(pScene, mesh);
    }
    
    // Recursive.
    for(size_t nodeIndex = 0; nodeIndex < pNode->mNumChildren; ++nodeIndex) {
        ProcessNode(pScene, pNode->mChildren[nodeIndex]);
    }
}

void Model::ProcessMesh(const aiScene *pScene, const aiMesh *pMesh) {
    HN_CORE_TRACE("");
    HN_CORE_TRACE("            Mesh name: {0}", pMesh->mName.C_Str());
    HN_CORE_TRACE("            Vertex count: {0}", pMesh->mNumVertices);
    HN_CORE_TRACE("            Index count: {0}", pMesh->mNumFaces * 3);

    const auto &aiAABB = pMesh->mAABB;
    m_aabb.AddPoint(Utils::GetAABBMax(aiAABB));
    m_aabb.AddPoint(Utils::GetAABBMin(aiAABB));

    ////////////////////////////// VERTEX //////////////////////////////

    std::vector<Vertex> vertices;
    vertices.reserve(pMesh->mNumVertices);

    for(size_t vertexIndex = 0; vertexIndex < pMesh->mNumVertices; ++vertexIndex) {
        Vertex vertex;

        // 1. Position
        if(pMesh->HasPositions()) {
            const auto &aiPosition = pMesh->mVertices[vertexIndex];
            auto &position = vertex.GetPosition();
            position.x = aiPosition.x;
            position.y = aiPosition.y;
            position.z = aiPosition.z;
        }

        // 2. Normal
        if(pMesh->HasNormals()) {
            const auto &aiNormal = pMesh->mNormals[vertexIndex];
            auto &normal = vertex.GetNormal();
            normal.x = aiNormal.x;
            normal.y = aiNormal.y;
            normal.z = aiNormal.z;
        }

        // 3. Tangent
        if(pMesh->HasTangentsAndBitangents()) {
            const auto &aiTangent = pMesh->mTangents[vertexIndex];
            auto &tangent = vertex.GetTangent();
            tangent.x = aiTangent.x;
            tangent.y = aiTangent.y;
            tangent.z = aiTangent.z;
        }

        // 4. UV
        if(pMesh->HasTextureCoords(0)) {
            const auto &aiUv = pMesh->mTextureCoords[0][vertexIndex];
            auto &uv = vertex.GetUV();
            uv.x = aiUv.x;
            uv.y = aiUv.y;
        }

        // TODO : Bone

        vertices.emplace_back(std::move(vertex));
    }

    ////////////////////////////// INDEX //////////////////////////////

    HN_CORE_ASSERT(pMesh->mFaces[0].mNumIndices == 3, "Hina only supports triangle face!");

    std::vector<Index> indices;
    indices.reserve(pMesh->mNumFaces * 3);
    
    for(size_t faceIndex = 0; faceIndex < pMesh->mNumFaces; ++faceIndex) {
        aiFace face = pMesh->mFaces[faceIndex];
        for(size_t indexIndex = 0; indexIndex < face.mNumIndices; ++indexIndex) {
            indices.push_back(static_cast<Index>(face.mIndices[indexIndex]));
        }
    }

    ////////////////////////////// MATERIAL //////////////////////////////

    Material material(m_materialType);

    if(pMesh->mMaterialIndex >= 0) {
        const aiMaterial *pMaterial = pScene->mMaterials[pMesh->mMaterialIndex];
        material.Load(m_path, pMaterial);
    }

    ////////////////////////////// MESH //////////////////////////////

    Mesh mesh;
    mesh.SetVertices(std::move(vertices));
    mesh.SetIndices(std::move(indices));
    mesh.CreateVertexArray();

    mesh.Setmaterial(std::move(material));
    
    m_meshs.emplace_back(std::move(mesh));
}

} // namespace Hina
