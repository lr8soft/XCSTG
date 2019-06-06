#include "XCDefaultShape.h"
#include <iostream>
#include <glm/glm.hpp>
void testfunc(float *arrayptr);
float * GetCoveredPlaneWithTexVertex(float width_rate, float height_rate)
{
	static float returnArray[] = {
		width_rate, height_rate, 1.0f, 1.0f,
		width_rate,-height_rate, 1.0f, 0.0f,
		-width_rate,-height_rate, 0.0f, 0.0f,
		-width_rate,-height_rate, 0.0f, 0.0f,
		-width_rate, height_rate, 0.0f, 1.0f,
		width_rate, height_rate, 1.0f, 1.0f
	};
	return returnArray;
}
float * GetCoveredPlaneVertex(float width_rate, float height_rate)
{
	
	static float returnArray[] =
	{
		 width_rate, height_rate,
		 width_rate,-height_rate,
		-width_rate,-height_rate,
		-width_rate,-height_rate,
		-width_rate, height_rate,
		 width_rate, height_rate
	};
	return returnArray;
}
float* GetSpecificTexture(int column, int row, int ix, int iy)
{
	float x = ix; float y = iy;
	static float returnArray[24];
	returnArray[0] = 1.0f;
	returnArray[1] = 1.0f;
	returnArray[2] = x / column;
	returnArray[3] = y / row;

	returnArray[4] = 1.0f;
	returnArray[5] = -1.0f,
	returnArray[6] = x / column;
	returnArray[7] = (y - 1) / row;

	returnArray[8] = -1.0f;
	returnArray[9] = -1.0f,
	returnArray[10] = (x - 1) / column;
	returnArray[11] = (y - 1) / row;

	returnArray[12] = -1.0f;
	returnArray[13] = -1.0f,
	returnArray[14] = (x - 1) / column;
	returnArray[15] = (y - 1) / row;

	returnArray[16] = -1.0f;
	returnArray[17] = 1.0f,
	returnArray[18] = (x - 1) / column;
	returnArray[19] = y / row;

	returnArray[20] = 1.0f;
	returnArray[21] = 1.0f;
	returnArray[22] = x / column;
	returnArray[23] = y / row;

	return returnArray;
}
float * GetSpecificTexWithWidthAndHeight(float width_rate, float height_rate, int column, int row, int ix, int iy)
{
	float x = ix; float y = iy;
	static float returnArray[24];
	returnArray[0] = width_rate;
	returnArray[1] = height_rate;
	returnArray[2] = x / column;
	returnArray[3] = y / row;

	returnArray[4] = width_rate;
	returnArray[5] = -height_rate,
		returnArray[6] = x / column;
	returnArray[7] = (y - 1) / row;

	returnArray[8] = -width_rate;
	returnArray[9] = -height_rate,
		returnArray[10] = (x - 1) / column;
	returnArray[11] = (y - 1) / row;

	returnArray[12] = -width_rate;
	returnArray[13] = -height_rate,
		returnArray[14] = (x - 1) / column;
	returnArray[15] = (y - 1) / row;

	returnArray[16] = -width_rate;
	returnArray[17] = height_rate,
		returnArray[18] = (x - 1) / column;
	returnArray[19] = y / row;

	returnArray[20] = width_rate;
	returnArray[21] = height_rate;
	returnArray[22] = x / column;
	returnArray[23] = y / row;
	return returnArray;
}
float * GetPointSpriteVertex(float size)
{
	static float returnArray[4];
	returnArray[0] = 0.0f;
	returnArray[1] = 0.0f;
	returnArray[2] = 0.0f;
	returnArray[3] = size;
	return returnArray;
}
void testfunc(float *arrayptr) {
	for (int i = 0; i < 24;i++) {
		std::cout << arrayptr[i] << "  ";
		if ((i + 1) % 4 == 0)
			std::cout << std::endl;
	}
	std::cout << std::endl;
}