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
	default_random_engine e(glfwGetTime());
	uniform_real_distribution<float> rand_engine(0.0f, rendertime);
	for (int i = 0; i < count;i++) {
		StorageParticleGroup[i].SpecialEffectInit(type);
		StorageParticleGroup[i].SetRenderTime(rand_engine(e));
		
	}
}

bool ParticleGroup::GroupRender(float x, float y, float z)
{
	bool is_render_finish = true;
	int i=0;
	default_random_engine e(glfwGetTime());
	uniform_real_distribution<float> rand_engine(-0.5f, 0.5f);
	for (int i = 0; i < particle_count; i++) {
		if (StorageParticleGroup[i].ShouldRender()) {
			float temp_x = 0, temp_y = 0, temp_z = z;
			switch (groupRenderType) {
			case ALL_ONE_COORD:
				StorageParticleGroup[i].SpecialEffectRender(x, y, z);
				is_render_finish = false; 
				break;
			case ROTATE_COORD:
				temp_x = x + sin(glfwGetTime()+i)/4;
				temp_y = y + cos(glfwGetTime()+i)/4;
				temp_z = z;
				StorageParticleGroup[i].SpecialEffectRender(temp_x, temp_y, temp_z);
				is_render_finish = false; 
				break;
			case DISPERSE_COORD:
				temp_x = x + rand_engine(e)*2;
				temp_y = y + rand_engine(e)*2;
				temp_z = z + abs(rand_engine(e)*10)-4;
				StorageParticleGroup[i].SpecialEffectRender(temp_x, temp_y, temp_z);
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
