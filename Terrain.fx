//--------------------------------------------------------------------------------------
// File: DX11 Framework.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);
//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register(b0)
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
	float gTime;
}

struct VS_INPUT
{
	
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
	
	
};

struct PS_INPUT
{
	float3 normalW : NORMAL;
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
	
};
//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float3 normalW : NORMAL;
	float3 PosW : POSITION;
	float2 Tex : TEXCOORD0;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(float4 Pos : POSITION, float3 NormalL : NORMAL, float2 Tex : TEXCOORD0)
{
	VS_OUTPUT output = (VS_OUTPUT) 0;

	output.Pos = mul(Pos, World);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);
		
	output.PosW = mul(Pos, World);
	
	Pos.xy += 0.5f * sin(Pos.x) * sin(3.0f * gTime);
	Pos.z *= 0.6f + 0.4f * sin(2.0f * gTime);
	
		// Convert from local space to world space
    // W component of vector is 0 as vectors cannot be translated
	float3 normalW = mul(float4(NormalL, 0.0f), World).xyz;
	normalW = normalize(normalW);
	output.Tex = Tex;
	return output;
}



//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------

float4 PS(VS_OUTPUT input) : SV_Target
{
	
	float3 toEye = normalize(EyePosW - input.PosW.xyz);
	float3 r = reflect(-LightVecW, input.normalW);
	float specularAmount = pow(max(dot(r, toEye), 0.0f), SpecularPower);
	float3 ambient = AmbientMtrl * AmbientLight;
	float diffuseAmount = max(dot(LightVecW, input.normalW), 0.0f);
	float3 specular = specularAmount * (SpecularMtrl * SpecularLight).rgb;
	float4 Color;
	

	Color.rgb = diffuseAmount * (DiffuseMtrl * DiffuseLight).rgb;
	Color.rgb = Color.rgb + ambient + specular;
	Color.a = DiffuseMtrl.a;
		
	float4 textureColor = txDiffuse.Sample(samLinear, input.Tex);
	return textureColor * Color;

		
}

