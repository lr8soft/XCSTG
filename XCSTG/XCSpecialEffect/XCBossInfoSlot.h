#pragma once
#ifndef _XCBOSSINFO_SLOT_H_
#define _XCBOSSINFO_SLOT_H_
#include <iostream>
#include <GL/glcorearb.h>
#include "../util/GameTimer.h"
namespace xc_se {
	class XCGameInfoSlot {
	private:
		enum InfoType {HP_SLOT,SPELLCARD_SLOT};
		static bool have_resource_init, have_program_init;
		static GLuint vao[5], vbo[5], tbo[2], program[2];
		XCGameTimer spellCardSlotTimer;
		std::string BossName;
		float *BossHP, *BossMaxHP;
		size_t RemainingTime,SpellCardCount;
		void ShaderInit();
		void TextureInit();
		void BufferInit();
	public:
		XCGameInfoSlot() = default;
		~XCGameInfoSlot() = default;
		void SetInfo(float *hp, float *mhp, int rtime, int sccount);
		void SpecialEffectInit();
		bool BossHPRender();
		enum SpellCardState {GET_SPELL_CARD,BONUS_FAILED,NEXT_STAGE};
		bool SpellCardInfoRender(int type);
		void SpecialEffectRelease();
	};
}
#endif