#pragma once
#ifndef _PARTICLEGROUP_H_
#define _PARTICLEGROUP_H_
#include "../XCSpecialEffect/XCParticle.h"
#include <vector>
class ParticleGroup {
protected:
	xc_se::XCParticle *StorageParticleGroup=nullptr;
	int groupRenderType= DISPERSE_COORD,particle_count=0;
public:
	enum GroupType {ALL_ONE_COORD, DISPERSE_COORD};
	enum ParticleType { CIRCLE_PARTICLE, MOVING_PARTICLE};
	void SetGroupRenderType(int groupType);
	virtual void GroupInit(int type,int count,float rendertime);
	/*Return whether particle render finish.*/
	virtual bool GroupRender(float x,float y,float z);
	virtual void GroupRelease();
};
#endif