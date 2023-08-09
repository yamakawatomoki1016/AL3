#include "EnemyStateApproach.h"
#include "EnemyStateManager.h"
#include "EnemyStateLeave.h"
#include "Enemy.h"

void EnemyStateLeave::Update() {
	Vector3 kCharctorSpeed = {-0.5f, 0.5f, 0.0f};
	enemy_->Move(kCharctorSpeed);
}

void EnemyStateLeave::Initialize(Enemy* enemy) { enemy_ = enemy; }
