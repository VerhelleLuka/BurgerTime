#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}
}

void dae::Scene::FixedUpdate(float deltaTime)
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate(deltaTime);
	}
}

void Scene::Render() const
{
	//Render objects with lower z axis first

	std::vector<SceneObject*> lowerZAxisObjects;
	for (const auto& object : m_Objects)
	{
		if (dynamic_cast<GameObject*>(object.get())->GetTransform().GetPosition().z >= 0)
		{
			lowerZAxisObjects.push_back(object.get());
		}
		else
		{
			object->Render();
		}
		
	}
	for (const auto& remainingObjects : lowerZAxisObjects)
	{
		remainingObjects->Render();
			
	}
}

