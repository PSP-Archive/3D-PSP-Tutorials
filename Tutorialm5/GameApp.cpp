#include "GameApp.h"
#include "GraphicsObject.h"
#include <pspctrl.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspgu.h>


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

	// turn on the analog stick
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

	return true;
}

int GameApp::Controls() {
	// reading controls
	SceCtrlData pad;

	sceCtrlPeekBufferPositive(&pad, 1); 

	float movementHorizontal, movementVertical;

	// getting the analog stick
	movementHorizontal = (float)(pad.Lx)-128.0f;
	//pspDebugScreenPrintf("Horizontal = %f\n",movementHorizontal);
	movementVertical = (float)(pad.Ly)-128.0f;
	//pspDebugScreenPrintf("movementVertical = %f\n",movementVertical);

	if (pad.Buttons != 0){
		if (pad.Buttons & PSP_CTRL_LEFT){
			pspDebugScreenPrintf("Pressed the left button...\n");
		}
		if (pad.Buttons & PSP_CTRL_RIGHT){
			pspDebugScreenPrintf("Pressed the right button...\n");
		}
		if (pad.Buttons & PSP_CTRL_UP){
			pspDebugScreenPrintf("Pressed the up button...\n");
		}
		if (pad.Buttons & PSP_CTRL_DOWN){
			pspDebugScreenPrintf("Pressed the down button...\n");
		}
		if (pad.Buttons & PSP_CTRL_CROSS){
			pspDebugScreenPrintf("Pressed the cross button...\n");
		}
		if (pad.Buttons & PSP_CTRL_SQUARE){
			pspDebugScreenPrintf("Pressed the square button...\n");
		}
		if (pad.Buttons & PSP_CTRL_TRIANGLE){
			pspDebugScreenPrintf("Pressed the triangle button...\n");
		}
		if (pad.Buttons & PSP_CTRL_CIRCLE){
			pspDebugScreenPrintf("Pressed the circle button...\n");
		}
		if (pad.Buttons & PSP_CTRL_START){
			pspDebugScreenPrintf("Pressed the start button...\n");
		}
		if (pad.Buttons & PSP_CTRL_SELECT){
			pspDebugScreenPrintf("Pressed the select button...\n");
		}
		if (pad.Buttons & PSP_CTRL_RTRIGGER){
			pspDebugScreenPrintf("Pressed the Right trigger button...\n");
		}
		if (pad.Buttons & PSP_CTRL_LTRIGGER){
			pspDebugScreenPrintf("Pressed the Left trigger button...\n");
		}
	}

	return 0;
}


void GameApp::Render() {
	// render information.
	//frameCount++;
	//pspDebugScreenPrintf("Rendering frame %d\n", frameCount);
	sceDisplayWaitVblankStart();
	sceGuSwapBuffers();
}
