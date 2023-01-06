struct VertexOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VertexOut main(float2 pos : POSITION, float3 col : COLOR)
{
	VertexOut output;

	output.position = float4(pos.x, pos.y, 0.f, 1.f);
	output.color = float4(col.x, col.y, col.z, 1.f);

	return output;
}
