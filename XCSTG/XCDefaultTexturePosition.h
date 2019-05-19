#pragma once
#ifndef _XCDEFAULT_TEXTURE_POSITION_H_
#define _XCDEFAULT_TEXTURE_POSITION_H_
/*贴图格式 宽8个x高3个*/
/*第一层为站着，第二层向左，第三层向右*/
static float player_standby_0_8x3[] = {
	0.125f,1.000f,0.125f,0.667f,0.000f,0.667f,
	0.000f,0.667f,0.000f,1.000f,0.125f,1.000f
};
static float player_standby_1_8x3[] = {
	0.250f,1.000f,0.250f,0.667f,0.125f,0.667f,
	0.125f,0.667f,0.125f,1.000f,0.250f,1.000f
};
static float player_standby_2_8x3[] = {
	0.375f,1.000f,0.375f,0.667f,0.250f,0.667f,
	0.250f,0.667f,0.250f,1.000f,0.375f,1.000f
};
static float player_standby_3_8x3[] = {
	0.500f,1.000f,0.500f,0.667f,0.375f,0.667f,
	0.375f,0.667f,0.375f,1.000f,0.500f,1.000f
};
static float player_standby_4_8x3[] = {
	0.625f,1.000f,0.625f,0.667f,0.500f,0.667f,
	0.500f,0.667f,0.500f,1.000f,0.625f,1.000f
};
static float player_standby_5_8x3[] = {
	0.750f,1.000f,0.750f,0.667f,0.625f,0.667f,
	0.625f,0.667f,0.625f,1.000f,0.750f,1.000f
};
static float player_standby_6_8x3[] = {
	0.875f,1.000f,0.875f,0.667f,0.750f,0.667f,
	0.750f,0.667f,0.750f,1.000f,0.875f,1.000f
};
static float player_standby_7_8x3[] = {
	1.000f,1.000f,1.000f,0.667f,0.875f,0.667f,
	0.875f,0.667f,0.875f,1.000f,1.000f,1.000f
};


static float player_turnleft_0_8x3[] = {
	1.000f,0.667f,1.000f,0.333f,0.875f,0.333f,
	0.875f,0.333f,0.875f,0.667f,1.000f,0.667f
};//
static float player_turnleft_1_8x3[] = {
	0.250f,0.667f,0.250f,0.333f,0.125f,0.333f,
	0.125f,0.333f,0.125f,0.667f,0.250f,0.667f
};//
static float player_turnleft_2_8x3[] = {
	0.375f,0.667f,0.375f,0.333f,0.250f,0.333f,
	0.250f,0.333f,0.250f,0.667f,0.375f,0.667f
};//
static float player_turnleft_3_8x3[] = {
	0.500f,0.667f,0.500f,0.333f,0.375f,0.333f,
	0.375f,0.333f,0.375f,0.667f,0.500f,0.667f
};//
static float player_turnleft_4_8x3[] = {
	0.625f,0.667f,0.625f,0.333f,0.500f,0.333f,
	0.500f,0.333f,0.500f,0.667f,0.625f,0.667f
};//
static float player_turnleft_5_8x3[] = {
	0.750f,0.667f,0.750f,0.333f,0.625f,0.333f,
	0.625f,0.333f,0.625f,0.667f,0.750f,0.667f
};//
static float player_turnleft_6_8x3[] = {
	0.875f,0.667f,0.875f,0.333f,0.750f,0.333f,
	0.750f,0.333f,0.750f,0.667f,0.875f,0.667f
};
static float player_turnleft_7_8x3[] = {
	1.000f,0.667f,1.000f,0.333f,0.875f,0.333f,
	0.875f,0.333f,0.875f,0.667f,1.000f,0.667f
};


static float player_turnright_0_8x3[] = {
	0.125f,0.333f,0.125f,0.000f,0.000f,0.000f,
	0.000f,0.000f,0.000f,0.333f,0.125f,0.333f
};//
static float player_turnright_1_8x3[] = {
	0.250f,0.333f,0.250f,0.000f,0.125f,0.000f,
	0.125f,0.000f,0.125f,0.333f,0.250f,0.333f
};//
static float player_turnright_2_8x3[] = {
	0.375f,0.333f,0.375f,0.000f,0.250f,0.000f,
	0.250f,0.000f,0.250f,0.333f,0.375f,0.333f
};//
static float player_turnright_3_8x3[] = {
	0.500f,0.333f,0.500f,0.000f,0.375f,0.000f,
	0.375f,0.000f,0.375f,0.333f,0.500f,0.333f
};//
static float player_turnright_4_8x3[] = {
	0.625f,0.333f,0.625f,0.000f,0.500f,0.000f,
	0.500f,0.000f,0.500f,0.333f,0.625f,0.333f
};//
static float player_turnright_5_8x3[] = {
	0.750f,0.333f,0.750f,0.000f,0.625f,0.000f,
	0.625f,0.000f,0.625f,0.333f,0.750f,0.333f
};//
static float player_turnright_6_8x3[] = {
	0.875f,0.333f,0.875f,0.000f,0.750f,0.000f,
	0.750f,0.000f,0.750f,0.333f,0.875f,0.333f
};//
static float player_turnright_7_8x3[] = {
	1.000f,0.333f,1.000f,0.000f,0.875f,0.000f,
	0.875f,0.000f,0.875f,0.333f,1.000f,0.333f
};
#endif