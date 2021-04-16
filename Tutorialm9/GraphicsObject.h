#ifndef GRAPHICSOBJECT_H_
#define GRAPHICSOBJECT_H_

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
