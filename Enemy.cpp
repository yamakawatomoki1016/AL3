#include "Enemy.h"
#include <assert.h>
#include "MathFunction.h"
# include "Player.h"
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
	SetCollisionAttribute(CollisionConfig::kCollisionAttributeEnemy);
	SetCollisionMask(~CollisionConfig::kCollisionAttributeEnemy);
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
	fireTimer--;
	if (fireTimer <= 0) {
		Fire();
		fireTimer = 30;
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
	assert(player_);
	//弾の速度
	const float kBulletSpeed = 1.0f;

	Vector3 PlayerPos = player_->GetWorldPosition();
	Vector3 enemyPos = this->GetWorldPosition();
	Vector3 velocity = Subtract(PlayerPos, enemyPos);
	velocity = Normalize(velocity);
	velocity.x *= kBulletSpeed;
	velocity.y *= kBulletSpeed;
	velocity.z *= kBulletSpeed;

	//弾を生成し、初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	//弾を登録する
	bullets_.push_back(newBullet);
}

Vector3 Enemy::GetWorldPosition() { 
	//ワールド座標を取得
	Vector3 worldPos;
	worldTransform_.UpdateMatrix();
	//ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
	
}

void Enemy::OnCollision() {}

void Enemy::Leave() {
	worldTransform_.translation_ = Add(worldTransform_.translation_, {-0.0f, 0.0f, 0.5f});
	if (worldTransform_.translation_.z > 15.0f) {
		phase_ = Phase::Approach;
	}
}

void (Enemy::*Enemy::EfuncTable[])() = {
    &Enemy::Approach, &Enemy::Leave
};