//-----------------------------------------------------------------------------
//Implementation of the CGameSprite class
//-----------------------------------------------------------------------------
#pragma once
#include "StdAfx.h"

CGameSprite::CGameSprite() : m_pDXSprite(nullptr)
{
}


CGameSprite::~CGameSprite()
{
	m_pDXSprite = nullptr;
}

int CGameSprite::Create(LPD3DXSPRITE pDxsprite)
{
	if (!pDxsprite)
		return -1;
	else
	{
		m_pDXSprite = pDxsprite;
		return 0;
	}
}

int CGameSprite::Draw(LPDIRECT3DTEXTURE9 pTex, const RECT * pSrcRc, const D3DXVECTOR2 * pCenter, float angle, const D3DXVECTOR2 * pPos, const D3DXVECTOR2 * pScaling, D3DCOLOR Color)
{
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);

	D3DXMATRIX mtRot, mtCenterI, mtCenter, mtTrans, mtScal;
	D3DXMatrixIdentity(&mtRot);
	D3DXMatrixIdentity(&mtCenterI);
	D3DXMatrixIdentity(&mtCenter);
	D3DXMatrixIdentity(&mtTrans);
	D3DXMatrixIdentity(&mtScal);

	m_pDXSprite->Begin(D3DXSPRITE_ALPHABLEND);

	if (pScaling)		//Scaling
		D3DXMatrixScaling(&mtScal, pScaling->x, pScaling->y, 1);

	if (pCenter)		//Rotation
	{
		float fTheta = D3DXToRadian(angle);
		D3DXMatrixRotationZ(&mtRot, -1* fTheta);
		D3DXMatrixTranslation(&mtCenter, pCenter->x, pCenter->y, 0);
		D3DXMatrixInverse(&mtCenterI, NULL, &mtCenter);
	}

	if (pPos)		//Translation
		D3DXMatrixTranslation(&mtTrans, pPos->x, pPos->y, 0);

	mt = mtScal * mtCenterI * mtRot * mtCenter * mtTrans;
	
	m_pDXSprite->SetTransform(&mt);
	m_pDXSprite->Draw(pTex, pSrcRc, NULL, NULL, Color);

	D3DXMatrixIdentity(&mt);
	m_pDXSprite->SetTransform(&mt);

	m_pDXSprite->End();

	return 0;
}
