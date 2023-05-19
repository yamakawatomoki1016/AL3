#include "Enemy.h"
#include <assert.h>
void Enemy::Initialize(Model* model, const Vector3& position) {
	assert(model);
	model_ = model;
	texturehandle_ = TextureManager::Load("Enemy.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}

void Enemy::Update() {
	Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = 0.2f;

	move.z -= kCharacterSpeed;
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view, texturehandle_);
}