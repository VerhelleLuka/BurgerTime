#pragma once
#include "Scene.h"

namespace dae
{
	class Physics
	{
	public:
		Physics(Scene& scene);
		~Physics();

		Physics(const Physics& other) = delete;
		Physics(Physics&& other) = delete;
		Physics& operator=(const Physics& other) = delete;
		Physics& operator=(Physics&& other) = delete;

	private:
		std::vector<SceneObject*> m_pSceneObjects;
	};
}
