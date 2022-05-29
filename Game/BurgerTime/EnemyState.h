#pragma once

#include "RigidBodyComponent.h"
namespace dae
{
	class SpriteComponent;
	class Enemy;
	class EnemyState
	{
	public:
		virtual ~EnemyState() = default;
		virtual void Update() {};
		void SetRigidBody(RigidBodyComponent* rigidBody) { m_pRigidBody = rigidBody; }
		void SetSprite(SpriteComponent* sprite) { m_pSprite = sprite; }
		void SetEnemy(Enemy* enemy) { m_pEnemy = enemy; }
		void SetWalking(bool walking) { m_WalkingPlatform = walking; }
		bool GetWalking() const { return m_WalkingPlatform; }

		void SetClimbing(bool climbing) { m_ClimbingLadder = climbing; }
		bool GetClimbing() { return m_ClimbingLadder;  }
	protected:

	 RigidBodyComponent* m_pRigidBody;
	 SpriteComponent* m_pSprite;
	 Enemy* m_pEnemy;

		bool m_ClimbingLadder;
		bool m_WalkingPlatform;

	//	void SetWalkingLeft(bool walkingLeft) { m_WalkingLeft = walkingLeft; }
	//	bool GetWalkingLeft() const { return m_WalkingLeft; }

	//	void SetWalkingRight(bool walkingRight) { m_WalkingRight = walkingRight; }
	//	bool GetWalkingRight() const { return m_WalkingRight; }

	//	void SetClimbing(bool climbing) { m_Climbing = climbing; }
	//	bool GetClimbing() { return m_Climbing; }

	//	void SetDescending(bool descending) { m_Descending = descending; }
	//	bool GetDescending() { return m_Descending; }
	//protected:
	//	RigidBodyComponent* m_pRigidBody;
	//	SpriteComponent* m_pSprite;

	//	bool m_Climbing;
	//	bool m_Descending;
	//	bool m_WalkingLeft;
	//	bool m_WalkingRight;
	};

	class MovingLeft final : public EnemyState
	{
	public:
		virtual void Update() override;
	};

	class MovingUp final : public EnemyState
	{
	public:
		virtual void Update() override;
	};
	class MovingRight final : public EnemyState
	{
	public:
		virtual void Update() override;
	};

	class MovingDown final : public EnemyState
	{
	public:
		virtual void Update() override;
	};
}

