#include "XCBoss.h"
#include "../../util/ShaderReader.h"
#include "../../util/ImageLoader.h"
using namespace xc_ogl;
bool xc_game::XCBoss::have_program_init = false;
void xc_game::XCBoss::ShaderInit()
{
	if (!have_program_init) {
		ShaderReader BossShaderLoader;
		BossShaderLoader.load_from_file("shader/enemy/normal.vert", GL_VERTEX_SHADER);
		BossShaderLoader.load_from_file("shader/enemy/normal.frag", GL_FRAGMENT_SHADER);
		BossShaderLoader.link_all_shader();
		program_static = BossShaderLoader.get_program();
		have_program_init = true;
	}
	program = program_static;
}

void xc_game::XCBoss::BufferInit()
{

}

void xc_game::XCBoss::TextureInit()
{
}
void xc_game::XCBoss::EnemyInit(size_t type)
{
	XCEnemyBase::EnemyInit(type);
}

void xc_game::XCBoss::EnemyRender(float nowFrame)
{
}

void xc_game::XCBoss::ReleaseResource()
{
}
