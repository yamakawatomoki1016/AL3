#include "Player.h"
#include "MathFunction.h"

Player::~Player() { 
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
	delete sprite2DReticle_;
}

Vector3 Player::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void Player::OnCollision() {}

void Player::SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

void Player::DrawUI() { sprite2DReticle_->Draw(); }

void Player::Attack() {
	XINPUT_STATE joyState;
	if (!Input::GetInstance()->GetJoystickState(0, joyState)) {
		return;
	}
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		if (count == 0) {
			// 弾の速度
			const float kBulletSpeed = 1.0f;
			Vector3 velocity(0, 0, kBulletSpeed);
			// 速度ベクトルの自機の向きに合わせて回転させる
			velocity = Subtract(worldTransform3DReticle_.translation_, GetWorldPosition());
			velocity = Multiply(kBulletSpeed, Normalize(velocity));
			PlayerBullet* newBulllet = new PlayerBullet();
			newBulllet->Initialize(model_, GetWorldPosition(), velocity);
			// 弾を登録する
			bullets_.push_back(newBulllet);
			count++;
		}
	} else {
		count = 0;
	}
	if (input_->PushKey(DIK_SPACE)) {
		if (count == 0) {
			// 弾の速度
			const float kBulletSpeed = 1.0f;
			Vector3 velocity(0, 0, kBulletSpeed);
			// 速度ベクトルの自機の向きに合わせて回転させる
			velocity = Subtract(worldTransform3DReticle_.translation_, GetWorldPosition());
			velocity = Multiply(kBulletSpeed, Normalize(velocity));
			PlayerBullet* newBulllet = new PlayerBullet();
			newBulllet->Initialize(model_, GetWorldPosition(), velocity);
			// 弾を登録する
			bullets_.push_back(newBulllet);
			count++;
		}
	} else {
		count = 0;
	}
}

void Player::Initialize(Model* model, uint32_t textureHandle, Vector3 position) { 
	//NULLポインタチェック
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	input_ = Input::GetInstance();
	worldTransform3DReticle_.Initialize();
	worldTransform_.translation_ = Add(worldTransform_.translation_, position);
	uint32_t textureReticle = TextureManager::Load("reticle.png");
	sprite2DReticle_ = Sprite::Create(textureReticle, {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
}

void Player::Update(const ViewProjection viewProjection) {
	// デスフラグのたった弾を削除
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});
	// 行列更新
	worldTransform_.TransferMatrix();
	//キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	//キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;

	//押した方向で移動ベクトルを変更(左右)
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
		inputFloat3[0] = worldTransform_.translation_.x;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
		inputFloat3[0] = worldTransform_.translation_.x;
	}

	//押した方向で移動ベクトルを変更(上下)
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
		inputFloat3[1] = worldTransform_.translation_.y;
	} else if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
		inputFloat3[1] = worldTransform_.translation_.y;
	}
	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		move.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed;
		move.y += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed;
	}
	//回転速さ[ラジアン/frame]
	const float kRotSpeed = 0.02f;

	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}

	// ベクターの加算
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	// アフィン変換行列の作成
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.UpdateMatrix();
	// ImGuiスライダー
	ImGui::Begin("PlayerDebug");
	ImGui::Text("DebugCamera Toggle : 0");
	ImGui::SliderFloat3("Positions", inputFloat3, -20.0f, 20.0f);
	// ImGui終わり
	ImGui::End();

	// 移動限界座標
	const float kMoveLimitX = 34;
	const float kMoveLimitY = 18;

	// 範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	Attack();

	//弾更新
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}

	const float kDistancePlayerTo3DReticle = 50.0f;
	Vector3 offset = {0.0f, 0.0f, 1.0f};
	offset = TransformNormal(offset, worldTransform_.matWorld_);
	offset = Multiply(kDistancePlayerTo3DReticle, Normalize(offset));
	worldTransform3DReticle_.translation_ = Add(GetWorldPosition(), offset);
	worldTransform3DReticle_.UpdateMatrix();
	Vector3 positionRetcle = {
	    worldTransform3DReticle_.matWorld_.m[3][0], worldTransform3DReticle_.matWorld_.m[3][1],
	    worldTransform3DReticle_.matWorld_.m[3][2]};
	Matrix4x4 matViewport = MakeViewportMatrix(0.0f, 0.0f, WinApp::kWindowWidth, WinApp::kWindowHeight, 0.0f, 1.0f);
	Matrix4x4 matViewProjectionViewport = Multiply(Multiply(viewProjection.matView , viewProjection.matProjection ), matViewport);
	positionRetcle = Transform(positionRetcle, matViewProjectionViewport);

    ////マウスの場合
    //POINT mousePosition;
    ////マウス座標（スクリーン座標）を取得する
    //GetCursorPos(&mousePosition);
    ////    クライアントエリア座標に変換する
    //HWND hwnd = WinApp::GetInstance()->GetHwnd();
    //ScreenToClient(hwnd, &mousePosition);
    //sprite2DReticle_->SetPosition({(float)mousePosition.x, (float)mousePosition.y});

	//コントローラーの場合
	Vector2 spritePosition = sprite2DReticle_->GetPosition();
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		move.x = (float)joyState.Gamepad.sThumbRX / SHRT_MAX * 5.0f;
		move.y = (float)joyState.Gamepad.sThumbRY / SHRT_MAX * 5.0f;
		spritePosition.x += move.x;
		spritePosition.y -= move.y;
		sprite2DReticle_->SetPosition(spritePosition);
	}
	

	Matrix4x4 matVPV = Multiply(Multiply(viewProjection.matView, viewProjection.matProjection), matViewport);
    Matrix4x4 matInverseVPV = Inverse(matVPV);
    Vector3 posNear = {(float)sprite2DReticle_->GetPosition().x, (float)sprite2DReticle_->GetPosition().y, 0};
    Vector3 posFar = {(float)sprite2DReticle_->GetPosition().x, (float)sprite2DReticle_->GetPosition().y, 1};
    posNear = Transform(posNear, matInverseVPV);
    posFar = Transform(posFar, matInverseVPV);
    Vector3 mouseDirection = Subtract(posFar, posNear);
    mouseDirection = Normalize(mouseDirection);
    const float kDistancetestObject = 100.0f;
    worldTransform3DReticle_.translation_ = Add(posNear, Multiply(kDistancetestObject, mouseDirection));
    worldTransform3DReticle_.UpdateMatrix();

	ImGui::Begin("Player");
	ImGui::Text("2DReticle:(%f,%f)", sprite2DReticle_->GetPosition().x, sprite2DReticle_->GetPosition().y);
	ImGui::Text("Near:(%+.2f,%+.2f,%+.2f)", posNear.x, posNear.y, posNear.z);
	ImGui::Text("Far:(%+.2f,%+.2f,%+.2f)", posFar.x, posFar.y, posFar.z);
	ImGui::Text("3DRetixle:(%+.2f,%+.2f,%.2f)", worldTransform3DReticle_.translation_.x,
	    worldTransform3DReticle_.translation_.y, worldTransform3DReticle_.translation_.z);
	ImGui::End();

	
}


void Player::Draw(ViewProjection viewProjection_) { 
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	//弾の描画
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}

}