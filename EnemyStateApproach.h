#pragma once

#include "IEnemyState.h"

class EnemyStateApproach : public IEnemyState {
public:
	void Update(Enemy* enemy) override;
};
