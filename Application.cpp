#include "Application.h"
/*
        Windows based aplications are always event drive to the core , waiting for messages(events) to be passed into message queue

*/

//Class Constructor - Initalizing all default values.
Application::Application()
{
    _hInst = nullptr;
    _hWnd = nullptr;
    _driverType = D3D_DRIVER_TYPE_NULL;
    _featureLevel = D3D_FEATURE_LEVEL_11_0;
    _pd3dDevice = nullptr;
    _pd3dDevice = nullptr;
    _pImmediateContext = nullptr;
    _pSwapChain = nullptr;
    _pRenderTargetView = nullptr;
    _pVertexShader = nullptr;
    _pPixelShader = nullptr;
    _pVertexLayout = nullptr;
    _pTriangleVertexBuffer = nullptr;
    _pTriangleIndexBuffer = nullptr;
    _pConstantBuffer = nullptr;

}

//Class Destructor - Calls cleanup , releases values.
Application::~Application()
{
    Cleanup();
}

//Initalises Window Coordinates , Projection Matrix & View Matrix 
HRESULT Application::Initialise(HINSTANCE hInstance, int nCmdShow)
{
    _gfx = new GraphicComponent(); 


}

HRESULT Application::CreateShadersAndInputLayout()
{
    HRESULT hr;

    // Compile the vertex shader
    ID3DBlob* pVSBlob = nullptr;
    hr = CompileShaderFromFile(L"DX11 Framework.fx", "VS", "vs_4_0", &pVSBlob);

    //Check Error Method - Was the CompiledShaderFromFile Above correct?
    if (FAILED(hr))
    {
        MessageBox(nullptr, L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

    // Create the vertex shader
    hr = _pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &_pVertexShader);

    if (FAILED(hr))
    {
        pVSBlob->Release();
        return hr;
    }

    // Compile the pixel shader
    ID3DBlob* pPSBlob = nullptr;
    hr = CompileShaderFromFile(L"DX11 Framework.fx", "PS", "ps_4_0", &pPSBlob);

    //Check Error Method - Was the CompiledShaderFromFile Above correct?
    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

    // Create the pixel shader
    hr = _pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &_pPixelShader);
    pPSBlob->Release();

    if (FAILED(hr))
        return hr;

    // Define the input layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD" , 0 , DXGI_FORMAT_R32G32_FLOAT , 0 , 24 , D3D11_INPUT_PER_VERTEX_DATA , 0},

    };

    UINT numElements = ARRAYSIZE(layout);

    // Create the input layout
    hr = _pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(), &_pVertexLayout);
    pVSBlob->Release();

    if (FAILED(hr))
    {
        return hr;
    }
    // Determines the input layout - How our data will need to be presented to our program.
    _pImmediateContext->IASetInputLayout(_pVertexLayout);

    return hr;
}

//Describes Buffer Data, resources , then creates buffers with data local in this
HRESULT Application::CreateVertexBuffer()
{
    HRESULT hr;

    //Initalise Vertex Data to be stored in buffer

    SimpleVertex CubeStruct[] =
    {     // Vertex/Point Desc        //Colour decsription for point
        { XMFLOAT3(1.0f ,1.0f,-1.0f), XMFLOAT3(0.333333f, 0.666667f , -0.666667f) , XMFLOAT2(0.0f , 0.1f)},    // 0
        { XMFLOAT3(-1.0f,1.0f,-1.0f)  , XMFLOAT3(-0.816497f, 0.408248f, -0.408248f) ,  XMFLOAT2(1.0f , 1.0f)},      // 1 
        { XMFLOAT3(-1.0f,1.0f,1.0f), XMFLOAT3(-0.333333f, 0.666667f, 0.666667f), XMFLOAT2(0.0f , 1.0f)}, // 2 
        { XMFLOAT3(1.0f,1.0f,1.0f) , XMFLOAT3(0.816497f, 0.408248f, 0.408248f), XMFLOAT2(1.0f , 1.0f)},      // 3
        { XMFLOAT3(1.0f,-1.0f,-1.0f), XMFLOAT3(0.666667f, -0.666667f, -0.333333f), XMFLOAT2(0.0f , 0.0f)},    // 4
        { XMFLOAT3(-1.0f,-1.0f,-1.0f) , XMFLOAT3(-0.408248f, -0.408248f, -0.816497f), XMFLOAT2(1.0f , 0.0f)},     // 5 
        { XMFLOAT3(-1.0f,-1.0f,1.0f)  , XMFLOAT3(-0.666667f, -0.666667f, 0.333333f), XMFLOAT2(0.0f , 0.0f)},    // 6
        { XMFLOAT3(1.0f, -1.0f,1.0f), XMFLOAT3(0.408248f, -0.408248f, 0.816497f), XMFLOAT2(1.0f , 0.0f)},  // 7
    };
    SimpleVertex PyramidStruct[] =
    {
         { XMFLOAT3(0.0f , 0.0f , 2.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0.0f , 0.5f)},  //0 
         { XMFLOAT3(-1.0f, -1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0.0f , 0.0f)},  // 1
         { XMFLOAT3(1.0f, -1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0.0f , 0.0f)},  // 2
         { XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0.0f , 0.0f)},  // 3
         { XMFLOAT3(-1.0f, 1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0.0f , 0.0f)},// 4
    };
    SimpleVertex GridStruct[625] =
    {

    };


    for (int row = 0; row < 10; row++)
    {

        for (int col = 0; col < 5; col++)
        {
            int index = row * 5 + col;
            GridStruct[index] = { XMFLOAT3((float)col , 0.0f , (float)row), XMFLOAT3(0.0f , 0.0f ,0.0f) , XMFLOAT2((float)row ,(float)col) };

        }

    }
    //D3D11_BUFFER_DESC - Struct that allows us to describe a buffers resource

    //Pyramid Vertex Buffer Description
    D3D11_BUFFER_DESC Pyrmidbufferdescription;
    ZeroMemory(&Pyrmidbufferdescription, sizeof(Pyrmidbufferdescription));

    //Describing Trianlge Vertex Data 
    Pyrmidbufferdescription.Usage = D3D11_USAGE_DEFAULT;
    Pyrmidbufferdescription.ByteWidth = sizeof(SimpleVertex) * 8;//Size of data contained inside buffer
    Pyrmidbufferdescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    Pyrmidbufferdescription.CPUAccessFlags = 0;

    //Cube Vertex  Buffer Description
    D3D11_BUFFER_DESC Cubebufferdescription;
    ZeroMemory(&Cubebufferdescription, sizeof(Cubebufferdescription));

    Cubebufferdescription.Usage = D3D11_USAGE_DEFAULT;
    Cubebufferdescription.ByteWidth = sizeof(SimpleVertex) * 8;
    Cubebufferdescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    Cubebufferdescription.CPUAccessFlags = 0;

    //Cube Vertex  Buffer Description
    D3D11_BUFFER_DESC Gridbufferdescription;
    ZeroMemory(&Gridbufferdescription, sizeof(Gridbufferdescription));

    Gridbufferdescription.Usage = D3D11_USAGE_DEFAULT;
    Gridbufferdescription.ByteWidth = sizeof(SimpleVertex) * 25;
    Gridbufferdescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    Gridbufferdescription.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitGridData;
    ZeroMemory(&InitGridData, sizeof(InitGridData));
    InitGridData.pSysMem = GridStruct;

    //Specifies data being used - Used in the process of creating buffers , calls reference to relevant vertex struct (InitData variable equals PyramidStruct)
    D3D11_SUBRESOURCE_DATA InitTriangleData;
    ZeroMemory(&InitTriangleData, sizeof(InitTriangleData));
    InitTriangleData.pSysMem = PyramidStruct;

    //Specifies data being used - Used in the process of creating buffers , calls reference to relevant vertex struct (InitData variable equals CubeStruct)
    D3D11_SUBRESOURCE_DATA InitCubeData;
    ZeroMemory(&InitCubeData, sizeof(InitCubeData));
    InitCubeData.pSysMem = CubeStruct;

    // Call device pointer , pass "CreateBuffer" function , parameter pass in relevant local data above (describe data and buffer resource) , then reference Buffer pointer
    hr = _pd3dDevice->CreateBuffer(&Cubebufferdescription, &InitCubeData, &_pCubeVertexBuffer);
    hr = _pd3dDevice->CreateBuffer(&Pyrmidbufferdescription, &InitTriangleData, &_pTriangleVertexBuffer);
    hr = _pd3dDevice->CreateBuffer(&Gridbufferdescription, &InitGridData, &_pGridVertexBuffer);
    //Fail Check Method
    if (FAILED(hr))
    {
        return hr;
    }

    return S_OK;
}
//Describes Buffer Data , resources , then creates the buffers with data local in this
HRESULT Application::CreateIndexBuffer()
{
    HRESULT hr;

    //Initalse Index data, to bestored in index buffer
    WORD CubeIndex[] =
    {
        //Front
          0,1,2,
          0,2,3,

          0,4,5,
          0,5,1,

          1,5,1,
          1,6,2,

          2,6,7,
          2,7,3,

          3,7,4,
          3,4,0,

          4,7,6,
          4,6,5,

    };
    WORD TrianglePyramidIndex[] =
    {

     0,2,1,
     0,1,4,
     0,4,3,
     0,3,2,
     4,3,2,
     4,2,1,

    };

    const int width = 5;
    const int height = 5;

    WORD Grid[(width - 1) * (height - 1) * 6];
    int tri_index = 0;
    int vertex_index = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j < width - 1 && i < height - 1)
            {

                //Check Error Statement // Checks if points are less or higher than our unesscary values on grid
                Grid[tri_index] = vertex_index;
                Grid[tri_index + 1] = vertex_index + width + 1;
                Grid[tri_index + 2] = vertex_index + width;

                Grid[tri_index + 3] = vertex_index + width + 1;
                Grid[tri_index + 4] = vertex_index;
                Grid[tri_index + 5] = vertex_index + 1;


                tri_index += 6;
            }
            vertex_index++;
        }


    }
    //D3D11_BUFFER_DESC - Struct that allows us to describe a buffers resource

    //Pyramid Index Buffer Description
    D3D11_BUFFER_DESC Pyramidbufferdescription;
    ZeroMemory(&Pyramidbufferdescription, sizeof(Pyramidbufferdescription));

    Pyramidbufferdescription.Usage = D3D11_USAGE_DEFAULT;
    Pyramidbufferdescription.ByteWidth = sizeof(WORD) * 18;
    Pyramidbufferdescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
    Pyramidbufferdescription.CPUAccessFlags = 0;

    //Cube Index Buffer Description
    D3D11_BUFFER_DESC Cubebufferdescription;
    ZeroMemory(&Cubebufferdescription, sizeof(Cubebufferdescription));

    Cubebufferdescription.Usage = D3D11_USAGE_DEFAULT;
    Cubebufferdescription.ByteWidth = sizeof(WORD) * 36;
    Cubebufferdescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
    Cubebufferdescription.CPUAccessFlags = 0;

    //Cube Index Buffer Description
    D3D11_BUFFER_DESC Gridbufferdescription;
    ZeroMemory(&Gridbufferdescription, sizeof(Gridbufferdescription));

    Gridbufferdescription.Usage = D3D11_USAGE_DEFAULT;
    Gridbufferdescription.ByteWidth = sizeof(WORD) * 175;
    Gridbufferdescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
    Gridbufferdescription.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA GridCubeData;
    ZeroMemory(&GridCubeData, sizeof(GridCubeData));
    GridCubeData.pSysMem = Grid;

    //Specifies data being used - Used in the process of creating buffers , calls reference to relevant index struct (InitData variable equals TrianglePyramidIndex)
    D3D11_SUBRESOURCE_DATA InitTriangleData;
    ZeroMemory(&InitTriangleData, sizeof(InitTriangleData));
    InitTriangleData.pSysMem = TrianglePyramidIndex;

    //Specifies data being used - Used in the process of creating buffers , calls reference to relevant index struct (InitData variable equals CubeIndex)

    D3D11_SUBRESOURCE_DATA InitCubeData;
    ZeroMemory(&InitCubeData, sizeof(InitCubeData));
    InitCubeData.pSysMem = CubeIndex;


    // Call device pointer , pass "CreateBuffer" function , parameter pass in relevant local data above (describe data and buffer resource) , then reference Buffer pointer
    hr = _pd3dDevice->CreateBuffer(&Pyramidbufferdescription, &InitTriangleData, &_pTriangleIndexBuffer);
    hr = _pd3dDevice->CreateBuffer(&Cubebufferdescription, &InitCubeData, &_pCubeIndexBuffer);
    hr = _pd3dDevice->CreateBuffer(&Gridbufferdescription, &GridCubeData, &_pGridIndexBuffer);
    if (FAILED(hr))
        return hr;

    return S_OK;
}



HRESULT Application::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
        dwShaderFlags, 0, ppBlobOut, &pErrorBlob);

    if (FAILED(hr))
    {
        if (pErrorBlob != nullptr)
            OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());

        if (pErrorBlob) pErrorBlob->Release();

        return hr;
    }

    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}

HRESULT Application::CreateDevice()
{
}

void Application::Cleanup()
{
    if (_pImmediateContext) _pImmediateContext->ClearState();
    if (_pConstantBuffer) _pConstantBuffer->Release();
    if (_pCubeVertexBuffer) _pCubeVertexBuffer->Release();
    if (_pCubeIndexBuffer) _pCubeIndexBuffer->Release();
    if (_pTriangleVertexBuffer) _pTriangleVertexBuffer->Release();
    if (_pTriangleIndexBuffer) _pTriangleIndexBuffer->Release();
    if (_pVertexLayout) _pVertexLayout->Release();
    if (_pVertexShader) _pVertexShader->Release();
    if (_pPixelShader) _pPixelShader->Release();
    if (_pRenderTargetView) _pRenderTargetView->Release();
    if (_pSwapChain) _pSwapChain->Release();
    if (_pImmediateContext) _pImmediateContext->Release();
    if (_pd3dDevice) _pd3dDevice->Release();
    if (_pDepthStencilView) _pDepthStencilView->Release();
    if (_pDepthStencilBuffer) _pDepthStencilBuffer->Release();
    if (_wireFrame) _wireFrame->Release();
}

HRESULT Application::Update()
{

    HRESULT hr = S_OK;


    // Update our time
    static float t = 5.0f;


    if (_driverType == D3D_DRIVER_TYPE_REFERENCE)
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

    _gTime = t;

   
    //Sun
    XMStoreFloat4x4(&_world, XMMatrixRotationY(t) * XMMatrixTranslation(0.0f, 0.0f, 0.0f));
    //Planets
    XMStoreFloat4x4(&_world2, XMMatrixTranslation(0.0f, 0.0f, 0.0f));
   XMStoreFloat4x4(&_world4, XMMatrixScaling(0.75f, 0.75f, 0.75f) * XMMatrixRotationX(t) * XMMatrixTranslation(0.0f, 1.2f + cos(t) * 5, 0.0f + sin(t) * 5));
    //Moons
   XMStoreFloat4x4(&_world3, XMMatrixScaling(0.25f, 0.25f, 0.25f) * XMMatrixTranslation(-1.2f - cos(t) * 5, 0.0f - sin(t) * 5, 0.0f));
   XMStoreFloat4x4(&_world5, XMMatrixTranslation(0.0f, -2.0f, -1.0f));
  
    XMStoreFloat4x4(&objTestWorld, XMMatrixRotationY(t) * XMMatrixTranslation(4.0f, 0.0f, 0.0f));
    D3D11_RASTERIZER_DESC rastDesc;

    if (GetAsyncKeyState(VK_DOWN))
    {
        //Changes rasterizer stage (how we visually convert world to 2D texels) to fill mode, showing full normal object
        ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC));
        rastDesc.FillMode = D3D11_FILL_SOLID;
        rastDesc.CullMode = D3D11_CULL_NONE;
        hr = _pd3dDevice->CreateRasterizerState(&rastDesc, &_wireFrame);
    }
    else if (GetAsyncKeyState(VK_UP))
    {
        //Changes rasterizer state to wireframe mode
        ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC));
        rastDesc.FillMode = D3D11_FILL_WIREFRAME;
        rastDesc.CullMode = D3D11_CULL_NONE;
        hr = _pd3dDevice->CreateRasterizerState(&rastDesc, &_wireFrame);

    }
    _pImmediateContext->RSSetState(_wireFrame);

    return S_OK;
}

void Application::Draw()
{


    // Set vertex buffer  passed into input assembly stage
    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;
    float ClearColor[4] = { 0.0f, 1.0f, 0.0f, 0.0f }; // red,green,blue,alpha
    //Clears RenderView , current buffer, used for swap chain
    _pImmediateContext->ClearRenderTargetView(_pRenderTargetView, ClearColor);
    //Clears current depthview , also used to update depth from next buffer in swapchain
    _pImmediateContext->ClearDepthStencilView(_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0); //for the float value :Clear the depth buffer with this value. This value will be clamped between 0 and 1.
   
  
    _pImmediateContext->PSSetSamplers(0, 1, &_pSamplerLinear);
    
    XMMATRIX world = XMLoadFloat4x4(&_world);
    XMMATRIX view = XMLoadFloat4x4(&_view);
    XMMATRIX projection = XMLoadFloat4x4(&_projection);













    _pImmediateContext->PSSetShaderResources(0, 1, &_pTextureRV);
    _pImmediateContext->DrawIndexed(36, 0, 0);

    
    _pImmediateContext->IASetVertexBuffers(0, 1, &_pTriangleVertexBuffer, &stride, &offset);
    _pImmediateContext->IASetIndexBuffer(_pTriangleIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

    world = XMLoadFloat4x4(&_world2);
    constantbuffer.mWorld = XMMatrixTranspose(world);
    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuffer, 0, 0);
    _pImmediateContext->DrawIndexed(18, 0, 0);

 
    world = XMLoadFloat4x4(&_world3);
    constantbuffer.mWorld = XMMatrixTranspose(world);
    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuffer, 0, 0);
    _pImmediateContext->DrawIndexed(18, 0, 0);

 
    world = XMLoadFloat4x4(&_world4);
    constantbuffer.mWorld = XMMatrixTranspose(world);
    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuffer, 0, 0);
    _pImmediateContext->DrawIndexed(18, 0, 0);
   

    _pImmediateContext->IASetVertexBuffers(0, 1, &_pGridVertexBuffer, &stride, &offset);
    _pImmediateContext->IASetIndexBuffer(_pGridIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

    world = XMLoadFloat4x4(&_world5);
    constantbuffer.mWorld = XMMatrixTranspose(world);
    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuffer, 0, 0);
    _pImmediateContext->DrawIndexed(150, 0, 0);
    

    _pImmediateContext->IASetVertexBuffers(0, 1, &objStarMeshData.VertexBuffer, &objStarMeshData.VBStride, &objStarMeshData.VBOffset);
    _pImmediateContext->IASetIndexBuffer(objStarMeshData.IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
    world = XMLoadFloat4x4(&objTestWorld);
    constantbuffer.mWorld = XMMatrixTranspose(world);
    _pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &constantbuffer, 0, 0);
    _pImmediateContext->DrawIndexed(objStarMeshData.IndexCount, 0, 0);


}