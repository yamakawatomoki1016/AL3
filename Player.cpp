#include <Player.h>
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle) { 
	//NULLポインタチェック
	assert(model);
}

void Player::Update() {
	//行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection) { 
	model_->Draw(worldTransform_, ViewProjection, textureHandle_);
}