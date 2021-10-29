//--------------------------------------------------------------------------------------
// File: DX11 Framework.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register( b0 )
{
    matrix World;
    matrix View;
    matrix Projection;


    float4 DiffuseMtrl;
    float4 DiffuseLight;
    float4 AmbientMtrl;
    float4 AmbientLight;
	float4 SpecularMtrl;
	float4 SpecularLight;
	float SpecularPower;
    float3 LightVecW;
	float4 EyePosW;

}

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float3 normalW : NORMAL;
    float4 Color : COLOR0;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( float4 Pos : POSITION, float3 NormalL : NORMAL )
{
    VS_OUTPUT output = (VS_OUTPUT)0;

    output.Pos = mul(Pos, World);
    
	float3 toEye = normalize(EyePosW - output.Pos.xyz);
    
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);
    
    // Convert from local space to world space
    // W component of vector is 0 as vectors cannot be translated
    float3 normalW = mul(float4(NormalL, 0.0f), World).xyz;
    normalW = normalize(normalW);

	float3 r = reflect(-LightVecW, normalW);
	float specularAmount = pow(max(dot(r, toEye), 0.0f), SpecularPower);
    
    float3 ambient = AmbientMtrl * AmbientLight;
    float diffuseAmount = max(dot(LightVecW, normalW), 0.0f);
	float3 specular = specularAmount * (SpecularMtrl * SpecularLight).rgb;
    output.Color.rgb = diffuseAmount * (DiffuseMtrl * DiffuseLight).rgb;
	output.Color.rgb = output.Color.rgb + ambient + specular;
    output.Color.a = DiffuseMtrl.a;

    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( VS_OUTPUT input ) : SV_Target
{
    return input.Color;
}
