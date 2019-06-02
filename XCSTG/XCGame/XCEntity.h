#pragma once
#ifndef _XCENTITY_H_
#define _XCENTITY_H_
#include <iostream>
class XCEntity {
protected:
	bool is_dead = false;
	float NowLife=1000, MaxLife=1000,collsion_radius=0.0f;
	float NowX = 0, NowY = 0, NowZ = 0;
	/*!返回敌人是否死亡
!请在检测 should_render=true后调用！*/
	virtual bool EntityCollideWithEntity(XCEntity* entity) {
		if (entity == nullptr) return false;
		if (entity->IsDead()) return false;
		auto enemy_coord = entity->GetNowCoord();
		float x = *enemy_coord, y = *(enemy_coord + 1), z = *(enemy_coord + 2);
		float dist = sqrt(pow(x - NowX, 2) + pow(y - NowY, 2) + pow(z - NowZ, 2));
		if (collsion_radius + entity->GetCollisionRadius() > dist) {
			return true;
		}
		else {
			return false;
		}
	}
public:
	float* GetNowCoord() {
		static float returnArray[3];
		returnArray[0] = NowX;
		returnArray[1] = NowY;
		returnArray[2] = NowZ;
		return returnArray;
	}
	float GetCollisionRadius() {
		return collsion_radius;
	}
	bool IsDead() {
		return is_dead;
	}
	void SetNowLife(float now) {
		NowLife = now;
	}
	void SetMaxLife(float max) {
		MaxLife = max;
	}
	void SetCoord(float x,float y,float z) {
		NowX = x; NowY = y; NowZ = z;
	}
	virtual void SetDead(bool dead) {
		is_dead = dead;
	}
	virtual void SetDamage(bool damage) {
		NowLife -= damage;
		if (NowLife<=0) {
			SetDead(true);
			NowLife = 0;
		}
	}

};
#endif