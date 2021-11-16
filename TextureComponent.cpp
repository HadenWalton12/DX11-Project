#include "TextureComponent.h"
#include "GraphicComponents.h"

void TextureComponent::SetTexture(int StartSlot, int count, std::vector<ID3D11ShaderResourceView*> ObjectTextures)
{
    gfx->_pImmediateContext->PSGetShaderResources(StartSlot , count , &ObjectTextures[0]);
}

void TextureComponent::ClearTexture()
{
    gfx->_pImmediateContext->PSSetShaderResources(0, 0, nullptr);
}

void TextureComponent::InitialiseSampler()
{
    // Create the sample state
    D3D11_SAMPLER_DESC SamplerDescription;

    ZeroMemory(&SamplerDescription, sizeof(SamplerDescription));

    SamplerDescription.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    SamplerDescription.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    SamplerDescription.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    SamplerDescription.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    SamplerDescription.ComparisonFunc = D3D11_COMPARISON_NEVER;
    SamplerDescription.MinLOD = 0;
    SamplerDescription.MaxLOD = D3D11_FLOAT32_MAX;

    gfx->_pPD3Ddevice->CreateSamplerState(&SamplerDescription, &_pSamplerLinear);
}