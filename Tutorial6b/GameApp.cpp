#include "GameApp.h"
#include "GraphicsObject.h"
#include <pspctrl.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspgu.h>
#include <pspgum.h>

static unsigned int __attribute__((aligned(16))) list[262144];


GameApp::GameApp() {

}

GameApp::~GameApp() {

}

int GameApp::Run() {

	if(!Load())
		return 1;
	
	// game loop
	while(1) {
		if (Controls() == 9) 
			break;
		Render();
	}
	return 0;
}

bool GameApp::Load() {
	// get pointer to Graphics object.
	gfx = GraphicsObject::Instance();
	// set up the environment.
	gfx->Init3DGraphics();

	// set frameCount
	frameCount = 0;

	// setting the projection
	sceGumMatrixMode(GU_PROJECTION); 
	sceGumLoadIdentity(); 
	sceGumPerspective(45.0f,16.0f/9.0f,2.0f,1000.0f);

	return true;
}

int GameApp::Controls() {
	// reading controls
	SceCtrlData pad;
	sceCtrlReadBufferPositive(&pad, 1); 

	// check for input
	if (pad.Buttons != 0){
		if (pad.Buttons & PSP_CTRL_CROSS){
				return 9;
		}
	}

	return 0;

}

void GameApp::Render() {
	// render information.
	sceGuStart(GU_DIRECT,list);

	// clear screen
	sceGuClearColor(0xff000000);
	sceGuClearDepth(0);
	sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

	// set the ambient light
	sceGuAmbient(0xffffffff);

	ScePspFVector3 pos = {0.0f,10.0f,30.0f};
	ScePspFVector3 at = {0.0f,0.0f,0.0f}; 
	ScePspFVector3 up = {0.0f,1.0f,0.0f}; 
	// setting the view
	sceGumMatrixMode(GU_VIEW); 
	sceGumLoadIdentity();
	sceGumLookAt(&pos, &at, &up);
	sceGumUpdateMatrix();

	gfx->Render3DLine(0.0f,0.0f, 0.0f, 0.0f, 4.0f, 0.0f, 0xffff6b38);
	gfx->Render2DLineOn3D(5,5, 475, 268, 0xffffffff);

	// ending rendering
	sceGuFinish();
	sceGuSync(0,0);
	sceDisplayWaitVblankStart();
	sceGuSwapBuffers();
}
