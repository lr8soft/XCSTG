#include "XCEnemyInfo.h"

xc_game::XCEnemyInfo::~XCEnemyInfo()
{

}

void xc_game::XCEnemyInfo::AddEnemyToVector(xc_game::XCEnemy * ptr)
{
	EnemyVector.push_back(ptr);
}

std::vector<xc_game::XCEnemy*>* xc_game::XCEnemyInfo::GetRenderingEnemy()
{
	RetVec.clear();
	for (auto ptr = EnemyVector.begin(); ptr != EnemyVector.end();ptr++) {
		auto *EnemyObj = (*(ptr));
		if (EnemyObj->IsRendering()) {
			RetVec.push_back(EnemyObj);
		}
	}
	return &RetVec;
}
