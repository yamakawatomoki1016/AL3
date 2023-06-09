#pragma once
#include "MathFunction.h"
#include "Model.h"
#include "WorldTransform.h"

/// <summary>
/// 敵
/// </summary>
class Enemy {
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& view);

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
};

