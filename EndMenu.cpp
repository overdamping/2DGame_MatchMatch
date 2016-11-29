//-----------------------------------------------------------------------------
//Implementation of the CEndMenu class
//-----------------------------------------------------------------------------
#include "StdAfx.h"

CEndMenu::CEndMenu(int finalScore)
{
	score = finalScore;
}


CEndMenu::~CEndMenu()
{
	Destroy();
}

int CEndMenu::Init()
{
	//UI texture creation
	if (FAILED(m_texUIpack.Create(GDEVICE, "texture/uipackSpace_sheet.png")))
		return -1;

	//button texture creation
	if (FAILED(m_texButtons.Create(GDEVICE, "texture/sheet_white2x.png")))
		return -1;

	//message creation
	m_strMsg = new char[80];
	char strbuf[80] = "축하합니다! 당신의 점수는 ";
	char scrBuf[20];
	_itoa_s(score, scrBuf, 20, 10);
	strcat_s(strbuf, 80, scrBuf);
	strcpy_s(m_strMsg, 80, strbuf);

	//fix : use xml
	m_panMetal = Panel(200, 200, 100, 100, 200, 200);
	m_panPlate = Panel(301, 212, 79, 80, 220, 255);

	m_btnNew = Button(200, 500, 100, 100, 240, 245);
	m_btnRank = Button(300, 800, 100, 100, 460, 245);

	return 0;
}

void CEndMenu::Destroy()
{
}

int CEndMenu::ProcessInput()
{
	D3DXVECTOR3 pos = GINPUT->GetCurMousePos();
	POINT pt = { (LONG)pos.x,(LONG)pos.y };

	if (PtInRect(&m_btnNew._btnRect, pt))
		SendMessage(GetActiveWindow(), WM_NEW_GAME, 0, 0);
	else if (PtInRect(&m_btnRank._btnRect, pt))
		MessageBox(GetActiveWindow(), "Rank!", "Rank!", 0);
	else
		return 0;
}

int CEndMenu::Update()
{
	return 0;
}

int CEndMenu::Render()
{
	if (GSPRITE)
	{
		GSPRITE->Draw(m_texUIpack.GetTexture(), &m_panMetal._srcRect, nullptr, 0, &m_panMetal._pos, &D3DXVECTOR2(4.0f, 2.0f), D3DXCOLOR(1, 1, 1, 1));
		GSPRITE->Draw(m_texUIpack.GetTexture(), &m_panPlate._srcRect, nullptr, 0, &m_panPlate._pos, &D3DXVECTOR2(4.5f, 1.5f), D3DXCOLOR(1, 1, 1, 1));
		GSPRITE->Draw(m_texButtons.GetTexture(), &m_btnNew._srcRect, nullptr, 0, &m_btnNew._pos, nullptr, D3DXCOLOR(1, 1, 1, 1));
		GSPRITE->Draw(m_texButtons.GetTexture(), &m_btnRank._srcRect, nullptr, 0, &m_btnRank._pos, nullptr, D3DXCOLOR(1, 1, 1, 1));
	}
	else
		return -1;

	RECT rc;
	if (GFONT)
	{
		::SetRect(&rc, 240, 220, 640, 300);
		GFONT->DrawText(NULL, m_strMsg, -1, &rc, 0, D3DXCOLOR(1, 1, 1, 1));
		::SetRect(&rc, 250, 340, 380, 370);
		GFONT->DrawText(NULL, "새 게임", -1, &rc, 0, D3DXCOLOR(1, 1, 1, 1));
		::SetRect(&rc, 485, 340, 585, 370);
		GFONT->DrawText(NULL, "순위", -1, &rc, 0, D3DXCOLOR(1, 1, 1, 1));
	}
	else
		return -1;
	return 0;
}
