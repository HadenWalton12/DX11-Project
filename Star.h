#pragma once
#include "ObjectComponent.h"

class Star : public GameObjects
{
public:
	Star::Star(GraphicComponent* gfx , ShaderComponent* _Shader , TextureComponent* _Tex , XMFLOAT4X4 world) : GameObjects(gfx) {}

	void LoadMesh()
	{
		_mesh = OBJLoader::Load("Star.obj", _gfx->GetDevice());
		SwitchDrawBuffers(_mesh.VertexBuffer, _mesh.IndexBuffer, _gfx);
	}
	void CalculateTransformation()override;
 
	void SwitchDrawBuffers(ID3D11Buffer* VB, ID3D11Buffer* IB, GraphicComponent* _gfx) override;

};