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

struct TexQuad
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

struct Button
{
	Button() {}
	Button(int left, int top, int width, int height, 
		float x, float y)
	{
		::SetRect(&_srcRect, left, top, left + width, top + height);
		::SetRect(&_btnRect, x, y, x + height, y + height);
		_pos.x = x; _pos.y = y;
	}
	RECT _srcRect;
	RECT _btnRect;
	D3DXVECTOR2 _pos;
};

struct Panel
{
	Panel() {}
	Panel(int left, int top, int width, int height,
		float x, float y)
	{
		::SetRect(&_srcRect, left, top, left + width, top + height);
		_pos.x = x; _pos.y = y;
	}
	RECT _srcRect;
	D3DXVECTOR2 _pos;
};

#define SAFE_RELEASE(p)		{if (p) {p->Release(); p = nullptr;}}
#define SAFE_DELEETE(p)		{if (p) {delete(p);  p = nullptr;}}
#define SAFE_UPDATE(p)															\
{																				\
	if(p)																		\
	{																			\
		if(FAILED((p)->Update()))												\
			return -1;															\
	}																			\
}

#define SAFE_INIT(p, CLASSTYPE)													\
{																				\
	if((p) == nullptr)															\
	{																			\
		p = new CLASSTYPE;														\
		if(FAILED((p)->Init()))													\
		{																		\
			delete p;															\
			p = nullptr;														\
			return -1;															\
		}																		\
	}																			\
}

//functions for mouse picking
Ray CalcPickingRay(int screen_x, int screen_y);
BOOL RayQuadIntersectionTest(Ray r,const CUSTOMVERTEX* quadVertices);