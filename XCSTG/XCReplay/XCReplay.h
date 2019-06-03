#pragma once
#ifndef _XCREPLAY_H_
#define _XCREPLAY_H_
#include <iostream>
#include <fstream>
#include <glfw/glfw3.h>
class XCReplaySystem {
private:
	std::string replay_path;
	std::fstream *replay_stream;
	int hard_rank = 0;//easy 0 normal 1 hard 2 lunatic 3
	int replay_stage = 0;//all:-1
	int keyup, keydown, keyleft, keyright, keyshoot, keyslow, keysa;
	bool ReadReplayFromFile(const char* path);
	bool SaveReplayToFile(const char* path);
public:
	XCReplaySystem();
	~XCReplaySystem();
	XCReplaySystem(const char* path);
	void SetRecordKey(int up,int down,int left,int right,int shoot,int slow,int sa);
	void ReplaySystemInit();
	void ReplayRecord(GLFWwindow* screen);
	void ReplayControl(GLFWwindow* screen);
};
#endif