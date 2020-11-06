#include "00_Global.fx"
#include "00_Light.fx"

cbuffer CB_Rain
{
    float4 Color;

    float3 Velocity;
    float DrawDistance;

    float3 Origin;
    float CB_Rain_Padding;

    float3 Extent;
};

struct VertexInput
{
    float4 Position : Position0;
    float2 Uv : Uv0;
    float2 Scale : Scale0;
};

struct VertexOutput
{
    float4 Position : Position0;
    float2 Uv : Uv0;
    float Alpha : Alpha0;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;

    float3 displace = Velocity;
    displace.xz /= input.Scale.y * 0.1f;
    displace = Time * displace;

    input.Position.xyz = Origin + (Extent + (input.Position.xyz + displace) % Extent) % Extent - (Extent * 0.5f);

    float4 wPosition = WorldPosition(input.Position);

    float3 up = normalize(Velocity);
    float3 forward = wPosition.xyz - ViewPosition();
    float3 right = normalize(cross(up, forward));

    wPosition.xyz += (input.Uv.x - 0.5f) * right * input.Scale.x;
    wPosition.xyz += (1 - input.Uv.y - 0.5f) * up * input.Scale.y;
    wPosition.w = 1.0;

    output.Position = ViewProjection(wPosition);
    output.Uv = input.Uv;

    float4 view = mul(wPosition, View);

    output.Alpha = saturate(1 - view.z / DrawDistance) * 0.5f;

    return output;
}

float4 PS(VertexOutput input) : SV_Target0
{
    float4 color = DiffuseMap.Sample(LinearSampler, input.Uv);

    color.rgb = color.rgb * input.Alpha * 2.0f;
    color.a = color.a * (input.Alpha * 1.5f);

    return color;
}

technique11 T0
{
    P_BS_VP(P0, AlphaBlend_AlphaToCoverage, VS, PS)
}