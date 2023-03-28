#include "hnpch.h"
#include "Model.h"

namespace Hina
{

Model::Model(const std::string &path) : m_path(path) {
    HN_PROFILE_FUNCTION();

    ImportScene(m_path);
}

Model::Model(std::string &&path) : m_path(path) {
    HN_PROFILE_FUNCTION();

    ImportScene(m_path);
}

void Model::Draw(const std::shared_ptr<Shader> &pShader) const {
    for(const auto &mesh : m_meshs) {
        mesh.Draw(pShader);
    }
}

void Model::ImportScene(const std::string &path) {
    HN_PROFILE_FUNCTION();

    timer.Reset();

    Assimp::Importer importer;
    const aiScene *pScene = nullptr;

    {
        HN_PROFILE_SCOPE("const aiScene *Importer::ReadFile(const std::string &pFile, unsigned int pFlags)");
        pScene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded | aiProcess_PreTransformVertices);
    }

    if(nullptr != pScene) {
        ProcessScene(pScene);
    }
    else {
        HN_CORE_ERROR("Import model failed at {0}", path);
    }

    HN_CORE_TRACE("    Loading model used {0} seconds", timer.ElapsedSeconds());
}

void Model::ProcessScene(const aiScene *pScene) {
    HN_CORE_INFO("Loading model {0}", m_path);
    HN_CORE_TRACE("Model details:");
    HN_CORE_TRACE("    Mesh count: {0}", pScene->mNumMeshes);
    HN_CORE_TRACE("    Material count: {0}", pScene->mNumMaterials);
    HN_CORE_TRACE("    Texture count: {0}", pScene->mNumTextures);

    m_meshs.reserve(pScene->mNumMeshes);
    ProcessNode(pScene, pScene->mRootNode);
}

void Model::ProcessNode(const aiScene *pScene, const aiNode *pNode) {
    for(size_t i = 0; i < pNode->mNumMeshes; ++i) {
        aiMesh *mesh = pScene->mMeshes[pNode->mMeshes[i]];
        ProcessMesh(pScene, mesh);
    }
    
    // Recursive.
    for(size_t i = 0; i < pNode->mNumChildren; i++) {
        ProcessNode(pScene, pNode->mChildren[i]);
    }
}

void Model::ProcessMesh(const aiScene *pScene, const aiMesh *pMesh) {
    HN_CORE_TRACE("        Mesh name: {0}", pMesh->mName.C_Str());
    HN_CORE_TRACE("        Vertex count: {0}", pMesh->mNumVertices);
    HN_CORE_TRACE("        Index count: {0}", pMesh->mNumFaces * 3);

    std::vector<Vertex> vertices;
    std::vector<Index> indices;

    vertices.reserve(pMesh->mNumVertices);
    indices.reserve(pMesh->mNumFaces * 3);
    HN_CORE_ASSERT(pMesh->mFaces[0].mNumIndices == 3, "Hina only supports triangle face!");

    for(size_t i = 0; i < pMesh->mNumVertices; ++i) {
        Vertex vertex;

        // 1. Position
        const auto &aiPosition = pMesh->mVertices[i];
        auto &position = vertex.GetPosition();
        position.x = aiPosition.x;
        position.y = aiPosition.y;
        position.z = aiPosition.z;

        // 2. Normal
        const auto &aiNormal = pMesh->mNormals[i];
        auto &normal = vertex.GetNormal();
        normal.x = aiNormal.x;
        normal.y = aiNormal.y;
        normal.z = aiNormal.z;

        // 3. Tangent
        const auto &aiTangent = pMesh->mTangents[i];
        auto &tangent = vertex.GetTangent();
        tangent.x = aiTangent.x;
        tangent.y = aiTangent.y;
        tangent.z = aiTangent.z;

        // 4. UV
        const auto &aiUv = pMesh->mTextureCoords[0][i];
        auto &uv = vertex.GetUV();
        uv.x = aiUv.x;
        uv.y = aiUv.y;

        vertices.emplace_back(std::move(vertex));
    }

    // 5. Index
    for(size_t i = 0; i < pMesh->mNumFaces; ++i) {
        aiFace face = pMesh->mFaces[i];

        for(size_t j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }

    Mesh mesh;
    mesh.SetVertices(std::move(vertices));
    mesh.SetIndices(std::move(indices));
    mesh.CreateVertexArray();
    m_meshs.emplace_back(std::move(mesh));
}

} // namespace Hina
