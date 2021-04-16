#include "Model.h"
#include <pspgu.h>
#include <pspgum.h>
#include "stdio.h"
#include "string.h"
#include "malloc.h"


Model::Model(const char* file, const char* mtl) {
	Load(file, mtl);
}

bool Model::Load(const char* file, const char* mtl) {

	char Textures[100][256];		// 2D array to store paths of the textures.
	char ReadBuffer[256];			// buffer use for reading files.
	char sBuffer[256];

	int textureCount = 0;			// variable to keep count of the number of textures in the model.
	
	// creating a FILE pointer
	FILE *fp = NULL;
	 
	// check whether the file can be opened.
	if ((fp = fopen(mtl, "rb")) == NULL) { return false; }
	
	// loop through the lines.
	while(!feof(fp)) {
		// get new line.
		fgets(ReadBuffer, 256, fp);
		// check if a texture is present.
		if (strncmp("map_Kd ", ReadBuffer, 7) == 0 ) {
			sprintf(Textures[textureCount],"%s", strtok((ReadBuffer+7),"#"));
			textureCount++;
		}
	}
	// close the file.
	fclose(fp);


	// read the object file
	// this is the first read. This reads how many elements there are.
	// With that information we can create the data structures.
	fpos_t position;
	int groupCount = 0;				// amount of groups in object file.
	int vertexCount = 0;			// amount of vertices in object file.
	int textureCoordCount = 0;		// amount of texture coordinates in object file.
	int faceCount = 0;				// amount of face in object file.
	int normalCount = 0;			// amount of normal in object file.


	if ((fp = fopen(file, "rb")) == NULL) { return false; }
	// we save the position so we can go back to the beginning
	fgetpos (fp, &position);
	while(!feof(fp)) {
		// read the line
		fgets(ReadBuffer, 256, fp);
		// check what kind of object is given in the line.
		if (strncmp("g default", ReadBuffer, 9) == 0 ) groupCount++;
		else if (strncmp("v ", ReadBuffer, 2) == 0 ) vertexCount++;
		else if (strncmp("vt ", ReadBuffer, 3) == 0 ) textureCoordCount++;
		else if (strncmp("f ", ReadBuffer, 2) == 0 ) faceCount++;
		else if (strncmp("vn ", ReadBuffer, 3) == 0 ) normalCount++; 
	}


	// prepare the arrays
	ScePspFVector3		Vertices[ vertexCount ];
	ScePspFTVector2		TexCoords[ textureCoordCount ];
	FaceObj				Faces[ faceCount ];
	ScePspFVector3		Normals[ normalCount ];
	// setting the number of modelgroups and get some memory for it.
	parts = (ObjMeshPart*)malloc(groupCount * sizeof(ObjMeshPart));
	// save the number of groups/parts
	partCount = groupCount;

	// go to the first line in the file.
	fsetpos(fp, &position);

	// variables
	int group = 0;
	int v = 0;
	int n = 0;
	int t = 0;
	int face = 0;
	int i = 0;
	int l = 0;
	int Correction = 0;
	int j = 0;
	int k = 0;


	while(!feof(fp))
	{
		fgets(ReadBuffer, 256, fp);

		if (strncmp("v ", ReadBuffer, 2) == 0 )
		{
			sscanf((ReadBuffer+2), "%f%f%f",&Vertices[ v ].x, &Vertices[ v ].y, &Vertices[ v ].z); 
			v++;
		}
		else if (strncmp("vn ", ReadBuffer, 3) == 0 )
		{
			sscanf((ReadBuffer+3), "%f%f%f",&Normals[ n ].x, &Normals[ n ].y, &Normals[ n ].z); 
			n++;
		}
		else if (strncmp("vt ", ReadBuffer, 3) == 0 )
		{
			sscanf((ReadBuffer+3), "%f%f",&TexCoords[ t ].u, &TexCoords[ t ].v); 
			t++;
		}

		else if (strncmp("f ", ReadBuffer, 2) == 0 )
		{
			
			char *pSplitString = NULL;
			i=0;
			pSplitString = strtok((ReadBuffer+2)," \t\n");

			do {

				sscanf((pSplitString), "%d/%d/%d",&Faces[ face ].vertices[ i ], &Faces[ face ].textc[ i ], &Faces[ face ].normals[ i ]); 
				Faces[ face ].textc[ i ] -= 1;		// 1 down because the obj file objects start at 1 and arrays start at 0
				Faces[ face ].vertices[ i ] -= 1;
				Faces[ face ].normals[ i ] -= 1;
				pSplitString = strtok(NULL," \t\n");
				i += 1;
			}
			while( pSplitString );

			face++;
		}
		
		else if (strncmp("EndGroup", ReadBuffer, 8) == 0 )
		{
			parts[group].Vertices = (vertexfull*)malloc((face-Correction) * 3 * sizeof(vertexfull));
			parts[group].faceCount = (face-Correction);
			l = 0;

			for (j=Correction;j<face;j++)
			{
				for (k=0; k<3; k++)
				{
					parts[group].Vertices[l].u = TexCoords[Faces[j].textc[k]].u;
					parts[group].Vertices[l].v = -(TexCoords[Faces[j].textc[k]].v);
					parts[group].Vertices[l].color = 0xffffffff;
					parts[group].Vertices[l].nx = Normals[Faces[j].normals[k]].x;
					parts[group].Vertices[l].ny = Normals[Faces[j].normals[k]].y;
					parts[group].Vertices[l].nz = Normals[Faces[j].normals[k]].z;
					parts[group].Vertices[l].x = Vertices[Faces[j].vertices[k]].x;
					parts[group].Vertices[l].y = Vertices[Faces[j].vertices[k]].y;
					parts[group].Vertices[l].z = Vertices[Faces[j].vertices[k]].z;
					l++;
				}
			}
			
			// the texture for this part.
			sprintf(sBuffer, "%s",Textures[group]); 
			parts[group].texture = loadImage(sBuffer);
			if (parts[group].texture == NULL) { fclose(fp); return false; }
			
			// increment the group number.
			Correction = face;
			group++;
		}
		else if (strncmp("v ", ReadBuffer, 2) == 0 )
		{
			sscanf((ReadBuffer+2), "%f%f%f",&Vertices[ v ].x, &Vertices[ v ].y, &Vertices[ v ].z); 
			v++;
		}
		else if (strncmp("vn ", ReadBuffer, 3) == 0 )
		{
			sscanf((ReadBuffer+3), "%f%f%f",&Normals[ n ].x, &Normals[ n ].y, &Normals[ n ].z); 
			n++;
		}
		else if (strncmp("vt ", ReadBuffer, 3) == 0 )
		{
			sscanf((ReadBuffer+3), "%f%f",&TexCoords[ t ].u, &TexCoords[ t ].v); 
			t++;
		}

		else if (strncmp("f ", ReadBuffer, 2) == 0 )
		{
			
			char *pSplitString = NULL;
			i=0;
			pSplitString = strtok((ReadBuffer+2)," \t\n");

			do {

				sscanf((pSplitString), "%d/%d/%d",&Faces[ face ].vertices[ i ], &Faces[ face ].textc[ i ], &Faces[ face ].normals[ i ]); 
				Faces[ face ].textc[ i ] -= 1;		// 1 down because the obj file objects start at 1 and arrays start at 0
				Faces[ face ].vertices[ i ] -= 1;
				Faces[ face ].normals[ i ] -= 1;
				pSplitString = strtok(NULL," \t\n");
				i += 1;
			}
			while( pSplitString );

			face++;
		}
	}
	fclose(fp);

	return true;
}


void Model::Render() {
	
	ScePspFVector3 pos = {0.0f, 0.0f, -10.0f};

	sceGumMatrixMode(GU_MODEL); 
	sceGumLoadIdentity(); 
	sceGumTranslate(&pos); 
		
	sceGuTexMode(GU_PSM_8888, 0 ,0 ,0);
	sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGB);
	sceGuTexFilter(GU_LINEAR, GU_LINEAR);
	sceGuTexScale(1.0f, 1.0f);
	sceGuTexOffset(0.0f, 0.0f);

	int i;

	for (i=0;i<partCount;i++)
	{
		sceGuTexImage(0, parts[i].texture->textureWidth, parts[i].texture->textureHeight, parts[i].texture->textureWidth, (void*)parts[i].texture->data);
		sceGumDrawArray(GU_TRIANGLES,GU_TEXTURE_32BITF|GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D,parts[i].faceCount*3,0,parts[i].Vertices);
	}
}

