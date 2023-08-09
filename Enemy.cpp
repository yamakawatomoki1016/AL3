#include "Enemy.h"
#include <assert.h>

void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	model_ = model;
	texturehandle_ = TextureManager::Load("Enemy.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
	stateManager_ = new EnemyStateManager();
	stateManager_->Initialize(this);
}

void Enemy::Update() {
	worldTransform_.UpdateMatrix();
	stateManager_->Update();
	
}

void Enemy::Approach() {
	
}

void Enemy::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view, texturehandle_);
}

void Enemy::Move(Vector3 velocity) {
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity);
}

void Enemy::Leave() {

	
}

void (Enemy::*Enemy::EfuncTable[])() = {
    &Enemy::Approach, &Enemy::Leave

};