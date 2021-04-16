#include "GameApp.h"
#include "GraphicsObject.h"
#include <pspctrl.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspgu.h>


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

	// create the loading thread
	loadscr = new LoadingScreen();
	
	// set frameCount
	frameCount = 0;

	for(int i=0;i<300;i++){
		//wait everytime for the screen blank, total 5 seconds
		sceDisplayWaitVblankStart();
	}

	// we stop the loading screen
	loadscr->KillLoadingScreen();
	// we remove it from memory
	delete(loadscr);

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
	
	frameCount++;
	pspDebugScreenSetXY(1,1);
	pspDebugScreenPrintf("Rendering frame %d\n", frameCount);
	
	// ending rendering
	sceGuFinish();
	sceGuSync(0,0);
	sceDisplayWaitVblankStart();
	sceGuSwapBuffers();
}
