#ifndef GAMEAPP_H_
#define GAMEAPP_H_

#include "GraphicsObject.h"
#include "Timer.h"

class GameApp {

protected:
	GraphicsObject* gfx;
	Timer* timer;

	int buttonCross;
	int buttonSquare;

	int Controls();
	void Render();
	bool Load();

public:
	GameApp();
	~GameApp();
	int Run();

};


#endif
