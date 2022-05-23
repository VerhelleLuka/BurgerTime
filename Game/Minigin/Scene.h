#pragma once
#include "SceneManager.h"
#include "RigidBodyComponent.h"
namespace dae
{
	class SceneObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<SceneObject>& object);

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);

		std::vector<std::shared_ptr<SceneObject>>& GetSceneObjects() { return m_Objects; }
		void Render() const;
		const std::string& GetName() const { return m_Name; }
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < std::shared_ptr<SceneObject>> m_Objects{};


		static unsigned int m_IdCounter; 
	};

}
