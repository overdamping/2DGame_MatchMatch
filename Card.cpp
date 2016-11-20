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
	//setting card ID
	m_cardID = id;
	
	//assign card textures
	if (!pFrontFace || !pBackFace)
		return -1;
	m_pFrontFace = pFrontFace;
	m_pBackFace = pBackFace;

	//setting card position
	card.vertices[0]._pos = D3DXVECTOR3{posX, posY, 0.0f};
	card.vertices[1]._pos = D3DXVECTOR3{posX+CARD_WIDTH, posY, 0.0f};
	card.vertices[2]._pos = D3DXVECTOR3{posX, posY-CARD_HEIGHT, 0.0f};
	card.vertices[3]._pos = D3DXVECTOR3{posX+CARD_WIDTH, posY-CARD_HEIGHT, 0.0f};

	m_cardSt = NOTFOUND_BACK;

	return 0;
}

int CCard::Render()
{	
	if (!m_pFrontFace || !m_pBackFace)
		return -1;

	if (m_cardSt == NOTFOUND_BACK)
		GDEVICE->SetTexture(0, m_pBackFace->GetTexture());
	else
		GDEVICE->SetTexture(0, m_pFrontFace->GetTexture());

	GDEVICE->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,		//primitive type
		2,												//number of primitives to render
		card.vertices,									//user memory pointer to vertex data
		sizeof(CUSTOMVERTEX));							//the number of bytes of data for each vertex	

	GDEVICE->SetTexture(0, NULL);
	return 0;
}

void CCard::Destroy()
{
	m_pFrontFace = nullptr;
	m_pBackFace = nullptr;
}

BOOL CCard::Equals(const CCard * pCard) const
{
	if (pCard)
	{
		return (this->m_cardID == pCard->m_cardID);
	}
	return FALSE;
}

BOOL CCard::IsFound() const
{
	return (m_cardSt == FOUND_FRONT);
}

void CCard::Flip(BOOL st)
{
	if (m_cardSt != FOUND_FRONT)
	{
		if (st)
			m_cardSt = NOTFOUND_BACK;
		else
			m_cardSt = NOTFOUND_FRONT;
	}
}

void CCard::Found()
{
	m_cardSt = FOUND_FRONT;
}

const CUSTOMVERTEX * CCard::GetQuadVertices()
{
	return card.vertices;
}
