#ifndef GAMEAPP_H_
#define GAMEAPP_H_

#include "GraphicsObject.h"
#include "UtilObject.h"

class GameApp {

protected:
	GraphicsObject* gfx;
	UtilObject* utils;

	int goodRandom;
	int badRandom;

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
