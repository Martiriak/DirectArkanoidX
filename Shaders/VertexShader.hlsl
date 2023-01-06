struct VertexOut
{
	float4 position : SV_Position;
	float4 color : Color;
};

VertexOut main(float2 pos : Position, float3 col : Color)
{
	VertexOut output;

	output.position = float4(pos.x, pos.y, 0.f, 1.f);
	output.color = float4(col.x, col.y, col.z, 1.f);

	return output;
}
