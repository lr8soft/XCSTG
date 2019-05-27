#include "XCExplodeEffect.h"
void XCExplodeEffect::MusicResourceInit()
{
	if (!have_source_init) {
		alGenSources(1, &msource);
		mbuffer = alutCreateBufferFromFile("Audio/se/se_explode.wav");
		alSourcei(msource, AL_BUFFER, mbuffer);//bind buffer to source
		have_source_init = true;
	}

}

void XCExplodeEffect::MusicPlay()
{
	if (have_source_init) 
	{
		if (!is_music_playing) {
			alSourcePlay(msource);
			alGetSourcei(msource, AL_SOURCE_STATE, &mstate);
		}
		if (mstate == AL_PLAYING)
			alGetSourcei(msource, AL_SOURCE_STATE, &mstate);
		else {
			is_music_playing = false;
		}
	}
}

void XCExplodeEffect::MusicStop()
{
	if (mstate == AL_PLAYING)
		alSourceStop(msource);
}

void XCExplodeEffect::MusicRelease()
{
	XCAudio::MusicRelease();
}

void XCExplodeEffect::MusicThreadWork()
{
	;
}
