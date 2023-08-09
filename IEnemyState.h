#pragma once
class Enemy;
class EnemyStateManager;
class IEnemyState {

public:
	virtual void Update() = 0;
	virtual void Initialize(Enemy* enemy) = 0;

protected:
	Enemy* enemy_ ;
	EnemyStateManager* manager_;





};
