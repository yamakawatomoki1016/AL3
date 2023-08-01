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
	delete modelSkydome_;
}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("./Resources/sample.png");
	model_ = Model::Create();
	worldTransform_.Initialize();
	viewProjection_.Initialize();
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	//自キャラの生成
	player_ = new Player();
	//自キャラの初期化
	Vector3 playerPosition(0.0f, 0.0f, 50.0f);
	player_->Initialize(model_,textureHandle_,playerPosition);

	//敵の生成
	enemy_ = new Enemy;
	Vector3 position = {6, 0, 30};
	//敵の初期化
	enemy_->SetPlayer(player_);
	enemy_->Initialize(model_, position, {0,0,-0.5});

	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_);
	railCamera_ = new RailCamera();
	railCamera_->Initialize({0.0f, 0.0f, 0.0f}, {0.0f,0.0f,0.0f});
	player_->SetParent(&railCamera_->GetWorldTransform());
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
		railCamera_->Update();
		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	}
#endif
	skydome_->Update();
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
	skydome_->Draw(viewProjection_);
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
	Vector3 posA, posB;
	float playerRadius = 1.0f;
	float enemyRadius = 1.0f;
	float playerBulletRadius = 0.5f;
	float enemyBulletRadius = 0.5f;
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();
	
#pragma region 自キャラと敵弾の当たり判定
	posA = player_->GetWorldPosition();
	for (EnemyBullet* bullet : enemyBullets) {
		posB = bullet->GetWorldPosition();
		Vector3 distance = {
		    (posB.x - posA.x) * (posB.x - posA.x), (posB.y - posA.y) * (posB.y - posA.y),
		    (posB.z - posA.z) * (posB.z - posA.z)};
		if ((playerRadius + enemyBulletRadius) * (playerRadius + enemyBulletRadius) >=
		    distance.x + distance.y + distance.z) {
			player_->OnCollision();
			bullet->OnCollision();
		}
	}
	#pragma endregion

	
#pragma region 自弾と敵キャラの当たり判定
	posA = enemy_->GetWorldPosition();
	for (PlayerBullet* bullet : playerBullets) {
		posB = bullet->GetWorldPosition();
		Vector3 distance = {
		    (posB.x - posA.x) * (posB.x - posA.x), (posB.y - posA.y) * (posB.y - posA.y),
		    (posB.z - posA.z) * (posB.z - posA.z)};
		if ((enemyRadius + playerBulletRadius) * (enemyRadius + playerBulletRadius) >=
		    distance.x + distance.y + distance.z) {
			enemy_->OnCollision();
			bullet->OnCollision();
		}
	}
	#pragma endregion

	//自弾と敵弾の当たり判定
	#pragma region
	for (EnemyBullet* enemyBullet : enemyBullets) {
		posA = enemyBullet->GetWorldPosition();
		for (PlayerBullet* playerBullet : playerBullets) {
			posB = playerBullet->GetWorldPosition();
			Vector3 distance = {
			    (posB.x - posA.x) * (posB.x - posA.x), (posB.y - posA.y) * (posB.y - posA.y),
			    (posB.z - posA.z) * (posB.z - posA.z)};
			if ((enemyBulletRadius + playerBulletRadius) * (enemyBulletRadius + playerBulletRadius) >=
			    distance.x + distance.y + distance.z) {
 				playerBullet->OnCollision();
				enemyBullet->OnCollision();
			}
		}
	}
	#pragma endregion
}
