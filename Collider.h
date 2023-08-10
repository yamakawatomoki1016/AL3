#pragma once
#include "Vector3.h"
class Collider {
private:

	float radius_ = 1.0f;

public:
	float GetRadius() { return radius_; }
	void SetRadius(float radius) { radius_ = radius; }
	virtual void OnCollision() = 0;
	virtual Vector3 GetWorldPosition() = 0;

};
