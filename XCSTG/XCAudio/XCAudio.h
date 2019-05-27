#pragma once
#ifndef _XCAUDIO_H_
#define _XCAUDIO_H_
#include<AL/alut.h>
#include<AL/al.h>
class XCAudio {
protected:
	int effect_type= ENEMY_DEAD_EFFECT;//default
	bool have_source_init = false, is_music_playing = false;
	ALuint msource, mbuffer;
	ALint mstate;
public:
	enum EffectType 
	{ 
		ENEMY_DEAD_EFFECT=1, BOSS_DEAD_EFFECT, PLAYER_DEAD_EFFECT, ATTACK_EFFECT, GRAZE_EFFECT,
		EXTEND_EFFECT, EXTEND_BOMB_EFFECT, SPECIAL_ATTACK_EFFECT, GET_SPELLCARD_EFFECT, FAIL_SPELLCARD_EFFECT
	};
	XCAudio() 
	{
		alutInit(0, 0);
	}
	~XCAudio() 
	{
		MusicRelease();
	}
	virtual void MusicResourceInit(int effectType) {
		effect_type = effectType;
	}
	virtual void MusicPlay() = 0;
	virtual void MusicStop() = 0;
	virtual void MusicRelease() {
		if (have_source_init) {
			alDeleteBuffers(1, &mbuffer);
			alDeleteSources(1, &msource);
			have_source_init = false;
			is_music_playing = false;
			effect_type = 0;
		}
	}
};
#endif