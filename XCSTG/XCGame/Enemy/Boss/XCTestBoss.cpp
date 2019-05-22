#include "XCTestBoss.h"
#include "../../../util/ImageLoader.h"
using namespace xc_ogl;
void TestBoss::TextureInit()
{
	MaxLife = 100;
	NowLife = 100;
	ImageLoader BossLoader;
	BossLoader.LoadTextureData("Image/Boss/boss_test.png");
	use_tbo = BossLoader.GetTBO();
}

void TestBoss::EnemyRender(float nowFrame)
{
	xc_game::XCBoss::EnemyRender(nowFrame);
}
