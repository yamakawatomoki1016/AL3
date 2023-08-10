 #include "PlayerBullet.h"
#include <assert.h>
#include "MathFunction.h"

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
	SetCollisionAttribute(CollisionConfig::kCollisionAttributePlayer);
	SetCollisionMask(~CollisionConfig::kCollisionAttributePlayer);
}

void PlayerBullet::Update() { 
	
	worldTransform_.UpdateMatrix(); 
	//座標を移動させる(1フレーム分の移動量を足しこむ)
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

	//時間経過でデス
	if (--deathtimer_ <= 0) {
		isDead_ = true;
	}

}

//モデルの描画
void PlayerBullet::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view, texturehandle_);
}

void PlayerBullet::OnCollision() { isDead_ = true; }

Vector3 PlayerBullet::GetWorldPosition() { 
// ワールド座標を取得
	Vector3 worldPos;
	worldTransform_.UpdateMatrix();
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}
