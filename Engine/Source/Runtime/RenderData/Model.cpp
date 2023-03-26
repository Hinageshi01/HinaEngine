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

void Model::ImportScene(const std::string &path) {
    HN_PROFILE_FUNCTION();

    Assimp::Importer importer;
    const aiScene *pScene = nullptr;

    {
        HN_PROFILE_SCOPE("const aiScene *Importer::ReadFile(const std::string &pFile, unsigned int pFlags)");
        pScene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_Fast | aiProcess_ConvertToLeftHanded);
    }

    if(nullptr != pScene) {
        ProcessScene(pScene);
    }
    else {
        HN_CORE_ERROR("Import model failed at {0}", path);
    }
}

void Model::ProcessScene(const aiScene *pScene) {
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
    std::vector<Vertex> vertices;
    std::vector<Index> indices;

    vertices.reserve(pMesh->mNumVertices);
    indices.reserve(pMesh->mNumFaces * 3);
    HN_CORE_ASSERT(pMesh->mFaces[0].mNumIndices == 3, "Hina only supports triangle face!");

    for(size_t i = 0; i < pMesh->mNumVertices; ++i) {
        Vertex vertex;

        std::memcpy(&vertex.GetPosition().x, &pMesh->mVertices[i].x, 3);
        std::memcpy(&vertex.GetNormal().x, &pMesh->mNormals[i].x, 3);
        std::memcpy(&vertex.GetTangent().x, &pMesh->mTangents[i].x, 3);
        std::memcpy(&vertex.GetUV().x, &pMesh->mTextureCoords[0][i].x, 2);
        // TODO : bones

        vertices.emplace_back(std::move(vertex));
    }

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
