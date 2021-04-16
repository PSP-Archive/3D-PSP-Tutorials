#include "LoadingScreen.h"
#include <pspthreadman.h>
#include <pspgu.h>
#include <pspgum.h>
#include <pspdisplay.h>
#include "GraphicsObject.h"
extern "C" {
	#include "graphics.h"
}

static unsigned int __attribute__((aligned(16))) list[262144];
Image* load1;
Image* load2;

LoadingScreen::LoadingScreen() {
	// the loadingscreen is loaded as a thread
	thid_ = sceKernelCreateThread("LoadingThread", RunLoadingScreen, 0x18, 0x10000, 0, NULL);
	// start the thread
	sceKernelStartThread(thid_, 0, 0);
}


void LoadingScreen::KillLoadingScreen() {
	// shut down the loading screen again.
	sceKernelTerminateDeleteThread(thid_);
	// free the mem space of the images
	freeImage(load1);
	freeImage(load2);
}


int LoadingScreen::RunLoadingScreen(SceSize args, void *argp) {

	// first create the graphicspart
	GraphicsObject* gfx = GraphicsObject::Instance();

	// load up the images
	load1 = loadImage("load1.png");
	load2 = loadImage("load2.png");

	// set animation to 0
	int	animation_ = 0;
	
	// start the render loop
	while(1) {
		
		// render information.
		sceGuStart(GU_DIRECT,list);

		// clear screen
		sceGuClearColor(0xff000000);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

		// set the ambient light
		sceGuAmbient(0xffffffff);

		// setting the view
		sceGumMatrixMode(GU_VIEW); 
		sceGumLoadIdentity();

		// the loading graphics :)
		animation_++;
		if(animation_ > 19)
			animation_ = 0;

		// switch images now and then
		if (animation_ < 10)
			gfx->Render2DImageOn3D(117, 100, load1);
		else if (animation_ < 20)
			gfx->Render2DImageOn3D(117, 100, load2);

		// ending rendering
		sceGuFinish();
		sceGuSync(0,0);
		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();
	}
	return 0;
}

