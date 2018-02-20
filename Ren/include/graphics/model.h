#pragma once
#include <vector>
#include "graphics/mesh.h"
#include "graphics/texture.h"
#include "graphics/shaderprogram.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <memory>
#include <string>

namespace ren
{
    class Model
    {
    private:
        std::vector<std::shared_ptr<Mesh>> m_meshes;
        std::string m_directory;

        auto loadModel(const std::string& path) -> void;
        auto processNode(aiNode *node, const aiScene *scene) -> void;
        auto processMesh(aiMesh *mesh, const aiScene *scene) -> std::shared_ptr<Mesh>;
        auto loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName) -> std::vector<Texture>;
    public:
        explicit Model(const char *path);
        auto render(const std::shared_ptr<ShaderProgram>& shader) -> void;
    };
}