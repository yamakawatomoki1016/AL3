 #include "PlayerBullet.h"
#include <assert.h>
void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	//NULLポインタチェック
	assert(model);
	model_ = model;
	//テクスチャ読み込み
	texturehandle_ = TextureManager::Load("black.png");
	
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	//引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
}

void PlayerBullet::Update() { 
	worldTransform_.UpdateMatrix(); 
	//座標を移動させる(1フレーム分の移動量を足しこむ)
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
}

//モデルの描画
void PlayerBullet::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view, texturehandle_);
}

Vector3 PlayerBullet::Add(Vector3& a, Vector3& b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }