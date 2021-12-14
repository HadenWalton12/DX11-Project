#pragma once
#include "ObjectComponent.h"
#include "EntityTransformations.h"
class Star : public GameObjects
{
public:
	Star::Star(RenderingPipeline* pipeline ,VertexShader* VS, PixelShader* PS , XMFLOAT4X4 world) : GameObjects(pipeline)
	{
		_mesh = OBJLoader::Load("star.obj", _pPipeline->GetDevice());
		_pVertexShader = VS;
		_pPixelShader = PS;
		_World = world;

	}

	
	void CalculateTransformation() override
	{
		Transformation = new EntityTransformation(_World, Translate, Rotation, Scale);
	}
	XMFLOAT4X4 _World;
	EntityTransformation* Transformation;
	XMFLOAT3 Translate = XMFLOAT3(0.0f, 0.0f, -5.0f);
	XMFLOAT3 Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 Scale = XMFLOAT3(0.20f, 0.20f, 0.20f);
	VertexShader* _pVertexShader;
	PixelShader* _pPixelShader;
	MeshData _mesh;
};