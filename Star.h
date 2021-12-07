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
	void CalculateTransformation() 
	{
		Timer t;
		XMMATRIX scale = XMMatrixScaling(ObjectScale.x, ObjectScale.y, ObjectScale.z);
		XMMATRIX translation = XMMatrixTranslation(ObjectTranslation.x, ObjectTranslation.y, ObjectTranslation.z);
		XMMATRIX rotation = XMMatrixRotationRollPitchYaw(ObjectRotation.x , ObjectRotation.y * t.time, ObjectRotation.z);


		XMStoreFloat4x4(&world, scale * translation * rotation);
	}
	void SwitchDrawBuffers(ID3D11Buffer* VB, ID3D11Buffer* IB, GraphicComponent* _gfx) override;

};