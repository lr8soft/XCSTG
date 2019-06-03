#include "XCReplay.h"
#include <sstream>
bool XCReplaySystem::ReadReplayFromFile(const char * path)
{
	return false;
}

bool XCReplaySystem::SaveReplayToFile(const char * path)
{
	return false;
}

XCReplaySystem::XCReplaySystem()
{
	keyup = GLFW_KEY_UP; keydown = GLFW_KEY_DOWN; keyleft = GLFW_KEY_LEFT; keyright = GLFW_KEY_RIGHT;
	keyshoot = GLFW_KEY_Z; keyslow = GLFW_KEY_LEFT_SHIFT; keysa = GLFW_KEY_X;

	replay_path = glfwGetTime();
}

XCReplaySystem::~XCReplaySystem()
{
}

XCReplaySystem::XCReplaySystem(const char * path)
{
	XCReplaySystem();
	replay_path = path;
}

void XCReplaySystem::SetRecordKey(int up, int down, int left, int right, int shoot, int slow, int sa)
{
	keyup = up; keydown = down; keyleft = left; keyright = right;
	keyshoot = shoot; keyslow = slow; keysa = sa;
}

void XCReplaySystem::ReplaySystemInit()
{
	replay_stream = new std::fstream(replay_path,std::ios::out);
}

void XCReplaySystem::ReplayRecord(GLFWwindow* screen)
{
	std::stringstream ss;
	if (glfwGetKey(screen, keyslow) == GLFW_PRESS) {
		ss.str("");
		ss << keyslow;
		replay_stream->write(ss.str().c_str(), ss.str().length());
	}
	if (glfwGetKey(screen, keyup) == GLFW_PRESS) {
		ss.str("");
		ss << keyup;
		replay_stream->write(ss.str().c_str(), ss.str().length());
	}

	if (glfwGetKey(screen, keydown) == GLFW_PRESS) {
		ss.str("");
		ss << keydown;
		replay_stream->write(ss.str().c_str(), ss.str().length());
	}
	if (glfwGetKey(screen, keyright) == GLFW_PRESS) {
		ss.str("");
		ss << keyright;
		replay_stream->write(ss.str().c_str(), ss.str().length());
	}

	if (glfwGetKey(screen, keyleft) == GLFW_PRESS) {
		ss.str("");
		ss << keyleft;
		replay_stream->write(ss.str().c_str(), ss.str().length());
	}

	if (glfwGetKey(screen, keyshoot) == GLFW_PRESS) {
		ss.str("");
		ss << keyshoot;
		replay_stream->write(ss.str().c_str(), ss.str().length());
	}
/*	if (glfwGetKey(screen, keyitem) == GLFW_PRESS) {
		player_fire_power += 0.1f;
	}*/
}

void XCReplaySystem::ReplayControl(GLFWwindow* screen)
{
}
