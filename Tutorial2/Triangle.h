#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <psptypes.h>

typedef struct {	unsigned int	color;
					float			x, y, z;		} vertex;	// vertex to render

class Triangle {

protected:
	vertex* triangle;
	float rot;
	ScePspFMatrix4 world;

public:
	Triangle();
	~Triangle();

	void Render();

};

#endif

