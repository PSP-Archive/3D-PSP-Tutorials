#ifndef GAMEAPP_H_
#define GAMEAPP_H_

#include "GraphicsObject.h"

class GameApp {

protected:
	int frameCount;
	GraphicsObject* gfx;

	int Controls();
	void Render();
	bool Load();

public:
	GameApp();
	~GameApp();
	int Run();

};


#endif
