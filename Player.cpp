#include <Player.h>
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle) { 
	//NULL�|�C���^�`�F�b�N
	assert(model);
}

void Player::Update() {
	//�s���萔�o�b�t�@�ɓ]��
	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection) { 
	model_->Draw(worldTransform_, ViewProjection, textureHandle_);
}