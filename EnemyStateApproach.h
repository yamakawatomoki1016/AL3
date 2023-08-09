#pragma once
#include "IEnemyState.h"
class EnemyStateApproach:public IEnemyState {
public:
	void Update()override;
	void Initialize(Enemy*enemy) override;
};
