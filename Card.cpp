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

	//Initialy, all cards ard flipped(showing backface)
	isFlipped = TRUE;
	isfound = FALSE;

	card.vertices[0]._pos = D3DXVECTOR3{posX, posY, 0.0f};
	card.vertices[1]._pos = D3DXVECTOR3{posX+CARD_WIDTH, posY, 0.0f};
	card.vertices[2]._pos = D3DXVECTOR3{posX, posY-CARD_HEIGHT, 0.0f};
	card.vertices[3]._pos = D3DXVECTOR3{posX+CARD_WIDTH, posY-CARD_HEIGHT, 0.0f};

	return 0;
}

int CCard::Render()
{	
	if (!m_pFrontFace || !m_pBackFace)
		return -1;

	if (!isFlipped)
		GDEVICE->SetTexture(0, m_pFrontFace->GetTexture());
	else
		GDEVICE->SetTexture(0, m_pBackFace->GetTexture());

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

const CUSTOMVERTEX * CCard::GetQuadVertices()
{
	return card.vertices;
}
