#include "XCTestBoss.h"
#include "../../../util/ImageLoader.h"
#include "../../../XCSpellCard/XCSpellCard.h"
using namespace xc_ogl;
void TestBoss::TextureInit()
{
	this->NowLife = 100;
	this->MaxLife = 100;
	ImageLoader BossLoader;
	BossLoader.LoadTextureData("Image/Boss/boss_test2.png");
	use_tbo = BossLoader.GetTBO();
	static XCSpellCard sc;
	AddSpellCard(1000, &sc);
}

void TestBoss::EnemyRender(float nowFrame)
{
	xc_game::XCBoss::EnemyRender(nowFrame);
}
