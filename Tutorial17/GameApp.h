#ifndef GAMEAPP_H_
#define GAMEAPP_H_

#include "GraphicsObject.h"
#include <psptypes.h>
#include "SkyBox.h"

class GameApp {

protected:
	GraphicsObject* gfx;
	SkyBox* sky;

	ScePspFMatrix4 projection;
	ScePspFMatrix4 view;

	float rot;

	int Controls();
	void Render();
	bool Load();

public:
	GameApp();
	~GameApp();
	int Run();

};


#endif
