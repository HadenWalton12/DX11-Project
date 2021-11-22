#pragma once
#include "ObjectComponent.h"

class Star : public GameObjects
{
public:
	Star::Star(GraphicComponent* gfx , ShaderComponent* _Shader , TextureComponent* _Tex) : GameObjects(gfx, "Star.obj") {}
	
	void Update(GraphicComponent* gfx) override 
	{

        // Update our time
        static float t = 5.0f;


        if (gfx->_driverType == D3D_DRIVER_TYPE_REFERENCE)
        {
            t += (float)XM_PI * 0.0125f;
        }
        else
        {
            static DWORD dwTimeStart = 0;
            DWORD dwTimeCur = GetTickCount();

            if (dwTimeStart == 0)
                dwTimeStart = dwTimeCur;

            t = (dwTimeCur - dwTimeStart) / 1000.0f;
        }

        gfx->UpdateConstantBuffer();
        
        XMStoreFloat4x4(&gfx->_world, XMMatrixRotationY(t) * XMMatrixTranslation(0.0f, 0.0f, 0.0f));
	}
};