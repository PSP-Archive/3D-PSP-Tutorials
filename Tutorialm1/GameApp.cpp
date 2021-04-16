#include "GameApp.h"
#include "GraphicsObject.h"
#include <pspctrl.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspgu.h>



GameApp::GameApp() {

}

GameApp::~GameApp() {
	delete timer;
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

	// load timer object
	timer = new Timer();
	// start the timer
	timer->startTimer();
	
	return true;
}

int GameApp::Controls() {
	// reading controls
	SceCtrlData pad;
	sceCtrlReadBufferPositive(&pad, 1); 

	// check for input
	if (pad.Buttons != 0){
		if (pad.Buttons & PSP_CTRL_CROSS){
			if(buttonCross == 0) {
				buttonCross = 1;
				timer->resetTimer();
			}
		}
		if (pad.Buttons & PSP_CTRL_SQUARE){
			if(buttonSquare == 0) {
				buttonSquare = 1;
				timer->startTimer();
			}
		}
	}
	else {
		buttonCross = 0;
		buttonSquare = 0;
	}

	return 0;

}

void GameApp::Render() {
	// render information.
	pspDebugScreenSetXY(10, 5);
	pspDebugScreenPrintf("%d seconds elapsed\n", timer->getTimer());
	pspDebugScreenSetXY(4, 15);
	pspDebugScreenPrintf("Press Cross to reset timer.\n");
	pspDebugScreenSetXY(4, 20);
	pspDebugScreenPrintf("Press Square to start timer.\n");
	sceDisplayWaitVblankStart();
	sceGuSwapBuffers();
}
