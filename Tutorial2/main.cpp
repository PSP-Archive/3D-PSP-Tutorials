#include <psptypes.h>
#include <pspmoduleinfo.h>
#include <pspthreadman.h>
#include <pspkernel.h>
#include "GameApp.h"
#include <pspdebug.h>
#include <pspgu.h>
#include <psppower.h>


// MODULE INITIALISATION

PSP_MODULE_INFO("Tutorial2", 0x0000, 1, 1);


/*!
*	\fn int exit_callback(int arg1, int arg2, void *common) 
*	\brief Exits the game.
*
*	@return			0
*/
int exit_callback(int arg1, int arg2, void *common) {
	  sceKernelExitGame();
	  return 0;
}


/*!
*	\fn int CallbackThread(SceSize args, void *argp) 
*	\brief callback thread.
*
*	@return			0
*/
int CallbackThread(SceSize args, void *argp) {
	  int cbid;

	  cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	  sceKernelRegisterExitCallback(cbid);

	  sceKernelSleepThreadCB();

	  return 0;
}


/*!
*	\fn int SetupCallbacks(void)
*	\brief Creates a callback thread and returns the thread ID.
*
*	@return			thid
*/
int SetupCallbacks(void) {
	  int thid = 0;

	  thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);   //als er foutenzijn dan  kan het hieraanliggen
	  if(thid >= 0) {
				sceKernelStartThread(thid, 0, 0);
	  }

	  return thid;
} 



/*!
*	\fn int Main(void)
*	\brief The main function
*
*	@return			0
*/
int main (void) {

	// set the speed better
	//scePowerSetClockFrequency(333, 333, 166);

	// init the debug screen functions
	pspDebugScreenInit();

	// setup the callbacks
	SetupCallbacks();

	// creating the game object
	GameApp* game = new GameApp();
	// run the game app and get return value
	int ret = game->Run();

	// shutdown
	sceGuTerm();
	sceKernelExitGame(); 

	return 0;
}




