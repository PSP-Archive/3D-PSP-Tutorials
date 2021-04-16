#ifndef MODEL_H_
#define MODEL_H_

#include "GraphicsObject.h"

class Model {

protected:
	ObjMeshPart* parts;
	int partCount;
	bool Load(const char* file, const char* mtl);

public:
	Model(const char* file, const char* mtl);
	void Render();

};

#endif
