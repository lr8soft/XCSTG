#pragma once
#ifndef _XCBOSSINFO_SLOT_H_
#define _XCBOSSINFO_SLOT_H_
#include <iostream>
#include <GL/glcorearb.h>
#include "../util/GameTimer.h"
namespace xc_se {
	class XCGameInfoSlot {
	private:
		float render_abs_width = 1.0f, render_abs_height = 1.0f;
		enum InfoType {HP_SLOT,SPELLCARD_SLOT,RENDER_PLANE};
		static bool have_resource_init, have_program_init,have_buffer_init;
		static GLuint vao[3], vbo[3], tbo[3], program[3];
		XCGameTimer spellCardSlotTimer;
		std::string BossName;
		float *BossHP, *BossMaxHP;
		size_t RemainingTime,SpellCardCount;
		void ShaderInit();
		void TextureInit();
		void BufferInit();
		void SpecialEffectInit();
	public:
		XCGameInfoSlot() = default;
		~XCGameInfoSlot() = default;
		void SetInfo(float *hp, float *mhp, int rtime, int sccount);
		void SetAbsWidthAndHeight(float absW, float absH);
		void BossHPInit();
		bool BossHPRender();
		void SpellCardInfoInit();
		enum SpellCardState { NEXT_STAGE, BONUS_FAILED,GET_SPELL_CARD};
		bool SpellCardInfoRender(int type);
		void CoveredPlaneInit();
		void CoveredPlaneRender(float absW,float absH);
		void SpecialEffectRelease();
	};
}
#endif