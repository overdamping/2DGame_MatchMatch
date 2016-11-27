//-----------------------------------------------------------------------------
//Implementation of the CGameTexture class
//-----------------------------------------------------------------------------
#pragma once
#include "StdAfx.h"

CGameTexture::CGameTexture()
{
	m_pTx = nullptr;
	memset(&m_Img, 0, sizeof(m_Img));
}

int CGameTexture::Create(LPDIRECT3DDEVICE9 pDev, const char* sFile)
{	
	if(FAILED(D3DXCreateTextureFromFileEx(
		pDev,								//Device pointer
		sFile,								//texture file name
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		1,									//Mip level
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		0x0000001,							//Filtering
		0x0000001,							//Mip filtering
		0x00FFFFFF,							//Color key
		&m_Img,								//texture Information
		NULL,
		&m_pTx								//texture Pointer
		)))		
	{
		MessageBox(GetActiveWindow(), "Can not find texture file", "Err", 0);
		m_pTx = nullptr;
		return -1;
	}

	return 0;
}

void CGameTexture::Destroy()
{
	SAFE_RELEASE(m_pTx);
}

int CGameTexture::GetImageWidth() const
{
	return m_Img.Width;
}

int CGameTexture::GetImageHeight() const
{
	return m_Img.Height;
}

RECT CGameTexture::GetImageRect()
{
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = m_Img.Width;
	rc.bottom = m_Img.Height;

	return rc;
}

LPDIRECT3DTEXTURE9 CGameTexture::GetTexture()
{
	return m_pTx;
}

CGameTexture::~CGameTexture(void)
{
	Destroy();
}
