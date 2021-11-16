#include "Application.h"
/*
        Windows based aplications are always event drive to the core , waiting for messages(events) to be passed into message queue

*/
HRESULT Application::Initialise(HINSTANCE hInstance, int nCmdShow)
{
    gfx = new GraphicComponents();
    gfx->Initialise(hInstance , nCmdShow);
    sfx = new ShaderComponent();


    return S_OK;
}

//Class Constructor - Initalizing all default values.
Application::Application()
{


}

//Class Destructor - Calls cleanup , releases values.
Application::~Application()
{
 
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
    hr = gfx->_pPD3Ddevice->CreateBuffer(&Cubebufferdescription, &InitCubeData, &_pCubeVertexBuffer);
    hr = gfx->_pPD3Ddevice->CreateBuffer(&Pyrmidbufferdescription, &InitTriangleData, &_pTriangleVertexBuffer);
    hr = gfx->_pPD3Ddevice->CreateBuffer(&Gridbufferdescription, &InitGridData, &_pGridVertexBuffer);
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
    hr = gfx->_pPD3Ddevice->CreateBuffer(&Pyramidbufferdescription, &InitTriangleData, &_pTriangleIndexBuffer);
    hr = gfx->_pPD3Ddevice->CreateBuffer(&Cubebufferdescription, &InitCubeData, &_pCubeIndexBuffer);
    hr = gfx->_pPD3Ddevice->CreateBuffer(&Gridbufferdescription, &GridCubeData, &_pGridIndexBuffer);
    if (FAILED(hr))
        return hr;

    return S_OK;
}






HRESULT Application::Update()
{

    HRESULT hr = S_OK;


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



   
    //Sun
    XMStoreFloat4x4(&_world, XMMatrixRotationY(t) * XMMatrixTranslation(0.0f, 0.0f, 0.0f));
/*    //Planets
    XMStoreFloat4x4(&_world2, XMMatrixTranslation(0.0f, 0.0f, 0.0f));
   XMStoreFloat4x4(&_world4, XMMatrixScaling(0.75f, 0.75f, 0.75f) * XMMatrixRotationX(t) * XMMatrixTranslation(0.0f, 1.2f + cos(t) * 5, 0.0f + sin(t) * 5));
    //Moons
   XMStoreFloat4x4(&_world3, XMMatrixScaling(0.25f, 0.25f, 0.25f) * XMMatrixTranslation(-1.2f - cos(t) * 5, 0.0f - sin(t) * 5, 0.0f));
   XMStoreFloat4x4(&_world5, XMMatrixTranslation(0.0f, -2.0f, -1.0f));
  
    XMStoreFloat4x4(&objTestWorld, XMMatrixRotationY(t) * XMMatrixTranslation(4.0f, 0.0f, 0.0f));
    */
    if (GetAsyncKeyState(VK_DOWN))
    {
        gfx->SwitchWireFrame();
    }
    else if (GetAsyncKeyState(VK_UP))
    {
        gfx->SwitchSolid();

    }


    return S_OK;
}

void Application::Draw()
{
    XMMATRIX world = XMLoadFloat4x4(&_world);
    XMMATRIX view = XMLoadFloat4x4(&_view);
    XMMATRIX projection = XMLoadFloat4x4(&_projection);
    gfx->InitialiseLigthing();
    sfx->InitialiseShader(gfx->_pVertexShader , gfx->_pPixelShader , gfx->_pConstantBuffer);
    gfx->UpdateBuffer();



    //_pImmediateContext->PSSetShaderResources(0, 1, &_pTextureRV);
    gfx->_pImmediateContext->DrawIndexed(36, 0, 0);

 
    gfx->SwitchIndex_VertexBuffer(_pTriangleVertexBuffer, _pTriangleIndexBuffer);



}