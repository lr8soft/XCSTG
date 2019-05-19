#pragma once
#ifndef _GroupInfo_
#define _GroupInfo_
#include <iostream>
#include <mutex>
#include <vector>
#include <gl/glcorearb.h>
#include "XCEnemyBase.h"
namespace xc_game {
	class XCEnemyInfo {
	private:
		std::vector<xc_game::XCEnemyBase*> EnemyVector;
		std::vector<xc_game::XCEnemyBase*> RetVec;
		std::mutex vec_mutex;
	public:
		XCEnemyInfo()=default;
		~XCEnemyInfo();
		void AddEnemyToVector(xc_game::XCEnemyBase* ptr);
		void RemoveEnemyFromVector(xc_game::XCEnemyBase* ptr);
		std::vector<xc_game::XCEnemyBase*>* GetRenderingEnemy();
	};
}

#endif