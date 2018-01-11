#include <iostream>
#include <GLFW/glfw3.h>

#include "rengine.h"
#include "ui/windowmanager.h"
#include "graphics/mesh.h"
#include "glm/glm.hpp"

namespace ren
{
	Rengine::Rengine()
	{
		createWindow();
	}

	void Rengine::start()
	{
        float vertices[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left 
        };
        unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
        };

        std::vector<Vertex> vertexData;

        for (int i = 0; i < 4; i += 3) {
            Vertex v;
            v.position = glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]);
            v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
            v.uv = glm::vec3(0.0f);
            vertexData.push_back(v);
        }
        std::vector<unsigned int> indexData;

        Mesh mesh(vertexData, indexData);
        mesh.setupBuffer(); 

        for (int i = 0; i < 6; i++) {
            indexData.push_back(indices[i]);
        }

		while (!WindowManager::exitRequested()) {
            
            mesh.draw();
			WindowManager::updateWindow();
		}

		WindowManager::destroyWindow();
	}

	void Rengine::createWindow()
	{
		WindowManager::init();
		WindowManager::createWindow(800, 600, "My Window");
	}
}
