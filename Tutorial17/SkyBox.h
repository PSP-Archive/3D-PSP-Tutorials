#ifndef SKYBOX_H
#define SKYBOX_H

#include "GraphicsObject.h"
#include <psptypes.h>

extern "C" {
	#include "graphics.h"
}

class SkyBox {

protected:

	ScePspFMatrix4	world;

	vertex2d*		boxside1;
	vertex2d*		boxside2;
	vertex2d*		boxside3;
	vertex2d*		boxside4;
	Image*			texture1;
	Image*			texture2;
	Image*			texture3;
	Image*			texture4;
	void CreateBox();

public:
	SkyBox();
	~SkyBox();
	void Render(ScePspFVector3 pos);



};

#endif
