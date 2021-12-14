#pragma once
#include "TransformationStructure.h"
#include "GraphicComponent.h"
#include "EntityTransformation.h"
#include "Mesh.h"
#include "OBJLoader.h"
class NewStar
{
public:
	NewStar(char* file , GraphicComponent* _gfx )
	{
		ObjectData star_data;
		star_data._File = file;

		star_data._Mesh = OBJLoader::Load(file , _gfx->_pd3dDevice);

		Transformation star_transformation;
		star_transformation.translation = XMFLOAT3(0.0f, 0.0f, 0.0f);
		star_transformation.rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
		star_transformation.scale = XMFLOAT3(0.20f, 0.20f, 0.20f);
		
		tran = new EntityTransformation(world, star_transformation.translation, star_transformation.rotation, star_transformation.scale);

	}
	

private:
	EntityTransformation* tran;
	XMFLOAT4X4 world;

};

