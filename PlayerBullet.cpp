 #include "PlayerBullet.h"
#include <assert.h>
void PlayerBullet::Initialize(Model* model, const Vector3& position) {
	//NULLポインタチェック
	assert(model);
	model_ = model;
	//テクスチャ読み込み
	texturehandle_ = TextureManager::Load("black.png");
	
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
}

void PlayerBullet::Update() { worldTransform_.UpdateMatrix(); }

//モデルの描画
void PlayerBullet::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view, texturehandle_);
}