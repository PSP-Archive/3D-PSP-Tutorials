// PSP includes
#include <pspgu.h>
#include <pspgum.h>

// Misc includes
#include "malloc.h"

// Own includes
#include "SkyBox.h"


SkyBox::SkyBox() {

	// loading the images
	texture1 = loadImage("land1.png");
	texture2 = loadImage("land2.png");
	texture3 = loadImage("land3.png");
	texture4 = loadImage("land4.png");

	// create the skybox geometry
	CreateBox();	
}

SkyBox::~SkyBox() {
	// free images
	freeImage(texture1);
	freeImage(texture2);
	freeImage(texture3);
	freeImage(texture4);

	// free vertices
	delete(boxside1);
	delete(boxside2);
	delete(boxside3);
	delete(boxside4);
}

void SkyBox::CreateBox() {

	// side 1
	boxside1 = (vertex2d*)memalign(16,4 * sizeof(vertex2d));
	boxside1[0].u = 0.0f;
	boxside1[0].v = 0.0f;
	boxside1[0].x = -3.5f;
	boxside1[0].y = 3.5f;
	boxside1[0].z = -3.5f;

	boxside1[1].u = 1.0f;
	boxside1[1].v = 0.0f;
	boxside1[1].x = 3.5f;
	boxside1[1].y = 3.5f;
	boxside1[1].z = -3.5f;

	boxside1[2].u = 0.0f;
	boxside1[2].v = 1.0f;
	boxside1[2].x = -3.5f;
	boxside1[2].y = -3.5f;
	boxside1[2].z = -3.5f;

	boxside1[3].u = 1.0f;
	boxside1[3].v = 1.0f;
	boxside1[3].x = 3.5f;
	boxside1[3].y = -3.5f;
	boxside1[3].z = -3.5f;

	// side 2
	boxside2 = (vertex2d*)memalign(16,4 * sizeof(vertex2d));
	boxside2[0].u = 0.0f;
	boxside2[0].v = 0.0f;
	boxside2[0].x = 3.5f;
	boxside2[0].y = 3.5f;
	boxside2[0].z = -3.5f;

	boxside2[1].u = 1.0f;
	boxside2[1].v = 0.0f;
	boxside2[1].x = 3.5f;
	boxside2[1].y = 3.5f;
	boxside2[1].z = 3.5f;

	boxside2[2].u = 0.0f;
	boxside2[2].v = 1.0f;
	boxside2[2].x = 3.5f;
	boxside2[2].y = -3.5f;
	boxside2[2].z = -3.5f;

	boxside2[3].u = 1.0f;
	boxside2[3].v = 1.0f;
	boxside2[3].x = 3.5f;
	boxside2[3].y = -3.5f;
	boxside2[3].z = 3.5f;

	// side 3
	boxside3 = (vertex2d*)memalign(16,4 * sizeof(vertex2d));
	boxside3[0].u = 0.0f;
	boxside3[0].v = 0.0f;
	boxside3[0].x = 3.5f;
	boxside3[0].y = 3.5f;
	boxside3[0].z = 3.5f;

	boxside3[1].u = 1.0f;
	boxside3[1].v = 0.0f;
	boxside3[1].x = -3.5f;
	boxside3[1].y = 3.5f;
	boxside3[1].z = 3.5f;

	boxside3[2].u = 0.0f;
	boxside3[2].v = 1.0f;
	boxside3[2].x = 3.5f;
	boxside3[2].y = -3.5f;
	boxside3[2].z = 3.5f;

	boxside3[3].u = 1.0f;
	boxside3[3].v = 1.0f;
	boxside3[3].x = -3.5f;
	boxside3[3].y = -3.5f;
	boxside3[3].z = 3.5f;

	// side 4
	boxside4 = (vertex2d*)memalign(16,4 * sizeof(vertex2d));
	boxside4[0].u = 0.0f;
	boxside4[0].v = 0.0f;
	boxside4[0].x = -3.5f;
	boxside4[0].y = 3.5f;
	boxside4[0].z = 3.5f;

	boxside4[1].u = 1.0f;
	boxside4[1].v = 0.0f;
	boxside4[1].x = -3.5f;
	boxside4[1].y = 3.5f;
	boxside4[1].z = -3.5f;

	boxside4[2].u = 0.0f;
	boxside4[2].v = 1.0f;
	boxside4[2].x = -3.5f;
	boxside4[2].y = -3.5f;
	boxside4[2].z = 3.5f;

	boxside4[3].u = 1.0f;
	boxside4[3].v = 1.0f;
	boxside4[3].x = -3.5f;
	boxside4[3].y = -3.5f;
	boxside4[3].z = -3.5f;


}


void SkyBox::Render(ScePspFVector3 pos) {
	
	sceGuDepthMask(GU_TRUE); // disable writes to the depth buffer
	
	sceGumMatrixMode(GU_MODEL); 
	sceGumLoadIdentity(); 
	sceGumTranslate(&pos); 
	
	sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGBA);
	sceGuTexMode(GU_PSM_8888, 0 ,0 ,0);
	sceGuTexFilter(GU_LINEAR,GU_LINEAR);
	sceGuTexWrap(GU_CLAMP, GU_CLAMP);

	sceGuTexImage(0, texture1->textureWidth, texture1->textureHeight, texture1->textureWidth, (void*)texture1->data);
	sceGumDrawArray(GU_TRIANGLE_STRIP,GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D,4,0,boxside1);
	sceGuTexImage(0, texture2->textureWidth, texture2->textureHeight, texture2->textureWidth, (void*)texture2->data);
	sceGumDrawArray(GU_TRIANGLE_STRIP,GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D,4,0,boxside2);
	sceGuTexImage(0, texture3->textureWidth, texture3->textureHeight, texture3->textureWidth, (void*)texture3->data);
	sceGumDrawArray(GU_TRIANGLE_STRIP,GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D,4,0,boxside3);
	sceGuTexImage(0, texture4->textureWidth, texture4->textureHeight, texture4->textureWidth, (void*)texture4->data);
	sceGumDrawArray(GU_TRIANGLE_STRIP,GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D,4,0,boxside4);

	sceGuDepthMask(GU_FALSE); // enable writes to the depth buffer
}
