#ifndef GAMEAPP_H_
#define GAMEAPP_H_

#include "GraphicsObject.h"
extern "C" {
	#include "graphics.h"
}

class GameApp {

protected:
	GraphicsObject* gfx;
	Image* pic;

	ScePspFMatrix4 projection;
	ScePspFMatrix4 view;

	bool fadeout;
	int fade;

	int Controls();
	void Render();
	bool Load();

public:
	GameApp();
	~GameApp();
	int Run();

};


#endif
