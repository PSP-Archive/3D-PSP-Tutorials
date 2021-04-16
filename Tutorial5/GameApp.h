#ifndef GAMEAPP_H_
#define GAMEAPP_H_

#include "GraphicsObject.h"
#include "Triangle.h"
extern "C" {
	#include "graphics.h"
}

class GameApp {

protected:
	GraphicsObject* gfx;
	Triangle* triangle;
	Image* pic;

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
