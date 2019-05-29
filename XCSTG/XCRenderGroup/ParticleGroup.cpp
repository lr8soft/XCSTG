#include "ParticleGroup.h"
#include <glfw/glfw3.h>
#include <random>
using namespace xc_se;
using namespace std;
void ParticleGroup::SetGroupRenderType(int groupType)
{
	groupRenderType = groupType;
}
void ParticleGroup::GroupInit(int type, int count, float rendertime)
{
	particle_count = count;
	StorageParticleGroup = new XCParticle[particle_count];
	for (int i = 0; i < count;i++) {
		StorageParticleGroup[i].SpecialEffectInit(type);
		StorageParticleGroup[i].SetRenderTime(rendertime);
		
	}
}

bool ParticleGroup::GroupRender(float x, float y, float z)
{
	bool is_render_finish = true;
	int i=0;
	default_random_engine rand_engine(glfwGetTime());
	for (int i = 0; i < particle_count; i++) {
		if (StorageParticleGroup[i].ShouldRender()) {
			switch (groupRenderType) {
			case ALL_ONE_COORD:
				StorageParticleGroup[i].SpecialEffectRender(x, y, z);
				is_render_finish = false; 
				break;
			case DISPERSE_COORD:
				float temp_x=0, temp_y=0, temp_z=0;
				temp_x = x + sin(glfwGetTime()+i)/3;
				temp_y = y + cos(glfwGetTime()+i)/3;
				temp_z = z;
				StorageParticleGroup[i].SpecialEffectRender(temp_x, temp_y, z);
				is_render_finish = false; 
				break;
			}

		}
	}
	return is_render_finish;
}

void ParticleGroup::GroupRelease()
{
	if(particle_count>0)
		delete[] StorageParticleGroup;
}
