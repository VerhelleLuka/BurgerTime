#pragma once
#include "Enemy.h"
class EnemyState
{
public:
	static MovingHorizontal m_MovingHorizontal;
	static MovingVertical m_MovingVertical;

	virtual ~EnemyState() {};
protected:
	virtual void Update(Enemy& enemy) = 0;
};

class MovingHorizontal final : public EnemyState
{
protected:
	virtual void Update(Enemy& enemy) override
	{

	}

private: 
	bool m_MovingLeft;
};

class MovingVertical final : public EnemyState
{
protected:
	virtual void Update(Enemy& enemy) override
	{

	}

private:
	bool m_MovingUp;
};