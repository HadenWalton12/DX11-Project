#pragma once
#include "SimpleVertexStructure.h"
class Cube
{
public:

    SimpleVertex CubeStruct =
    {     // Vertex/Point Desc        //Colour decsription for point
        { XMFLOAT3(1.0f ,1.0f,-1.0f), XMFLOAT3(0.333333f, 0.666667f , -0.666667f) , XMFLOAT2(0.0f , 0.1f)},    // 0
        { XMFLOAT3(1.0f,-1.0f,-1.0f)  , XMFLOAT3(-0.816497f, 0.408248f, -0.408248f) ,  XMFLOAT2(1.0f , 1.0f)},      // 1 
        { XMFLOAT3(-1.0f,1.0f,1.0f), XMFLOAT3(-0.333333f, 0.666667f, 0.666667f), XMFLOAT2(0.0f , 1.0f)}, // 2 
        { XMFLOAT3(1.0f,1.0f,1.0f) , XMFLOAT3(0.816497f, 0.408248f, 0.408248f), XMFLOAT2(1.0f , 1.0f)},      // 3
        { XMFLOAT3(1.0f,-1.0f,-1.0f), XMFLOAT3(0.666667f, -0.666667f, -0.333333f), XMFLOAT2(0.0f , 0.0f)},    // 4
        { XMFLOAT3(-1.0f,-1.0f,-1.0f) , XMFLOAT3(-0.408248f, -0.408248f, -0.816497f), XMFLOAT2(1.0f , 0.0f)},     // 5 
        { XMFLOAT3(-1.0f,-1.0f,1.0f)  , XMFLOAT3(-0.666667f, -0.666667f, 0.333333f), XMFLOAT2(0.0f , 0.0f)},    // 6
        { XMFLOAT3(1.0f, -1.0f,1.0f), XMFLOAT3(0.408248f, -0.408248f, 0.816497f), XMFLOAT2(1.0f , 0.0f)},  // 7
    };
private:


};

