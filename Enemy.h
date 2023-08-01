#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "EnemyBullet.h"

class Player;
/// <summary>
/// 敵
/// </summary>
class Enemy {
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	~Enemy();

	void Update();

	void Draw(const ViewProjection& view);

	void Fire();

	void SetPlayer(Player* player) { player_ = player; }

	Vector3 GetworldPosition();

	static const int kFireInterval = 60;
	int32_t fireTimer;

private:
	// 行動フェーズ
	enum class Phase {
		Approach, // 接近する
		Leave,    // 離脱する
		start,    // 初期
	};
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t texturehandle_;
	//フェーズ
	Phase phase_ = Phase::Approach;
	Vector3 velocity_;
	void Approach();
	void Leave();
	static void (Enemy::*EfuncTable[])();
	std::list<EnemyBullet*> bullets_;
	Player* player_ = nullptr;
};

