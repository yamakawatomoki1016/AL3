#include "Enemy.h"
#include <assert.h>
Enemy::~Enemy() {
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	model_ = model;
	texturehandle_ = TextureManager::Load("Enemy.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
}

void Enemy::Update() {
	(this->*EfuncTable[static_cast<size_t>(phase_)])();
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->isDead()) {
			delete bullet;
			return true;
		}
		return false;
	});
	worldTransform_.UpdateMatrix();
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}
}

void Enemy::Approach() {
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	if (fireTimer <= 1) {
		Fire();
	}
	if (worldTransform_.translation_.z < -15.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view, texturehandle_);
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(view);
	}
}

void Enemy::Fire() {
	Vector3 velocity = {0.0f, 0.0f, -1.0f};
	velocity = TransformNormal(velocity, worldTransform_.matWorld_);
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	bullets_.push_back(newBullet);
}

void Enemy::Leave() {
	worldTransform_.translation_ = Add(worldTransform_.translation_, {-0.1f, 0.5f, 0.0f});
}

void (Enemy::*Enemy::EfuncTable[])() = {
    &Enemy::Approach, &Enemy::Leave
};