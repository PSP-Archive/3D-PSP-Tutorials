#ifndef GRAPHICSOBJECT_H_
#define GRAPHICSOBJECT_H_

extern "C" {
	#include "graphics.h"
}

typedef struct {	float			u, v;
					float			x, y, z;		} vertex2d;	// vertex to render


class GraphicsObject {

private:
	static GraphicsObject* _instance;

protected:
	GraphicsObject(void);
	GraphicsObject(const GraphicsObject&);
	GraphicsObject& operator= (const GraphicsObject&);

public:
	static GraphicsObject* Instance(void);
	~GraphicsObject(void);

	bool Init3DGraphics(void);

	int Render2DImageOn3D(float left, float top, const Image* texture);
};

#endif
