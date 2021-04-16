#include "GraphicsObject.h"
#include <pspgu.h>
#include <pspgum.h>

static unsigned int __attribute__((aligned(16))) list[262144];

GraphicsObject* GraphicsObject::_instance = 0;// initialize pointer

GraphicsObject* GraphicsObject::Instance (void) {
    
	if (_instance == 0){  
		_instance = new GraphicsObject; // create sole instance
    }
    return _instance; // address of sole instance
}

GraphicsObject::GraphicsObject(void) { 
    // creation of object
}

GraphicsObject::~GraphicsObject(void) {
	// clean up
}

bool GraphicsObject::Init3DGraphics(void) {

	// Initialize the GraphicalSystem
	sceGuInit();
	gumInit();
	sceGuStart(GU_DIRECT,list);
	sceGuDrawBuffer(GU_PSM_8888,(void*)0,512);
	sceGuDispBuffer(480,272,(void*)0x88000,512);
	sceGuDepthBuffer((void*)0x110000,512);
	sceGuOffset(2048 - (480/2),2048 - (272/2));

	// create a viewport centered at 2048,2048 width 480 and height 272
	sceGuViewport(2048,2048,480,272);
	sceGuDepthRange(0xc350,0x2710);

	sceGuScissor(0,0,480,272);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuDepthFunc(GU_GEQUAL);
	sceGuEnable(GU_DEPTH_TEST);
	sceGuFrontFace(GU_CW);
	sceGuShadeModel(GU_SMOOTH);
	sceGuEnable(GU_CULL_FACE);
	//sceGuEnable(GU_TEXTURE_2D);
	sceGuEnable(GU_CLIP_PLANES);
	sceGuEnable(GU_LIGHTING);
	//sceGuEnable(GU_BLEND);
	//sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
	sceGuFinish();
	// wait untill the list has finished.
	sceGuSync(0,0);
	// turn on the display
	sceGuDisplay(GU_TRUE);

	return true;
}


int GraphicsObject::Render2DLineOn3D(const float x1, const float y1, const float x2, const float y2, const unsigned int color) {

	sceGuDisable(GU_TEXTURE_2D);
	sceGuDisable(GU_DEPTH_TEST);

	lineVertex* Line = (lineVertex*)sceGuGetMemory(2 * sizeof(lineVertex));

	Line[0].color = color;
	Line[0].x = x1;
	Line[0].y = y1;
	Line[0].z = 0.0f;
	
	Line[1].color = color;
	Line[1].x = x2;
	Line[1].y = y2;
	Line[1].z = 0.0f;
	

	sceGuDrawArray(GU_LINES, GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_2D, 2, 0, Line);

	sceGuEnable(GU_DEPTH_TEST);
	sceGuEnable(GU_TEXTURE_2D);

	return 0;

}

int GraphicsObject::Render3DLine(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2, const unsigned int color) {

	sceGuDisable(GU_TEXTURE_2D);
	
	lineVertex* Line = (lineVertex*)sceGuGetMemory(2 * sizeof(lineVertex));

	Line[0].color = color;
	Line[0].x = x1;
	Line[0].y = y1;
	Line[0].z = z1;
	
	Line[1].color = color;
	Line[1].x = x2;
	Line[1].y = y2;
	Line[1].z = z1;
	
	sceGumMatrixMode(GU_MODEL); 
	sceGumLoadIdentity();
	sceGuDrawArray(GU_LINES, GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 2, 0, Line);
	sceGuEnable(GU_TEXTURE_2D);

	return 0;

}
