#pragma once
#include "OBJLoader.h"
#include "GraphicComponent.h"
#include "ShaderComponent.h"
#include "TextureComponent.h"

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

	//Transform Properties
	XMFLOAT4X4 mTransform;
	XMFLOAT3 mPosition;
	XMFLOAT3 mRotation;
	XMFLOAT3 mScale;

	XMFLOAT4X4 GetTransform();
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();
	XMFLOAT3 GetScale();
private:
	void Initialise();

	GraphicComponent* _gfx;
	ShaderComponent* _Shader;
	TextureComponent* _Tex;

protected:
	MeshData _mesh;
	std::vector<ID3D11ShaderResourceView*> _Textures;


};

