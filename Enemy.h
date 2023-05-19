#pragma once
#include "MathFunction.h"
#include "Model.h"

/// <summary>
/// 敵
/// </summary>
class Enemy {
public:

	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& view);

private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t texturehandle_;
};

