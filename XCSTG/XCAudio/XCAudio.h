#pragma once
#ifndef _XCAUDIO_H_
#define _XCAUDIO_H_
#include<AL/alut.h>
#include<AL/al.h>
class XCAudio {
protected:
	bool have_source_init = false, is_music_playing = false;
	ALuint msource, mbuffer;
	ALint mstate;
public:
	XCAudio() {
		alutInit(0, 0);
	}
	virtual void MusicResourceInit() = 0;
	virtual void MusicPlay() = 0;
	virtual void MusicStop() = 0;
	virtual void MusicRelease() {
		if (have_source_init) {
			alDeleteBuffers(1, &mbuffer);
			alDeleteSources(1, &msource);
			have_source_init = false;
		}
	}
	virtual void MusicThreadWork() = 0;
};
#endif