#pragma once
#include <WorldTransform.h>
#include <ViewProjection.h>
#include "MathFunction.h"
#include <ImGuiManager.h>
class RailCamera {
public:

	void Initialize(const Vector3& pos, const Vector3& rotate);

	void Update();

	const ViewProjection& GetViewProjection() { return viewProjection_; }

	const WorldTransform& GetWorldTransform() { return worldTransform_; }

private:

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;


};
