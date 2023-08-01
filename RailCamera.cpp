#include "RailCamera.h"

void RailCamera::Initialize(const Vector3& pos,const Vector3& rotate ) { 
	worldTransform_.Initialize();
	worldTransform_.rotation_ = rotate;
	worldTransform_.translation_ = pos;
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	viewProjection_.Initialize();
}

void RailCamera::Update() { 
	worldTransform_.translation_.z -= 0.0001f;
	worldTransform_.rotation_.y += 0.00001f;
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);
	ImGui::Begin("Camera");
	ImGui::DragFloat3("Translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("Rotation", &worldTransform_.rotation_.x, 0.1f);
	ImGui::End();
}
