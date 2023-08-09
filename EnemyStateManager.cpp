#include "EnemyStateManager.h"
#include "Enemy.h"

void EnemyStateManager::Update() { 
	state_->Update();
}

void EnemyStateManager::ChangeState(IEnemyState* state) { 
	state_ = state;
	state_->Initialize(enemy_);
}

void EnemyStateManager::Initialize(Enemy* enemy) { 
	enemy_ = enemy; 
    state_ = new EnemyStateApproach();
	state_->Initialize(enemy_);
}

EnemyStateManager::~EnemyStateManager() {  }
