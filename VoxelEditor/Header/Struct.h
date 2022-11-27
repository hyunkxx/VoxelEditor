#pragma once

struct Rotation
{
	float x;
	float y;
	float z;
	
	Rotation(vec3 v) : x(v.x), y(v.y), z(v.z)
	{}
};

struct Ray
{
	vec3 dir;
	vec3 origin;
};

struct Vertex
{
	vec3 pos;
	D3DCOLOR color;
};
const uint32 FVF_TRI = D3DFVF_XYZ | D3DFVF_DIFFUSE;

struct Index32
{
	uint32 _0;
	uint32 _1;
	uint32 _2;
};
const uint32 FVF_CUBE = D3DFVF_XYZ | D3DFVF_DIFFUSE;

