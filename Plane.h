#pragma once
#include "ObjectComponent.h"

class Plane : public GameObjects
{
public:
	Plane::Plane(GraphicComponent* gfx, ShaderComponent* _Shader, TextureComponent* _Tex, XMFLOAT4X4 world) : GameObjects(gfx) {}
	void LoadMesh()
	{
		_mesh = OBJLoader::Load("Hercules.obj", _gfx->GetDevice());
		SwitchDrawBuffers(_mesh.VertexBuffer, _mesh.IndexBuffer, _gfx);
	}
	void CalculateTransformation() override;

	void SwitchDrawBuffers(ID3D11Buffer* VB, ID3D11Buffer* IB, GraphicComponent* _gfx) override;
};