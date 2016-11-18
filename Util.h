#pragma once

struct CUSTOMVERTEX
{
	D3DXVECTOR3 _pos;
	DWORD _color;
	float _u, _v;
};
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

struct Ray
{
	D3DXVECTOR3 _origin;
	D3DXVECTOR3 _direction;
};

struct TexQuad	//textured quad built from two triangles
{	
	TexQuad() 
	{
		for(int i=0; i<4; i++)
			vertices[i]._color = D3DCOLOR_XRGB(255, 255, 255);

		vertices[0]._u = 0; vertices[0]._v = 0;
		vertices[1]._u = 1; vertices[1]._v = 0;
		vertices[2]._u = 0; vertices[2]._v = 1;
		vertices[3]._u = 1; vertices[3]._v = 1;
	}
	CUSTOMVERTEX vertices [4];
};

#define SAFE_RELEASE(p)		{if (p) {p->Release(); p = nullptr;}}
#define SAFE_DELEETE(p)		{if (p) {delete(p);  p = nullptr;}}

Ray CalcPickingRay(int screen_x, int screen_y);
bool RayQuadIntersectionTest(Ray r,const CUSTOMVERTEX* quadVertices);