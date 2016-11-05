//-----------------------------------------------------------------------------
//Interface of the CGameTexture class
//-----------------------------------------------------------------------------
#pragma once

class CGameTexture
{
public:
	CGameTexture();
	~CGameTexture();

	int Create(LPDIRECT3DDEVICE9 pDev, const char* sFile);
	void Destroy();
public:
	int GetImageWidth() const;
	int GetImageHeight() const;
	RECT GetImageRect();
	LPDIRECT3DTEXTURE9 GetTexture();

private:
	D3DXIMAGE_INFO			m_Img;
	LPDIRECT3DTEXTURE9		m_pTx;
};


