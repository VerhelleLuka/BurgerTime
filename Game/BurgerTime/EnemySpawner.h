#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "BaseComponent.h"
#include <Structs.h>
#include "Observer.h"
#include "Enemy.h"
namespace dae
{
	struct EnemyKilledArgs : EventArgs{
		EnemyType enemyType;
	};
	class Scene;
	enum class Difficulty
	{
		EASY,
		NORMAL,
		HARD
	};
	class EnemySpawner final : public BaseComponent, public Observer
	{
	public:
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float /*deltaTime*/) override {};
		virtual void Render() const override {};

		EnemySpawner(Difficulty difficulty);
		virtual ~EnemySpawner() {};

		virtual void Initialize(Scene& /*scene*/) override;

		void SetDifficulty(Difficulty difficulty);
		void SetSpawnPositions(std::vector<Float2> spawnPositions) { m_SpawnPositions = spawnPositions; }
		virtual void OnNotify(EventType /*event_*/, std::shared_ptr<EventArgs> /*args*/) override;

		void SpawnEnemy();
	protected:
		GameObject* m_pParent{};

		Difficulty m_Difficulty;
		int m_MaxEnemies;
		int m_NumEnemies;
		float m_EnemyRespawnTimer;
		float m_EnemyRespawnTime;

		std::vector<Float2> m_SpawnPositions;

		bool m_EggPresent;
	};
}
