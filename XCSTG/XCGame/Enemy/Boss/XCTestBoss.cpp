#include "XCTestBoss.h"
#include "../../../util/ImageLoader.h"
using namespace xc_ogl;
void TestBoss::TextureInit()
{
	ImageLoader BossLoader;
	BossLoader.loadTextureFromFile("Image/Boss/boss_test.png");
	use_tbo = BossLoader.getTextureBufferObjectHandle();
}

void TestBoss::EnemyRender(float nowFrame)
{
	xc_game::XCBoss::EnemyRender(nowFrame);
}
