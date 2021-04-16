#include <psptypes.h>
#include <pspmoduleinfo.h>
#include <pspthreadman.h>
#include <pspkernel.h>
#include "GraphicsObject.h"
#include <pspdebug.h>
#include <pspgu.h>


// MODULE INITIALISATION

PSP_MODULE_INFO("Tutorial0", 0x0000, 1, 1);


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

	// setup the callbacks
	SetupCallbacks();

	// setup the environment
	GraphicsObject* gfx = GraphicsObject::Instance();
	// init the 3D environment
	gfx->Init3DGraphics();

	// shutdown
	sceGuTerm();
	sceKernelExitGame(); 

	return 0;
}

