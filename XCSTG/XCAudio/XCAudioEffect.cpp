#include "XCAudioEffect.h"
ALfloat SourcePosDefault[] = { 0.0, 0.0, -6.0 };
ALfloat SourcePosFar[] = { 0.0, 0.0, -12.0 };
ALfloat SourcePosNear[] = { 0.0, 0.0, 0.0 };
void XCAudioEffect::MusicResourceInit(int effectType)
{
	if (!have_source_init) {
		XCAudio::MusicResourceInit(effectType);
		alGenSources(1, &msource);
		switch (effect_type) {
		case ENEMY_DEAD_EFFECT:
			mbuffer = alutCreateBufferFromFile("Audio/se/se_explode.wav");	
			alSourcefv(msource, AL_POSITION, SourcePosDefault);break;
		case PLAYER_DEAD_EFFECT:
			mbuffer = alutCreateBufferFromFile("Audio/se/se_playerdead.wav");
			alSourcefv(msource, AL_POSITION, SourcePosDefault); break;
		case BOSS_DEAD_EFFECT:
			mbuffer = alutCreateBufferFromFile("Audio/se/se_bossdead.wav");
			alSourcefv(msource, AL_POSITION, SourcePosDefault); break;
		case ATTACK_EFFECT:
			mbuffer = alutCreateBufferFromFile("Audio/se/se_attack.wav");
			alSourcefv(msource, AL_POSITION, SourcePosFar); break;
		case GRAZE_EFFECT:
			mbuffer = alutCreateBufferFromFile("Audio/se/se_graze.wav");
			alSourcefv(msource, AL_POSITION, SourcePosFar); break;
		case GET_SPELLCARD_EFFECT:
			mbuffer = alutCreateBufferFromFile("Audio/se/se_cardget.wav"); break;
			alSourcefv(msource, AL_POSITION, SourcePosDefault); break;
		default:
			throw("XCAudio:Effect haven\'t initialized or unknown effect type!");
		}
		alSourcei(msource, AL_BUFFER, mbuffer);//bind buffer to source
		have_source_init = true;
	}
}

void XCAudioEffect::MusicPlay()
{
	if (have_source_init) 
	{
		if (!is_music_playing|| effect_type== PLAYER_DEAD_EFFECT) {//玩家死亡音效可以多次叠加
			alSourcePlay(msource);
			alGetSourcei(msource, AL_SOURCE_STATE, &mstate);
			is_music_playing = true;
		}
		if (mstate == AL_PLAYING) {
			alGetSourcei(msource, AL_SOURCE_STATE, &mstate);
		}
		else {
			is_music_playing = false;
		}
	}
}

void XCAudioEffect::MusicStop()
{
	if (mstate == AL_PLAYING) 
	{
		alSourceStop(msource);
		is_music_playing = false;
	}
}

void XCAudioEffect::MusicRelease()
{
	XCAudio::MusicRelease();
}

