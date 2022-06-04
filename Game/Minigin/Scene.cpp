#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "Physics.h"
using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name),
	m_MarkedForDestroy(false)
{}

Scene::~Scene() = default;


void Scene::Initialize()
{
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->Initialize(*this);
	}
}
void Scene::Add(const std::shared_ptr<SceneObject>&object)
{
	m_Objects.push_back(object);
}

void Scene::Update(float deltaTime)
{
	//int i{};

	for (size_t i = 0; i < m_Objects.size(); i++)
	{

		m_Objects[i]->Update(deltaTime);
		if (m_Objects[i]->GetMarkForDelete())
		{
			m_Objects[i] = nullptr;
			m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), m_Objects[i]), m_Objects.end());
		}
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

