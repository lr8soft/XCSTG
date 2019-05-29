#include "ParticleGroup.h"
#include <glfw/glfw3.h>
#define DISPERSE_COORD_DEFINE_FUNC(coord,src_coord) if (rand() % 2 == 0) coord = src_coord + (rand()%10)*0.1; else coord = src_coord - (rand()%10)*0.1;
using namespace xc_se;
void ParticleGroup::SetGroupRenderType(int groupType)
{
	groupRenderType = groupType;
}
void ParticleGroup::GroupInit(int type, int count, float rendertime)
{
	for (int i = 0; i < count;i++) {
		XCParticle particleTemp;
		particleTemp.SpecialEffectInit(type);
		particleTemp.SetRenderTime(rendertime);
		StorageParticleGroup.push_back(particleTemp);
	}
}

bool ParticleGroup::GroupRender(float x, float y, float z)
{
	auto iter_end = StorageParticleGroup.end();
	bool is_render_finish = true;
	for (auto iter = StorageParticleGroup.begin(); iter != iter_end; iter++) {
		srand(glfwGetTime());
		if ((*iter).ShouldRender()) {
			switch (groupRenderType) {
			case ALL_ONE_COORD:
				iter->SpecialEffectRender(x, y, z);
				is_render_finish = false; break;
			case DISPERSE_COORD:
				float temp_x=0, temp_y=0, temp_z=0;
				DISPERSE_COORD_DEFINE_FUNC(temp_x,x)
				DISPERSE_COORD_DEFINE_FUNC(temp_y,y)
				DISPERSE_COORD_DEFINE_FUNC(temp_z,z)
				iter->SpecialEffectRender(temp_x, temp_y, temp_z);
				is_render_finish = false; 
				break;
			}

		}
	}
	return is_render_finish;
}

void ParticleGroup::GroupRelease()
{
	auto iter_end = StorageParticleGroup.end();
	for (auto iter = StorageParticleGroup.begin(); iter != iter_end; iter++) {
		iter->SpecialEffectRelease();
	}
}
