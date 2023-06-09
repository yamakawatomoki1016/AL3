#include "Enemy.h"
#include <assert.h>

void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	model_ = model;
	texturehandle_ = TextureManager::Load("Enemy.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
}

void Enemy::Update() {
	worldTransform_.UpdateMatrix();
	/*worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);*/
	switch (phase_) {
	case Phase::Approach:
		Approach();
		break;
	case Phase::Leave:
		Leave();
		break;
	case Phase::start:

		break;
	default:
		break;
	}
}

void Enemy::Approach() {
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	if (worldTransform_.translation_.z < -15.0f) {

		phase_ = Phase::Leave;
	}
}

void Enemy::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view, texturehandle_);
}

void Enemy::Leave() {

	worldTransform_.translation_ = Add(worldTransform_.translation_, {-0.5f, 0.5f, 0.0f});
}