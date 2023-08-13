#include "EnemyStateApproach.h"
#include "Enemy.h"
#include "EnemyStateLeave.h"

void EnemyStateApproach::Update(Enemy* enemy) {
	Vector3 kCharctorSpeed = {0.0f, 0.0f, -0.5f};
	enemy->Move(kCharctorSpeed);

	if (enemy->EnemyGetPos().z < -15.0f) {
		enemy->StateChange(new EnemyStateLeave());
	}
}