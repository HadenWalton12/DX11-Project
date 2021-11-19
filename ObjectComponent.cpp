#include "ObjectComponent.h"

GameObjects::GameObjects(GraphicComponent* _gfx, char* file) : _gfx(_gfx)
{
	_mesh = OBJLoader::Load(file, this->_gfx->GetDevice());
	Initialise();
}

GameObjects::~GameObjects()
{
}

void GameObjects::Update()
{
	XMStoreFloat4x4(&mTransform, CalculateTransform());
}

void GameObjects::Draw()
{
	_Shader->ComposeShader();
	_gfx->SwitchDrawBuffers(_mesh.VertexBuffer, _mesh.IndexBuffer);
	_gfx->UpdateConstantBuffer();
	_gfx->BindTextures(0, _Textures.size(), _Textures);

	
	_gfx->Draw(_mesh.IndexCount);
}

XMMATRIX GameObjects::CalculateTransform()
{
	XMMATRIX transformMatrix = XMLoadFloat4x4(&mTransform);

	XMMATRIX objectScale = XMMatrixScaling(mScale.x, mScale.y, mScale.z);
	XMMATRIX objectPosition = XMMatrixTranslation(mPosition.x, mPosition.y, mPosition.z);
	XMMATRIX objectRotation = XMMatrixRotationRollPitchYaw(mRotation.x, mRotation.y, mRotation.z);

	XMMATRIX calculatedTransform = XMMatrixMultiply(objectScale, objectPosition) * objectRotation;

	XMStoreFloat4x4(&mTransform, calculatedTransform);

	return calculatedTransform;
}

void GameObjects::CreateTexture(wchar_t* path)
{
	ID3D11ShaderResourceView* texture;



	_gfx->CreateTexture(path, &texture);
	_Textures.push_back(texture);
}

void GameObjects::Initialise()
{
	XMStoreFloat4x4(&mTransform, XMMatrixIdentity());
	mPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mRotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mScale = XMFLOAT3(1.0f, 1.0f, 1.0f);


	_Shader = new ShaderComponent(_gfx);
	_Shader->CreateShaderandLayout();
}

