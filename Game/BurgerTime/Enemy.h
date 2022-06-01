#pragma once
#include "RigidBodyComponent.h"
#include "BaseComponent.h"
#include "EnemyState.h"
#include "PeterPepper.h"
#include "Scene.h"
namespace dae
{
	class LadderComponent;
	enum class EnemyType
	{
		EGG,
		SAUSAGE,
		PICKLE
	};
	class Enemy final : public BaseComponent
	{
	public:
		virtual void Update(float /*deltaTime*/) override;
		virtual void FixedUpdate(float /*deltaTime*/) override;
		virtual void Render() const {};
		void Initialize(Scene& scene);
		void Reinitialize();
		Enemy(EnemyType type);
		virtual ~Enemy();

		//void ReduceLife();
		//int GetLives() { return m_Lives; }
		//void AddPoints(int points);
		//int GetPoints() { return m_Points; }
		//void ButtonPress();
		//void ChangeState(int state);

		bool GetCanClimb() const { return m_CanClimb; }
		bool GetCanDescend() const { return m_CanDescend; }
		bool GetCanWalkLeft() const { return m_CanWalkLeft; }
		bool GetCanWalkRight() const { return m_CanWalkRight; }
		EnemyType GetEnemyType() const { return m_EnemyType; }

		void SetOverlapEvent();

		void SetOnTriggerExitEvent();
		bool IsDead() const { return m_IsDead; }
		void Kill();
		void Fall();
		bool GetFalling() const { return m_IsFalling; }
		//Enemy* clone(Float2 pos)
		//{
		//	retu
		//}
	private:
		//Terrain related
		bool m_CanClimb;
		bool m_CanDescend;
		bool m_CanWalkLeft;
		bool m_CanWalkRight;

		bool m_OverlappingLadder;
		bool m_OverlappingPlatform;
		void OnOverlap(RigidBodyComponent* /*other*/);
		void OnTriggerExit(RigidBodyComponent* /*other*/);

		EnemyState* m_pEnemyState;
		EnemyType m_EnemyType;
		Transform* m_pPeter1Transform;
		Transform* m_pPeter2Transform;

		LadderComponent* m_pWalkedLadder;
		bool m_Initialized;
		const float m_BehaviorSwitchTimer{ 0.7f };
		float m_BehaviorSwitchTime;
		bool m_SwitchBehavior;
		bool m_IsDead;
		bool m_IsFalling;
		
	};
}