#pragma once
#include "Vector3.h"
class Collider {
private:

	float radius_ = 1.0f;
	uint32_t collisionAttribute_ = 0xffffffff;
	uint32_t CollisionMask_ = 0xffffffff;

public:
	float GetRadius() { return radius_; }
	void SetRadius(float radius) { radius_ = radius; }
	virtual void OnCollision() = 0;
	virtual Vector3 GetWorldPosition() = 0;
	uint32_t GetCOllisionAttribute() { return collisionAttribute_; }
	void SetCollisionAttribute(uint32_t attribute) { collisionAttribute_ = attribute; }
	uint32_t GetCollosionMask() { return CollisionMask_; }
	void SetCollisionMask(uint32_t mask) { CollisionMask_ = mask; }
};
