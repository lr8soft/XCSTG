#pragma once
#ifndef _GroupInfo_
#define _GroupInfo_
#include <iostream>
#include <mutex>
#include <vector>
#include <gl/glcorearb.h>
#include "XCNormalEnemy.h"
namespace xc_game {
	class XCEnemyInfo {
	private:
		std::vector<xc_game::XCEnemy*> EnemyVector;
		std::vector<xc_game::XCEnemy*> RetVec;
		std::mutex vec_mutex;
	public:
		XCEnemyInfo()=default;
		~XCEnemyInfo();
		void AddEnemyToVector(xc_game::XCEnemy* ptr);
		void RemoveEnemyFromVector(xc_game::XCEnemy* ptr);
		std::vector<xc_game::XCEnemy*>* GetRenderingEnemy();
	};
}

#endif