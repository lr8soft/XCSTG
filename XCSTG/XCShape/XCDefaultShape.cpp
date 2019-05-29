#include "XCDefaultShape.h"
#include <iostream>
#include <glm/glm.hpp>
void testfunc(float *arrayptr);
float* GetSpecificTexture(int column, int row, int ix, int iy)
{
	float x = ix; float y = iy;
	static float returnArray[24];
	returnArray[0] = 1.0f;
	returnArray[1] = 1.0f;
	returnArray[2] = x/column;
	returnArray[3] = y/row;

	returnArray[4] = 1.0f;
	returnArray[5] = -1.0f,
	returnArray[6] = x / column;
	returnArray[7] = (y -1)/ row;

	returnArray[8] = -1.0f;
	returnArray[9] = -1.0f,
	returnArray[10] = (x - 1)/ column;
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
#ifdef _DEBUG
	//testfunc(returnArray);
#endif
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