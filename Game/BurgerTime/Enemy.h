#pragma once
#include "RigidBodyComponent.h"
#include "BaseComponent.h"
#include "EnemyState.h"
#include "PeterPepper.h"
#include "Scene.h"
namespace dae
{
	class Enemy final : public BaseComponent
	{
	public:
		virtual void Update(float /*deltaTime*/) {};
		virtual void FixedUpdate(float /*deltaTime*/) override;
		virtual void Render() const {};
		void Initialize(Scene& scene);
		Enemy();
		virtual ~Enemy();

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

		void SetOverlapEvent();

		void SetOnTriggerExitEvent();

		bool GetInMenu() const { return m_InMenu; }
		void SetInMenu(bool inGameScene) { m_InMenu = inGameScene; }

	private:
		//Terrain related
		bool m_CanClimb;
		bool m_CanDescend;
		bool m_CanWalkLeft;
		bool m_CanWalkRight;

		bool m_InMenu;
		bool m_OverlappingLadder;
		bool m_OverlappingPlatform;
		void OnOverlap(RigidBodyComponent* /*other*/);
		void OnTriggerExit(RigidBodyComponent* /*other*/);

		EnemyState* m_pEnemyState;

		PeterPepperComponent* m_pPeter1Ref;
		PeterPepperComponent* m_pPeter2Ref;
		
	};
}