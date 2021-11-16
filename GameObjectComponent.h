#pragma once
#include "OBJLoader.h"

#include <vector>
#include "DDSTextureLoader.h"
#include "ShaderComponent.h"
#include "GraphicComponents.h"
#include "TextureComponent.h"
#include "VertexStruct.h"
#include "MeshStruct.h"
#include "ConstantStruct.h"

class GameObjectComponent
{
public:
	GameObjectComponent(GraphicComponents* gfx, char* file);

	void Update();
	void CreateTexture(wchar_t* path);
	void Draw();

	XMMATRIX CalculateTransform();







protected:

	ShaderComponent*	sfx;
	GraphicComponents*  gfx;
	TextureComponent*	TexComp;
	MeshData ObjectMesh;

	std::vector<ID3D11ShaderResourceView*> ObjectTextures;

	//Transformation Properties of an object
	XMFLOAT4X4 Transform;
	XMFLOAT3 Position;
	XMFLOAT3 Rotation;
	XMFLOAT3 Scale;

};

