#include "ObjectComponent.h"

GameObjects::GameObjects(GraphicComponent* _gfx, char* file) : _gfx(_gfx) , _Shader(_Shader) , _Tex(_Tex)
{
	
	_mesh = OBJLoader::Load(file, _gfx->GetDevice());
	Initialise();
}

GameObjects::~GameObjects()
{
}

void GameObjects::Update()
{


}

void GameObjects::Draw()
{
	_Shader->ComposeShader(_gfx);
	_gfx->SwitchDrawBuffers(_mesh.VertexBuffer, _mesh.IndexBuffer);
	_Tex->BindTextures(0, _Textures.size(), _Textures , _gfx);

	
	_gfx->Draw(_mesh.IndexCount);
}



void GameObjects::CreateTexture(wchar_t* path)
{
	ID3D11ShaderResourceView* texture;
	_Tex->CreateTexture(path, &texture , _gfx);
	_Textures.push_back(texture);
}

void GameObjects::Initialise()
{
	_Shader = new ShaderComponent();
	_Shader->CreateShaderandLayout(_gfx);
}
