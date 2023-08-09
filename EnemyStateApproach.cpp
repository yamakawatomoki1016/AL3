#include "EnemyStateApproach.h"
#include "EnemyStateManager.h"
#include "EnemyStateLeave.h"
#include "Enemy.h"

void EnemyStateApproach::Update() {
	Vector3 kCharctorSpeed = {0.0f, 0.0f, -0.5f};
	enemy_->Move(kCharctorSpeed);
	if (enemy_->EnemyGetPos().z < -15.0f) {

		manager_->ChangeState(new EnemyStateLeave());
	}
}

void EnemyStateApproach::Initialize(Enemy* enemy) { 
	enemy_ = enemy; 
}
