#pragma once
#include "OBJLoader.h"
#include "GraphicComponent.h"
#include "ShaderComponent.h"
#include "TextureComponent.h"

#include <vector>
#include "DDSTextureLoader.h"
#include "SimpleVertexStructure.h"
#include "LightingValuesStructure.h"
#include "ConstantStructure.h"
#include "TimeStructure.h"
#include "MeshStructure.h"


class SkyBox
{
public:
	SkyBox(GraphicComponent* gfx , ShaderComponent* Shader , TextureComponent* Tex , XMFLOAT4X4 world);
	~SkyBox();
	ID3D11Buffer* VertexBuffer;
	MeshData _mesh;
	ID3D11Buffer* IndexBuffer;
	void Draw();
	void UpdateSkybox();
	XMFLOAT4X4 _World;
	std::vector<ID3D11ShaderResourceView*> _Textures;	//Texture Vector to store multiple textures
	GraphicComponent* _gfx;
	TextureComponent* _Tex;
	ShaderComponent* _Shader;
	void CreateTexture(wchar_t* path);
	void SwitchDrawBuffers(ID3D11Buffer* VB, ID3D11Buffer* IB, GraphicComponent* _gfx);
};

