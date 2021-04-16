#include "Triangle.h"
#include <pspgu.h>
#include <pspgum.h>
#include "malloc.h"


Triangle::Triangle() {

	triangle = (vertex*)memalign(16,3 * sizeof(vertex));
	triangle[0].color = 0xffffffff;
	triangle[0].x = -4.0f;
	triangle[0].y = 2.0f;
	triangle[0].z = 10.0f;

	triangle[1].color = 0xffffffff;
	triangle[1].x = 0.0f;
	triangle[1].y = -2.0f;
	triangle[1].z = 10.0f;

	triangle[2].color = 0xffffffff;
	triangle[2].x = 4.0f;
	triangle[2].y = 2.0f;
	triangle[2].z = 10.0f;

	rot = 0.0f;
}

Triangle::~Triangle() {
	delete(triangle);
}

void Triangle::Render() {

	rot += 0.05f;

	sceGumMatrixMode(GU_MODEL); 
	sceGumLoadIdentity();
	sceGumRotateY(rot);

	sceGumDrawArray(GU_TRIANGLES, GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 3, 0, triangle);	
}



