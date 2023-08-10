#include "CollisionManager.h"

void CollisionManager::CheckAllCollisions() {
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
	std::list<Collider*>::iterator itrA = colliders_.begin();
	for (; itrA != colliders_.end(); ++itrA) {

		std::list<Collider*>::iterator itrB = itrA;
		++itrB;
		for (; itrB != colliders_.end(); ++itrB) {
			CheckCollisionPair(*(itrA), *(itrB));
		}
	}
}

void CollisionManager::CheckCollisionPair(Collider* colliderA, Collider* colliderB) {
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
	if ((radA + radB) * (radA + radB) >= distance.x + distance.y + distance.z) {
		colliderA->OnCollision();
		colliderB->OnCollision();
	}
}
