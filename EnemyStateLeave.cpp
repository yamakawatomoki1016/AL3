#include "EnemyStateLeave.h"
#include "Enemy.h"
#include "EnemyStateApproach.h"

void EnemyStateLeave::Update(Enemy* enemy) {
	Vector3 kCharctorSpeed = {-0.5f, 0.5f, 0.0f};
	enemy->Move(kCharctorSpeed);
}
