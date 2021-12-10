#include "ObjectComponent.h"

GameObjects::GameObjects(GraphicComponent* _gfx) : _gfx(_gfx) , _Shader(_Shader) , _Tex(_Tex) , world(world)
{
	
	Initialise();
}

GameObjects::~GameObjects()
{
}



void GameObjects::Update(GraphicComponent* gfx)
{
	CalculateTransformation();

}

void GameObjects::Draw()
{
	LoadMesh();

	_gfx->UpdateConstantBuffer(world);
	_Shader->ComposeShader(_gfx);


	_Tex->BindTextures(0, _Textures.size(), _Textures , _gfx);
	_gfx->_pImmediateContext->DrawIndexed(_mesh.IndexCount, 0, 0);



}

void GameObjects::CreateTexture(wchar_t* path)
{
	ID3D11ShaderResourceView* texture;
	_Tex->CreateTexture(path, &texture , _gfx);
	_Textures.push_back(texture);
}

void GameObjects::LoadMesh()
{
	
}
void GameObjects::LoadObject()
{

}
void GameObjects::Initialise()
{
	_Shader = new ShaderComponent();
	_Shader->CreateVertexShader(_gfx);
	_Shader->CreatePixelShader(_gfx);

}

void GameObjects::SwitchDrawBuffers(ID3D11Buffer* VB, ID3D11Buffer* IB , GraphicComponent* _gfx)
{

}

void GameObjects::CalculateTransformation()
{
}






void GameObjects::SetRotation(float x, float y, float z)
{
	ObjectRotation = XMFLOAT3(x, y, z);
}

void GameObjects::SetTranslation(float x, float y, float z)
{
	ObjectTranslation = XMFLOAT3(x, y, z);
}
void GameObjects::SetScale(float x, float y, float z)
{

	ObjectScale = XMFLOAT3( x,  y,  z);
}
