#include "ObjectComponent.h"

GameObjects::GameObjects(ID3D11Device* device, ID3D11DeviceContext* device_context, MeshData mesh, ID3D11VertexShader* VS, ID3D11PixelShader* PS, ID3D11Buffer* CB, XMFLOAT4X4 world, char* file, ID3D11ShaderResourceView* texture)
: _pDevice(device), _pDeviceContext(device_context), _Mesh(mesh), _pVertexShader(VS), _pPixelShader(PS), _pConstantBuffer(CB), _World(world), File(file), _Texture(texture)
{

	





}

void Update()
{



}
void Draw()
{



}

