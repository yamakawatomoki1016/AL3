#pragma once
#include "Model.h"
#include "WorldTransform.h"

///<summary>
///自キャラの弾
///</summary>
class PlayerBullet {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">初期座標</param>
	void Initialize(Model* model, const Vector3& position,const Vector3& velocity);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="ViewProjection">ビュープロジェクション</param>
	void Draw(const ViewProjection& ViewProjection);
	bool IsDead() const { return isDead_; }
	private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t texturehandle_;
	//速度
	Vector3 velocity_;
	//Vector3 Add(Vector3& a, Vector3& b);
	//寿命<frm>
	static const int32_t kLifeTime = 60 ;
	//デスタイマー
	int32_t deathtimer_ = kLifeTime;
	//デスフラグ
	bool isDead_ = false;
	
};