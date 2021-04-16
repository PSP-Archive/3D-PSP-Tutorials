#ifndef GAMEAPP_H_
#define GAMEAPP_H_

#include "GraphicsObject.h"
#include <psptypes.h>

class GameApp {

protected:
	int frameCount;
	GraphicsObject* gfx;

	ScePspFMatrix4 projection;
	ScePspFMatrix4 view;

	int Controls();
	void Render();
	bool Load();

public:
	GameApp();
	~GameApp();
	int Run();

};


#endif
