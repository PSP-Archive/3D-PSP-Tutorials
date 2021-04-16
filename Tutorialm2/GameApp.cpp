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

	// load the UtilObject
	utils = UtilObject::Instance();

	// initialize the randomizer.
	utils->InitRandomizer();

	// setting the initial state of the variables
	this->goodRandom = 0;
	this->badRandom = 0;
	
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
				this->badRandom = utils->getRandomIntBad(0,9);
			}
		}
		if (pad.Buttons & PSP_CTRL_SQUARE){
			if(buttonSquare == 0) {
				buttonSquare = 1;
				this->goodRandom = utils->getRandomIntGood(0,9);
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
	pspDebugScreenPrintf("The bad randomizer:  %d", this->badRandom);
	pspDebugScreenSetXY(10, 6);
	pspDebugScreenPrintf("The good randomizer: %d", this->goodRandom);
	pspDebugScreenSetXY(4, 15);
	pspDebugScreenPrintf("Press Cross to get bad random number.\n");
	pspDebugScreenSetXY(4, 20);
	pspDebugScreenPrintf("Press Square to get real random number.\n");
	sceDisplayWaitVblankStart();
	sceGuSwapBuffers();
}
