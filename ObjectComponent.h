#pragma once
#include "OBJLoader.h"
#include "GraphicComponent.h"
#include "ShaderComponent.h"

#include <vector>
#include "DDSTextureLoader.h"
#include "Structure.h"

class GameObjects
{
public:
	GameObjects(GraphicComponent* _gfx , char* file);
	~GameObjects();

	void Update();
	void Draw();
	XMMATRIX CalculateTransform();
	void CreateTexture(wchar_t* path);

private:
	void Initialise();

	GraphicComponent* _gfx;
protected:
	MeshData _mesh;
	ShaderComponent* _Shader;
	std::vector<ID3D11ShaderResourceView*> _Textures;
	//Transform Properties
	XMFLOAT4X4 mTransform;
	XMFLOAT3 mPosition;
	XMFLOAT3 mRotation;
	XMFLOAT3 mScale;
};

