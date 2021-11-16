#pragma once
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include "resource.h"

#include "DDSTextureLoader.h"
#include "ShaderComponent.h"
#include "VertexStruct.h"
#include "MeshStruct.h"
#include "ConstantStruct.h"
#include "OBJLoader.h"

class GraphicComponents;
class TextureComponent
{
public:
	void SetTexture(int StartSlot, int count, std::vector<ID3D11ShaderResourceView*> ObjectTextures);
	void ClearTexture();
	void InitialiseSampler();
	GraphicComponents* gfx;

	ID3D11SamplerState* _pSamplerLinear = nullptr;
	ID3D11ShaderResourceView* _pTextureRV = nullptr;

private:

};

