#include "Enemy.h"
#include <assert.h>

void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	model_ = model;
	texturehandle_ = TextureManager::Load("Enemy.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;

	state_ = new EnemyStateApproach();
}

void Enemy::Update() {
	state_->Update(this);
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view, texturehandle_);
}

void Enemy::Move(Vector3 velocity) {
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity);
}

void Enemy::StateChange(IEnemyState* newState) { state_ = newState; }