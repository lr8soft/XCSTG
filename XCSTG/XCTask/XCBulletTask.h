#pragma once
#ifndef _XCBULLETTASK_H_
#define _XCBULLETTASK_H_
#include "XCTask.h"
#include "../XCBullet/XCBullet.h"
#include <map>
class XCBulletTask:public XCTask {
protected:
	/*bool task_should_run = false,task_should_delete=false,,have_resource_init=false;
  int taskType= DefaultType;*/
  /*          ���ȶ�(0~MAX)  ptr to XCEnemy�����ȶ�Խ��0��Խ�ȱ���Ⱦ*/
	std::multimap<int, xc_bullet::XCBullet*> pBulletMap;
	int render_priority = 0;//�����ȶ�0��ʼ��Ⱦ
	void AddBulletToMap(int priority, xc_bullet::XCBullet* ptr) {
		pBulletMap.insert(std::make_pair(priority, ptr));
	}
	bool TaskPriorityRender(float nowframe) {
		bool no_same_priority_bullet = true, nothing_to_render = true;
		auto end_iter = pBulletMap.end();
		for (auto iter = pBulletMap.begin(); iter != end_iter; iter++)
		{
			if (iter->second->IsBulletRender()) {//����Ҫ��Ⱦ��
				nothing_to_render = false;//������û��Ҫ��Ⱦ��
				if (iter->first == render_priority) {//��ͬ���ȶ�
					iter->second->BulletRender(nowframe);
					no_same_priority_bullet = false;//�������� �����ȶ� �ĵ�Ļ ������Ⱦ
				}
			}
		}
		if (no_same_priority_bullet) {
			render_priority++;//��Ⱦ��һ���ȶ�
		}
		return nothing_to_render;
	}
public:
	XCBulletTask() {
		taskType = BulletType;
	}
	/*ȱʡ��Ⱦ����*/
	virtual void TaskRender(XCTaskRenderInfo * pInfo) override {
		task_should_delete = TaskPriorityRender(pInfo->nowFrame);//������ɣ��Զ�ɾ��
	}
	virtual void TaskRelease() {
		auto end_iter = pBulletMap.end();
		for (auto iter = pBulletMap.begin(); iter != end_iter; iter++) {
			iter->second->StopBulletWork();
			iter->second->BulletRelease();
		}
	}
	virtual void TaskCollisionCheck(XCTaskCollisionInfo * pInfo) override{
		auto end_iter = pBulletMap.end();
		for (auto iter = pBulletMap.begin(); iter != end_iter; iter++)
		{
			if (iter->second->IsBulletRender()) {
				if (iter->first == render_priority) {//������Ⱦ�ĸ����ȼ���Ļ�����ܽ�����ײ���
					iter->second->BulletCollisionWithPlayer(pInfo->pPlayer);
				}
			}
		}
	}
};
#endif