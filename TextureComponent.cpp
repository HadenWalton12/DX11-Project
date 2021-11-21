#include "TextureComponent.h"


TextureComponent::TextureComponent()
{

}

HRESULT TextureComponent::CreateTexture(wchar_t* filepath, ID3D11ShaderResourceView** texture , GraphicComponent* gfx)
{
    return CreateDDSTextureFromFile(gfx->GetDevice(), filepath, nullptr, texture);
}

void TextureComponent::BindTextures(int startSlot, int count, std::vector<ID3D11ShaderResourceView*> textures , GraphicComponent* gfx)
{
    gfx->_pImmediateContext->PSSetShaderResources(startSlot, count, &textures[0]);
}

void TextureComponent::ClearTexture(GraphicComponent* gfx)
{
    gfx->_pImmediateContext->PSSetShaderResources(0, 0, nullptr);
}