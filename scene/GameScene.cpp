#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete model_;
	delete player_;
	delete debugCamera_;
	delete enemy_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("./Resources/sample.png");
	model_ = Model::Create();
	worldTransform_.Initialize();
	viewProjection_.Initialize();
	//自キャラの生成
	player_ = new Player();
	//自キャラの初期化
	player_->Initialize(model_,textureHandle_);

	//敵の生成
	enemy_ = new Enemy;
	Vector3 position = {6, 0, 30};
	//敵の初期化
	enemy_->SetPlayer(player_);
	enemy_->Initialize(model_, position, {0,0,-0.5});

	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	// 軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::Update() { 
	 player_->Update();
	enemy_->Update();
	 CheckAllCollisions();
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_0) && isDebugCameraActive_ == false) {
		isDebugCameraActive_ = true;
	} else if (input_->TriggerKey(DIK_0) && isDebugCameraActive_ == true) {
		isDebugCameraActive_ = false;
	}
	// カメラの処理
	if (isDebugCameraActive_ == true) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		// ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}
#endif
	debugCamera_->Update();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	//自キャラの描画
	player_->Draw(viewProjection_);
	enemy_->Draw(viewProjection_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions() { 
	/*const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();
	
#pragma region 自キャラと敵弾の当たり判定
	for (EnemyBullet* bullet : enemyBullets) {
		CheckCollisionPair(bullet, player_);
	}
	#pragma endregion

#pragma region 自弾と敵キャラの当たり判定
	for (PlayerBullet* bullet : playerBullets) {
		CheckCollisionPair(bullet, enemy_);
	}
	#pragma endregion

#pragma region 自弾と敵弾の当たり判定
	for (EnemyBullet* enemyBullet : enemyBullets) {
		for (PlayerBullet* playerBullet : playerBullets) {
			CheckCollisionPair(enemyBullet, playerBullet);
		}
	}
	#pragma endregion*/

	std::list<Collider*> colliders_;

	colliders_.push_back(player_);
	colliders_.push_back(enemy_);

	for (PlayerBullet* bullet : player_->GetBullets()) {
		colliders_.push_back(bullet);
	}
	for (EnemyBullet* enemyBullet : enemy_->GetBullets()) {
		colliders_.push_back(enemyBullet);
	}
	std::list<Collider*>::iterator itrA = colliders_.begin();
	for (; itrA != colliders_.end(); ++itrA) {

		std::list<Collider*>::iterator itrB = itrA;
		++itrB;
		for (; itrB != colliders_.end(); ++itrB) {
			CheckCollisionPair(*(itrA), *(itrB));
		}
	}
}

void GameScene::CheckCollisionPair(Collider* colliderA, Collider* colliderB) {
	if (!(colliderA->GetCOllisionAttribute() & colliderB->GetCollosionMask()) ||
	    !(colliderB->GetCOllisionAttribute() & colliderA->GetCollosionMask())) {
		return;
	}
		Vector3 posA = colliderA->GetWorldPosition();
		Vector3 posB = colliderB->GetWorldPosition();
	    float radA = colliderA->GetRadius();
	    float radB = colliderB->GetRadius();
		Vector3 distance = {
			    (posB.x - posA.x) * (posB.x - posA.x), (posB.y - posA.y) * (posB.y - posA.y),
			    (posB.z - posA.z) * (posB.z - posA.z)};
			if ((radA + radB) * (radA + radB) >=
			    distance.x + distance.y + distance.z) {
 				colliderA->OnCollision();
				colliderB->OnCollision();
			}
		}
