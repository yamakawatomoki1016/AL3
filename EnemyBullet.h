#pragma once
#include "Model.h"
#include "Player.h"
//#include <WorldTransform.h>
class EnemyBullet {
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& view);

	bool isDead() const { return isDead_; }

	void SetPlayer(Player* player) { 
		player_ = player;
	}

private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t texturehandle_;
	Vector3 velocity_;
	static const int32_t kLifeTime = 110;
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;
	Player* player_;
};