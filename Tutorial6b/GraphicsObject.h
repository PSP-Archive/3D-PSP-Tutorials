#ifndef GRAPHICSOBJECT_H_
#define GRAPHICSOBJECT_H_

typedef struct {	unsigned int		color;
					float				x, y, z;		} lineVertex;

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
	int Render2DLineOn3D(const float x1, const float y1, const float x2, const float y2, const unsigned int color);
	int Render3DLine(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2, const unsigned int color);
};

#endif
