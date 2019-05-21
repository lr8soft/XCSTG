#pragma once
#ifndef _XCBOSSINFO_SLOT_H_
#define _XCBOSSINFO_SLOT_H_
#include <iostream>
#include <GL/glcorearb.h>
namespace xc_se {
	class XCBossInfoSlot {
	private:
		std::string BossName;
		float *BossHP, *BossMaxHP;
		size_t RemainingTime,SpellCardCount;
		GLuint vao, vbo, tbo,program;
		void ShaderInit();
		void TextureInit();
		void BufferInit();
	public:
		XCBossInfoSlot() = default;
		~XCBossInfoSlot() = default;
		void SetInfo(float *hp, float *mhp, int rtime, int sccount);
		void SpecialEffectInit();
		bool SpecialEffectRender();
		void SpecialEffectRelease();
	};
}
#endif