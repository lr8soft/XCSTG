#pragma once
#include "../XCTask/XCBossTask.h"
class TestBossTask:public XCBossTask {
protected:

public:
	virtual void TaskInit() override;
	virtual void TaskKeyCheck(GLFWwindow* win) override;
	virtual void TaskRender(XCTaskRenderInfo* pInfo) override;
};