#pragma once

#include "RigidBodyComponent.h"
namespace dae
{
	class SpriteComponent;
	class EnemyState
	{
	public:
		virtual ~EnemyState() = default;
		virtual void Update() {};
		void SetRigidBody(RigidBodyComponent* rigidBody) { m_pRigidBody = rigidBody; }
		void SetSprite(SpriteComponent* sprite) { m_pSprite = sprite; }
	protected:
		RigidBodyComponent* m_pRigidBody;
		SpriteComponent* m_pSprite;
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

