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
	sceGuEnable(GU_CLIP_PLANES);
	sceGuEnable(GU_LIGHTING);

	sceGuFinish();
	// wait untill the list has finished.
	sceGuSync(0,0);
	// turn on the display
	sceGuDisplay(GU_TRUE);

	return true;
}



