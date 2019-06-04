#include "XCDialog.h"
#include "../util/ImageLoader.h"
#include "../util/ShaderReader.h"
#include "../XCShape/XCDefaultShape.h"
#include "../XCFont/XCFont.h"
#include <GL3/gl3w.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include <sstream>
#include FT_FREETYPE_H  
bool xc_se::XCDialog::have_resource_init = false;
bool xc_se::XCDialog::have_program_init = false;
GLuint xc_se::XCDialog::vao[2];
GLuint xc_se::XCDialog::vbo[2];
GLuint xc_se::XCDialog::tbo[2];
GLuint xc_se::XCDialog::program[2];
using namespace xc_ogl;
void xc_se::XCDialog::ShaderInit()
{
	
}

void xc_se::XCDialog::TextureInit()
{
	if (!have_resource_init) {
////////////////////////×Ö·ûÎÆÀí¼ÓÔØStart/////////////////////////////////////////
	
////////////////////////×Ö·ûÎÆÀí¼ÓÔØFinish/////////////////////////////////////////
		have_resource_init = true;
	}
}

void xc_se::XCDialog::BufferInit()
{
	glGenVertexArrays(2, vao);
	glGenBuffers(2, vbo);
////////////////////Char start////////////
	
}
void xc_se::XCDialog::DialogInit()
{
	ShaderInit();
	TextureInit();
	BufferInit();
}

void xc_se::XCDialog::DialogRender()
{
}

void xc_se::XCDialog::DialogRelease()
{
	glDeleteVertexArrays(2, vao);
	glDeleteBuffers(2, vbo);
}
