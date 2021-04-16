#include "Triangle.h"
#include <pspgu.h>
#include <pspgum.h>
#include "malloc.h"
#include "stdio.h"


Triangle::Triangle() {

	triangle = (vertex*)memalign(16,3 * sizeof(vertex));
	triangle[0].u = 0.0f;
	triangle[0].v = 0.0f;
	triangle[0].color = 0xffffffff;
	triangle[0].x = -4.0f;
	triangle[0].y = 2.0f;
	triangle[0].z = 10.0f;

	triangle[1].u = 0.5f;
	triangle[1].v = 1.0f;
	triangle[1].color = 0xffffffff;
	triangle[1].x = -4.0f;
	triangle[1].y = -2.0f;
	triangle[1].z = 10.0f;

	triangle[2].u = 1.0f;
	triangle[2].v = 0.0f;
	triangle[2].color = 0xffffffff;
	triangle[2].x = 4.0f;
	triangle[2].y = 2.0f;
	triangle[2].z = 10.0f;

	rot = 1.5f;

	//char buffer[256];
	//sprintf(buffer, "texture.png");
	texture = loadImage("texture.png");
}

Triangle::~Triangle() {
	delete(triangle);
}

void Triangle::Render() {

	rot += 0.01f;

	sceGumMatrixMode(GU_MODEL); 
	sceGumLoadIdentity();
	sceGumRotateY(rot);

	sceGuTexMode(GU_PSM_8888, 0 ,0 ,0);
	sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGB);
	sceGuTexFilter(GU_LINEAR, GU_LINEAR);
	sceGuTexScale(1.0f, 1.0f);
	sceGuTexImage(0, texture->textureWidth, texture->textureHeight, texture->textureWidth, (void*)texture->data);
	sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 3, 0, triangle);	
}



