#ifndef GRAPHICSOBJECT_H_
#define GRAPHICSOBJECT_H_

extern "C" {
	#include "graphics.h"
}

typedef struct {	float u, v;
					unsigned int color;
					float nx, ny, nz;
					float x, y, z; } vertexfull; // vertex to render

typedef struct {	float u, v; } ScePspFTVector2;

typedef struct {	unsigned int	vertices[3];
					unsigned int	textc[3];		
					unsigned int	normals[3]; } FaceObj;
					
typedef struct {	unsigned int	faceCount;
					vertexfull		*Vertices;
					Image*			texture;		} ObjMeshPart;

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

};

#endif
