#include "GameObjectComponent.h"

GameObjectComponent::GameObjectComponent(GraphicComponents* gfx, char* file) : gfx(gfx)
{
	ObjectMesh = OBJLoader::Load(file, gfx->_pPD3Ddevice, false);
	
	sfx->InitialiseShader(gfx->_pVertexShader, gfx->_pPixelShader, gfx->_pConstantBuffer);

}

void GameObjectComponent::Update()
{
}

void GameObjectComponent::CreateTexture(wchar_t* path)
{
	ID3D11ShaderResourceView* Tex;

	TexComp->CreateTexture(&Tex , path);
	ObjectTextures.push_back(Tex);

}

void GameObjectComponent::Draw()
{
	gfx->_pImmediateContext->PSSetShaderResources();
}

XMMATRIX GameObjectComponent::CalculateTransform()
{
	return XMMATRIX();
}
