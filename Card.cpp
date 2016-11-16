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
	m_cardID = id;

	//Setting card position
	//m_cardPos.x = posX;
	//m_cardPos.y = posY;

	////Setting card rectangle
	//::SetRect(&m_cardRect, posX, posY, posX+width, posY+height);

	//Assign card textures
	if (!pFrontFace)
		return -1;
	m_pFrontFace = pFrontFace;

	if (!pBackFace)
		return -1;
	m_pBackFace = pBackFace;

	//Initialy, all cards ard flipped(showing backface)
	isFlipped = TRUE;
	isfound = FALSE;

	//fix
	vertices[0].pos = D3DXVECTOR3{posX, posY, 0.0f};
	vertices[1].pos = D3DXVECTOR3{posX+CARD_WIDTH, posY, 0.0f};
	vertices[2].pos = D3DXVECTOR3{posX, posY-CARD_HEIGHT, 0.0f};
	vertices[3].pos = D3DXVECTOR3{posX+CARD_WIDTH, posY-CARD_HEIGHT, 0.0f};

	vertices[0].color = D3DCOLOR_XRGB(255, 255, 255);
	vertices[1].color = D3DCOLOR_XRGB(255, 255, 255);
	vertices[2].color = D3DCOLOR_XRGB(255, 255, 255);
	vertices[3].color = D3DCOLOR_XRGB(255, 255, 255);

	vertices[0].u = 0; vertices[0].v = 0;
	vertices[1].u = 1; vertices[1].v = 0;
	vertices[2].u = 0; vertices[2].v = 1;
	vertices[3].u = 1; vertices[3].v = 1;

	return 0;
}

int CCard::Render()
{	
	//if (!m_pFrontFace || !m_pBackFace)
	//	return -1;
	//
	//RECT rc = m_pFrontFace->GetImageRect();
	//if (!isFlipped)
	//	GSPRITE->Draw(m_pFrontFace->GetTexture(), &rc, nullptr, 0, &m_cardPos, nullptr, D3DXCOLOR(1, 1, 1, 1));
	//else
	//	GSPRITE->Draw(m_pBackFace->GetTexture(), &rc, nullptr, 0, &m_cardPos, nullptr, D3DXCOLOR(1, 1, 1, 1));
	GDEVICE->SetTexture(0, m_pFrontFace->GetTexture());
	//fix : nullptr È®ÀÎ
	GDEVICE->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,		//PrimitiveType
		2,												//PrimitiveCount
		vertices,										//*pVertexStreamZeroData
		sizeof(CUSTOMVERTEX));							//VertexStreamZeroStride	
	GDEVICE->SetTexture(0, NULL);

	return 0;
}

void CCard::Destroy()
{
	m_pFrontFace = nullptr;
	m_pBackFace = nullptr;
}

//RECT CCard::GetCardRect() const
//{
//	return m_cardRect;
//}

BOOL CCard::Equals(const CCard * pCard) const
{
	if (pCard)
	{
		return (this->m_cardID == pCard->m_cardID);
	}
	return FALSE;
}
