#pragma once
#include "IEnemyState.h"
class EnemyStateLeave:public IEnemyState {
public:
	void Update()override;
	void Initialize(Enemy*enemy) override;

};
