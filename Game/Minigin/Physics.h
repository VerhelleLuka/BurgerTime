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
		void CheckOverlapping();

		void FixedUpdate(float deltaTime);

		bool GetOverlappingLadder() { return m_OverlappingLadder; }
		bool GetOverlappingPlatform() { return m_OverlappingPlatform; }

	private:
		std::vector<std::shared_ptr<RigidBodyComponent>> m_pRigidBodies;
		bool m_OverlappingLadder;
		bool m_OverlappingPlatform;
	};
}
