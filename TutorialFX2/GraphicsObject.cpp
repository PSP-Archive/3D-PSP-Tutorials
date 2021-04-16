#include "GraphicsObject.h"
#include <pspgu.h>
#include <pspgum.h>

static unsigned int __attribute__((aligned(16))) list[262144];

GraphicsObject* GraphicsObject::_instance = 0;// initialize pointer

GraphicsObject* GraphicsObject::Instance (void) {
    
	if (_instance == 0){  
		_instance = new GraphicsObject; // create sole instance
    }
    return _instance; // address of sole instance
}

GraphicsObject::GraphicsObject(void) { 
    // creation of object
}

GraphicsObject::~GraphicsObject(void) {
	// clean up
}

bool GraphicsObject::Init3DGraphics(void) {

	// Initialize the GraphicalSystem
	sceGuInit();
	sceGuStart(GU_DIRECT,list);
	sceGuDrawBuffer(GU_PSM_8888,(void*)0,512);
	sceGuDispBuffer(480,272,(void*)0x88000,512);
	sceGuDepthBuffer((void*)0x110000,512);
	sceGuOffset(2048 - (480/2),2048 - (272/2));

	// create a viewport centered at 2048,2048 width 480 and height 272
	sceGuViewport(2048,2048,480,272);
	sceGuDepthRange(0xc350,0x2710);

	sceGuScissor(0,0,480,272);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuDepthFunc(GU_GEQUAL);
	sceGuEnable(GU_DEPTH_TEST);
	sceGuFrontFace(GU_CW);
	sceGuShadeModel(GU_SMOOTH);
	sceGuEnable(GU_CULL_FACE);
	sceGuEnable(GU_TEXTURE_2D);
	sceGuEnable(GU_CLIP_PLANES);

	sceGuEnable(GU_BLEND);
	sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);

	sceGuFinish();
	// wait untill the list has finished.
	sceGuSync(0,0);
	// turn on the display
	sceGuDisplay(GU_TRUE);

	return true;
}


int GraphicsObject::Render2DImageOn3D(float left, float top, const Image* texture) {

	vertex2d* DisplayVertices = (vertex2d*) sceGuGetMemory(4 * sizeof(vertex2d));

	// we do not need to test for depth
	sceGuDisable(GU_DEPTH_TEST); 
	// setting the texture
	sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGBA);
	sceGuTexMode(GU_PSM_8888, 0 ,0 ,0);
	sceGuTexImage(0, texture->textureWidth, texture->textureHeight, texture->textureWidth, (void*) texture->data);

	// setting the 4 vertices			
	DisplayVertices[0].u = 0.0f;
	DisplayVertices[0].v = 0.0f;
	DisplayVertices[0].x = left;
	DisplayVertices[0].y = top;
	DisplayVertices[0].z = 0.0f;

	DisplayVertices[1].u = texture->textureWidth-1;
	DisplayVertices[1].v = 0.0f;
	DisplayVertices[1].x = left + texture->textureWidth;
	DisplayVertices[1].y = top;
	DisplayVertices[1].z = 0.0f;

	DisplayVertices[2].u = 0.0f;
	DisplayVertices[2].v = texture->textureHeight-1;
	DisplayVertices[2].x = left;
	DisplayVertices[2].y = top + texture->textureHeight;
	DisplayVertices[2].z = 0.0f;

	DisplayVertices[3].u = texture->textureWidth-1;
	DisplayVertices[3].v = texture->textureHeight-1;
	DisplayVertices[3].x = left + texture->textureWidth;
	DisplayVertices[3].y = top + texture->textureHeight;
	DisplayVertices[3].z = 0.0f;

	// draw the trianglestrip with transform 2D
	sceGuDrawArray(GU_TRIANGLE_STRIP, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_2D, 4, 0, DisplayVertices);

	// enable the depthtesting again.
	sceGuEnable(GU_DEPTH_TEST); 

	return 0;
};

int GraphicsObject::RenderScreenFade(const unsigned int r, const unsigned int g,const unsigned int b,const int alphaPercentage) {

	sceGuDisable(GU_DEPTH_TEST); 
	sceGuDisable(GU_TEXTURE_2D);

	vertexc2d* vertices = (vertexc2d*) sceGuGetMemory(2 * sizeof(vertexc2d)); 

	vertices[0].color = GU_RGBA(r, g, b, alphaPercentage); 
	vertices[0].x = 0; 
	vertices[0].y = 0; 
	vertices[0].z = 0; 
	vertices[1].color = GU_RGBA(r, g, b, alphaPercentage); 
	vertices[1].x = 480; 
	vertices[1].y = 272; 
	vertices[1].z = 0; 

	sceGuDrawArray(GU_SPRITES, GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_2D, 2, 0, vertices); 

	sceGuEnable(GU_TEXTURE_2D);
	sceGuEnable(GU_DEPTH_TEST); 

	return 0;
};



