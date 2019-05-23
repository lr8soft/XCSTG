#include "XCEnemyInfo.h"

xc_game::XCEnemyInfo::~XCEnemyInfo()
{

}

void xc_game::XCEnemyInfo::AddEnemyToVector(xc_game::XCEnemyBase * ptr)
{
	EnemyVector.push_back(ptr);
}

void xc_game::XCEnemyInfo::RemoveEnemyFromVector(xc_game::XCEnemyBase * ptr)
{
	vec_mutex.lock();
	auto iter_end = EnemyVector.end(),iter_begin= EnemyVector.begin();
	auto ptr_iter = find(iter_begin, iter_end,ptr);
	if (ptr_iter == iter_end)//没有您这位小朋友
	{
		vec_mutex.unlock();
		return;
	}
	else 
	{
		EnemyVector.erase(ptr_iter);
	}
	vec_mutex.unlock();
}

std::vector<xc_game::XCEnemyBase*>* xc_game::XCEnemyInfo::GetRenderingEnemy()
{
	RetVec.clear();
	vec_mutex.lock();
	auto iter_end = EnemyVector.end();
	for (auto ptr = EnemyVector.begin(); ptr != iter_end;ptr++) {
		auto *EnemyObj = (*(ptr));
		if (EnemyObj->IsRenderNow()) {
			RetVec.push_back(EnemyObj);
		}
	}
	vec_mutex.unlock();
	return &RetVec;
}
