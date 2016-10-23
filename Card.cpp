//-----------------------------------------------------------------------------
//Implementation of the CCard class
//-----------------------------------------------------------------------------
#pragma once
#include "Stdafx.h"

CCard::CCard() : m_pFrontFace(nullptr), m_pBackFace(nullptr)
{
}


CCard::~CCard()
{
	Destroy();
}

int CCard::Create(int id, float posX, float posY, CGameTexture* pFrontFace, CGameTexture* pBackFace)
{
	//Setting card ID
	cardID = id;

	//Setting card position
	m_cardPos.x = posX;
	m_cardPos.y = posY;

	//Assign card textures
	if (!pFrontFace)
		return -1;
	m_pFrontFace = pFrontFace;

	if (!pBackFace)
		return -1;
	m_pBackFace = pBackFace;

	//Initialy, all cards ard flipped(showing backface)
	isFlipped = TRUE;
	foundFlag = FALSE;

	return 0;
}

int CCard::Render()
{	
	if (!m_pFrontFace || !m_pBackFace)
		return -1;

	RECT rc = m_pFrontFace->GetImageRect();
	if (!isFlipped)
		GSPRITE->Draw(m_pFrontFace->GetTexture(), &rc, nullptr, 0, &m_cardPos, nullptr, D3DXCOLOR(1, 1, 1, 1));
	else
		GSPRITE->Draw(m_pBackFace->GetTexture(), &rc, nullptr, 0, &m_cardPos, nullptr, D3DXCOLOR(1, 1, 1, 1));

	return 0;
}

void CCard::Destroy()
{
	m_pFrontFace = nullptr;
	m_pBackFace = nullptr;
}

RECT CCard::GetCardRect()
{
	RECT rc = m_pFrontFace->GetImageRect();

	rc.left += m_cardPos.x;
	rc.right += m_cardPos.x;
	rc.top += m_cardPos.y;
	rc.bottom += m_cardPos.y;

	return rc;
}

void CCard::FlipCard()
{
	isFlipped = !isFlipped;
}

BOOL CCard::Equals(const CCard * pCard) const
{
	if (pCard)
	{
		return (this->cardID == pCard->cardID);
	}
	return FALSE;
}
