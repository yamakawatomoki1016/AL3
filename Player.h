#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <cassert>
#include "Input.h"
#include "ImGuiManager.h"
#include "PlayerBullet.h"
#include <list>

///<summary>
///自キャラ
///</summary>
class Player {

	public:
		///<summary>
		///初期化
		///</summary>
		///<param name="model">モデル</param>
		///<param name="textureHandle">テクスチャハンドル</param>
	    void Initialize(Model* model, uint32_t textureHandle);

		///<summary>
		///更新
		///</summary>
	    void Update();

		///<summary>
		///描画
		///</summary>
	    void Draw(ViewProjection viewProjection_);

	    /// <summary>
	    /// 攻撃
	    /// </summary>
	    void Attack();

	    /// <summary>
	    /// デストラクタ
	    /// </summary>
	    ~Player();


	private:
		//ワールド変換データ
	    WorldTransform worldTransform_;
		//モデル
	    Model* model_ = nullptr;
		//テクスチャハンドル
	    uint32_t textureHandle_ = 0u;
		//キーボード入力
	    Input* input_ = nullptr;
	    // ImGUiで値を入力する変数
	    float inputFloat3[3] = {0, 0, 0};
		//弾
	    PlayerBullet* bullet_ = nullptr;
		//弾
	    std::list<PlayerBullet*> bullets_;
	    int count = 0;
};