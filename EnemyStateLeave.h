#pragma once

#include "IEnemyState.h"

class EnemyStateLeave : public IEnemyState {
public:
	void Update(Enemy* enemy) override;
};
