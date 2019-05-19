#include "XCBoss.h"

void xc_game::XCBoss::EnemyInit(size_t type)
{
	ShaderInit();
	BufferInit();
	TextureInit();
	move_type = type;
}

void xc_game::XCBoss::EnemyRender(float nowFrame)
{
}


void xc_game::XCBoss::ReleaseResource()
{
}

void xc_game::XCBoss::ShaderInit()
{
}

void xc_game::XCBoss::BufferInit()
{
}

void xc_game::XCBoss::TextureInit()
{
}
