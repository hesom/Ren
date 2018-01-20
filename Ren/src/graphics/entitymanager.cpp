#include "graphics/entitymanager.h"
#include <iostream>
#include "glm/glm.hpp"
#include "glad/glad.h"
#include "util/stb_image.h"

namespace ren
{
    class Entity;

    std::vector<std::shared_ptr<Entity>> EntityManager::m_entities;
    std::vector<std::shared_ptr<DirectionalLight>> EntityManager::m_directionalLights;

    auto EntityManager::loadFromOBJ(std::string path) -> std::shared_ptr<Entity>
    {
        //http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
        std::vector<glm::vec3> temp_positions;
        std::vector<glm::vec2> temp_uvs;
        std::vector<glm::vec3> temp_normals;

        FILE* file;

        if (fopen_s(&file, path.c_str(), "r") == 0) {
            while (true) {
                char lineHeader[128];
                int res = fscanf(file, "%s", lineHeader);
                if (res == EOF)
                    break;
                if (strcmp(lineHeader, "v") == 0) {
                    glm::vec3 position;
                    fscanf(file, "%f %f %f\n", &position.x, &position.y, &position.z);
                    temp_positions.push_back(position);
                }
                else if (strcmp(lineHeader, "vt") == 0) {
                    glm::vec2 uv;
                    fscanf(file, "%f %f\n", &uv.x, &uv.y);
                    temp_uvs.push_back(uv);
                }
                else if (strcmp(lineHeader, "vn") == 0) {
                    glm::vec3 normal;
                    fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
                    temp_normals.push_back(normal);
                }
                else if (strcmp(lineHeader, "f") == 0) {
                    std::string vertex1, vertex2, vertex3;
                    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                    int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                                           &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                           &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                                           &vertexIndex[2], &uvIndex[2], &normalIndex[2]
                    );
                    if (matches != 9) {
                        printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                        return false;
                    }
                    vertexIndices.push_back(vertexIndex[0]);
                    vertexIndices.push_back(vertexIndex[1]);
                    vertexIndices.push_back(vertexIndex[2]);
                    uvIndices.push_back(uvIndex[0]);
                    uvIndices.push_back(uvIndex[1]);
                    uvIndices.push_back(uvIndex[2]);
                    normalIndices.push_back(normalIndex[0]);
                    normalIndices.push_back(normalIndex[1]);
                    normalIndices.push_back(normalIndex[2]);
                }
            }
        }
        else {
            std::cout << "Impossible to open the file!" << std::endl;
            return nullptr;
        }

        for (unsigned int i = 0; i < vertexIndices.size(); i++) {
            Vertex v;
            unsigned int vertexIndex = vertexIndices[i];
            v.position = temp_positions[vertexIndex - 1];
            unsigned int uvIndex = uvIndices[i];
            v.uv.x = temp_uvs[uvIndex - 1].x;
            v.uv.y = 1 - temp_uvs[uvIndex - 1].y;
            unsigned int normalIndex = normalIndices[i];
            v.normal = temp_normals[normalIndex - 1];

            vertices.push_back(v);
            indices.push_back(i);
            
        }

        auto mesh = std::make_shared<Mesh>(vertices, indices);

        //extensions for diffuse, normal and specular map
        std::string diffExt = "diffuse.jpg";
        std::string normExt = "normal.jpg";
        std::string specExt = "specular.jpg";

        std::string diffPath = path;
        std::string normPath = path;
        std::string specPath = path;

        auto diffTex = std::make_shared<Texture>();
        auto normTex = std::make_shared<Texture>();
        auto specTex = std::make_shared<Texture>();

        auto extIndex = path.rfind('.', path.length());
        if (extIndex != std::string::npos) {
            diffPath.replace(extIndex + 1, diffExt.length(), diffExt);
            normPath.replace(extIndex + 1, normExt.length(), normExt);
            specPath.replace(extIndex + 1, specExt.length(), specExt);
        }

        int width, height, channels;
        unsigned char* diffData = stbi_load(diffPath.c_str(), &width, &height, &channels, 0);
        diffTex->allocate(width, height, GL_TRUE, GL_RGB8);
        diffTex->buffer(diffData);

        unsigned char* normData = stbi_load(normPath.c_str(), &width, &height, &channels, 0);
        normTex->allocate(width, height, GL_TRUE, GL_RGB8);
        normTex->buffer(normData);

        unsigned char* specData = stbi_load(specPath.c_str(), &width, &height, &channels, 0);
        specTex->allocate(width, height, GL_TRUE, GL_RGB8);
        specTex->buffer(specData);

        stbi_image_free(diffData);
        stbi_image_free(normData);
        stbi_image_free(specData);


        m_entities.push_back(std::make_shared<Entity>(mesh, diffTex, normTex, specTex));

        mesh->setupBuffer();

        return m_entities.at(m_entities.size()-1);
    }

    auto EntityManager::addDirectionalLight(glm::vec3 position, float intensity) -> std::shared_ptr<DirectionalLight>
    {
        m_directionalLights.push_back(std::make_shared<DirectionalLight>(position, intensity));
        return m_directionalLights.at(m_directionalLights.size()-1);
    }

    auto EntityManager::get(size_t handle) -> std::shared_ptr<Entity>
    {
        return m_entities.at(handle);
    }

    auto EntityManager::render() -> void
    {
        glEnable(GL_DEPTH_TEST);
        for (auto entity : m_entities) {
            entity->render();
        }
        glDisable(GL_DEPTH_TEST);
    }
}

