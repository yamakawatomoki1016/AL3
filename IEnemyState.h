#pragma once

class Enemy;

class IEnemyState {
public:
	virtual void Update(Enemy* enemy) = 0;

};