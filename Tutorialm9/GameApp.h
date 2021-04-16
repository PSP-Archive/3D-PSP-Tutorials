#ifndef GAMEAPP_H_
#define GAMEAPP_H_

#include "GraphicsObject.h"
#include <psptypes.h>

class GameApp {

protected:
	GraphicsObject* gfx;

	int frames;		// for calculating the frames per second
	u32 res;			// resolution
	u64 now;			// the ticks at current point
	u64 previous;		// the ticks at the previous point
	char fps[100];		// the text buffer

	int Controls();
	void Render();
	bool Load();

public:
	GameApp();
	~GameApp();
	int Run();

};


#endif
