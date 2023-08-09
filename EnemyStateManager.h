#pragma once
#include "IEnemyState.h"
#include "EnemyStateApproach.h"
#include "EnemyStateLeave.h"

class EnemyStateManager {

public:
	void Update();
	void ChangeState(IEnemyState* state);
	void Initialize(Enemy* enemy);
	~EnemyStateManager();

private:
	IEnemyState* state_;
	Enemy* enemy_;
};
