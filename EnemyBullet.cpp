#include "EnemyBullet.h"
#include "MathFunction.h"
#include <assert.h>
void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	texturehandle_ = TextureManager::Load("EnemyBullet.png");
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
	worldTransform_.scale_.x = 0.5f;
	worldTransform_.scale_.y = 0.5f;
	worldTransform_.scale_.z = 3.0f;
	worldTransform_.rotation_.y = std::atan2(velocity_.x,velocity_.z);
	float velocityXZ = Length({velocity_.x, 0.0f, velocity_.z});
	worldTransform_.rotation_.x = std::atan2(-velocity_.y, velocityXZ);
}

void EnemyBullet::Update() {
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
	Vector3 toPlayer = Subtract(player_->GetWorldPosition(), worldTransform_.translation_);
	toPlayer = Normalize(toPlayer);
	velocity_ = Normalize(velocity_);
	velocity_ = Slerp(velocity_, toPlayer, 0.1f);
	worldTransform_.rotation_.y = std::atan2(velocity_.x, velocity_.z);
	float velocityXZ = Length({velocity_.x, 0.0f, velocity_.z});
	worldTransform_.rotation_.x = std::atan2(-velocity_.y, velocityXZ);
	worldTransform_.UpdateMatrix();
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
}

void EnemyBullet::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view, texturehandle_);
}