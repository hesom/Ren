#include <iostream>
#include <memory>
#include <rengine.h>
#include "glm/gtc/matrix_transform.hpp"

int main()
{
	using namespace ren;
	Rengine engine;

    const auto camera = std::make_shared<FPSCamera>();
    engine.setMainCamera(camera);

    auto well = EntityManager::loadFromFile("well.coveredopen.obj");
    glm::mat4 transformation = glm::mat4(1.0f);
    transformation = glm::translate(transformation, glm::vec3(-2.0f, -0.25f, 0.0f));
    well->setTransformation(transformation);

    auto table = EntityManager::loadFromFile("table_medieval_trestle.obj");
    transformation = glm::mat4(1.0f);
    transformation = glm::translate(transformation, glm::vec3(3.0f, -0.25f, 0.0f));
    table->setTransformation(transformation);

    EntityManager::addDirectionalLight(glm::vec3(0.0f, 10000.0f, 3000.0f), glm::vec3(3.0f));
    WaterRenderer::addTile(std::make_shared<WaterTile>(0.0f, 0.0f, 0.0f));
    
    EntityRenderer::setDefaultShader("ToonShader");
    
	engine.start();
}