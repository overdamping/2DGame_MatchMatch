#pragma once

struct CUSTOMVERTEX
{
	D3DXVECTOR3 pos;
	DWORD color;
	float u, v;
};
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

struct Ray
{
	D3DXVECTOR3 _origin;
	D3DXVECTOR3 _direction;
};

#define SAFE_RELEASE(p)		{if (p) {p->Release(); p = nullptr;}}
#define SAFE_DELEETE(p)		{if (p) {delete(p);  p = nullptr;}}