#include "GameApp.h"
#include "GraphicsObject.h"
#include <pspctrl.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspgu.h>
#include <time.h>
#include <psprtc.h>
#include "stdio.h"


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

	sceRtcGetCurrentTick(&previous);
	res = sceRtcGetTickResolution();


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
	frames++;
	sceRtcGetCurrentTick( &now );
	
	if( ((now - previous)/((float)res)) >= 1.0f )
	{
		previous = now;
		sprintf(fps, "FPS: %d", frames);
		frames = 0;
	}

	pspDebugScreenSetXY(0, 0);
	pspDebugScreenPrintf("Frames per second: %s\n", fps);
	sceDisplayWaitVblankStart();
	sceGuSwapBuffers();
}
