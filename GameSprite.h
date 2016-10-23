//-----------------------------------------------------------------------------
//Interface of the CGameSprite class
//-----------------------------------------------------------------------------
#pragma once

class CGameSprite
{
public:
	CGameSprite();
	~CGameSprite();

	int Create(LPD3DXSPRITE pDxsprite);
	int Draw(LPDIRECT3DTEXTURE9 pTex, const RECT* pSrcRc, const D3DXVECTOR2 * pCenter, float angle, const D3DXVECTOR2 * pPos, const D3DXVECTOR2 * pScaling, D3DCOLOR Color);

private:
	LPD3DXSPRITE m_pDXSprite;
};

