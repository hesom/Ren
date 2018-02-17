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

        auto loadModel(std::string path) -> void;
        auto processNode(aiNode *node, const aiScene *scene) -> void;
        auto processMesh(aiMesh *mesh, const aiScene *scene) -> std::shared_ptr<Mesh>;
        auto loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) -> std::vector<Texture>;
    public:
        Model(const char *path);
        auto render(std::shared_ptr<ShaderProgram> shader) -> void;
    };
}