#include "SkyBox.h"
SkyBox::SkyBox(GraphicComponent* gfx, ShaderComponent* Shader, TextureComponent* Tex, XMFLOAT4X4 world)
{
	_gfx = gfx;
	_Tex = Tex;
	_Shader = Shader;
	_World = world;

	OBJLoader::Load("sphere.obj", _gfx->_pd3dDevice);

	_Shader = new ShaderComponent();
	_Shader->CreateVertexShader(_gfx);
	_Shader->CreatePixelShader(_gfx);


}
void SkyBox::Draw()
{

	_gfx->UpdateConstantBuffer(_World);
	SwitchDrawBuffers(_mesh.VertexBuffer, _mesh.IndexBuffer, _gfx);

	_Shader->ComposeShader(_gfx);
	_Tex->BindTextures(0, _Textures.size(), _Textures, _gfx);
	_gfx->_pImmediateContext->DrawIndexed(_mesh.IndexCount, 0, 0);
}
void SkyBox::UpdateSkybox()
{



}
void SkyBox::CreateTexture(wchar_t* path)
{
	ID3D11ShaderResourceView* texture;
	_Tex->CreateTexture(path, &texture, _gfx);
	_Textures.push_back(texture);
}
void SkyBox::SwitchDrawBuffers(ID3D11Buffer* VB, ID3D11Buffer* IB, GraphicComponent* _gfx)
{
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	_gfx->_pImmediateContext->IASetVertexBuffers(0, 1, &VB, &stride, &offset);
	_gfx->_pImmediateContext->IASetIndexBuffer(IB, DXGI_FORMAT_R16_UINT, 0);
}
