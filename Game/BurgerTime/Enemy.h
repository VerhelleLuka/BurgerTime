#pragma once
#include "RigidBodyComponent.h"s
#include "EnemyState.h"
namespace dae
{
	class Enemy final : public BaseComponent
	{
	public:
		virtual void Update(float deltaTime);
		virtual void FixedUpdate(float /*deltaTime*/) override;
		virtual void Render() const {};

		Enemy();
		virtual ~Enemy() {};

		//void ReduceLife();
		//int GetLives() { return m_Lives; }
		//void AddPoints(int points);
		//int GetPoints() { return m_Points; }
		//void ButtonPress();
		//void ChangeState(int state);

		//bool GetCanClimb() const { return m_CanClimb; }
		//bool GetCanDescend() const { return m_CanDescend; }
		//bool GetCanWalkLeft() const { return m_CanWalkLeft; }
		//bool GetCanWalkRight() const { return m_CanWalkRight; }

		void SetOverlapEvent()
		{
			auto bindIng = std::bind(&Enemy::OnOverlap, this, std::placeholders::_1);
			m_pParent->GetComponent<RigidBodyComponent>("RigidBody")->SetOnOverlapEvent(bindIng);
		}
		void SetOnTriggerExitEvent()
		{
			auto bindIng = std::bind(&Enemy::OnTriggerExit, this, std::placeholders::_1);
			m_pParent->GetComponent<RigidBodyComponent>("RigidBody")->SetOnTriggerExit(bindIng);
		}

		bool GetInMenu() const { return m_InMenu; }
		void SetInMenu(bool inGameScene) { m_InMenu = inGameScene; }

	private:
		//Terrain related
		//bool m_CanClimb;
		//bool m_CanDescend;
		//bool m_CanWalkLeft;
		//bool m_CanWalkRight;

		bool m_InMenu;
		bool m_OverlappingLadder;
		bool m_OverlappingPlatform;
		void OnOverlap(RigidBodyComponent* other);
		void OnTriggerExit(RigidBodyComponent* other);

		EnemyState* m_pEnemyState;
	};
}