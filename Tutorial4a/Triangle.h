#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <psptypes.h>
extern "C" {
	#include "graphics.h"	
}

typedef struct {	float			u,v;
					unsigned int	color;
					float			x, y, z;		} vertex;	// vertex to render

class Triangle {

protected:
	vertex* triangle;
	float rot;
	ScePspFMatrix4 world;
	Image* texture;

public:
	Triangle();
	~Triangle();

	void Render();

};

#endif

