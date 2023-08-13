#pragma once
#include "MathFunction.h"
#include "Model.h"
#include "WorldTransform.h"
#include "EnemyStateApproach.h"
#include "IEnemyState.h"

/// <summary>
/// 敵
/// </summary>
class Enemy {
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& view);

	void Move(Vector3 velocity);

	Vector3 EnemyGetPos() { return worldTransform_.translation_; }

	void StateChange(IEnemyState* newState);

private:
	// 行動フェーズ

	WorldTransform worldTransform_;
	Model* model_;
	uint32_t texturehandle_;
	// フェーズ

	Vector3 velocity_;

	IEnemyState* state_;
};
