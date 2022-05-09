#pragma once
#include "RigidBodyComponent.h"

namespace dae
{
	class Physics : public Subject
	{
	public:
		Physics() {};
		~Physics() = default;

		Physics(const Physics& other) = delete;
		Physics(Physics&& other) = delete;
		Physics& operator=(const Physics& other) = delete;
		Physics& operator=(Physics&& other) = delete;

		void AddRigidBodyComponent(std::shared_ptr<RigidBodyComponent> rigidBody);

		void FixedUpdate(float deltaTime);
		void CheckOverlap();

	private:
		std::vector<std::shared_ptr<RigidBodyComponent>> m_pRigidBodies;
	};
}
