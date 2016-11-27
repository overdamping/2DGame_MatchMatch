//-----------------------------------------------------------------------------
//Implementation of the CMainMenu class
//-----------------------------------------------------------------------------
#include "StdAfx.h"

CMainMenu::CMainMenu()
{
}


CMainMenu::~CMainMenu()
{
	Destroy();
}

int CMainMenu::Init()
{
	//UI texture creation
	if (FAILED(m_texUIpack.Create(GDEVICE, "texture/uipackSpace_sheet.png")))
		return -1;

	//button texture creation
	if (FAILED(m_texButtons.Create(GDEVICE, "texture/sheet_white2x.png")))
		return -1;

	//fix : use xml
	m_panMetal = Panel(200, 200, 100, 100, 200, 200);
	m_panPlate = Panel(301, 212, 79, 80, 220, 255);

	m_btnNew = Button(200, 500, 100, 100, 240, 265);
	m_btnResume = Button(200, 300, 100, 100, 350, 265);
	m_btnRank = Button(300, 800, 100, 100, 460, 265);

	return 0;
}

void CMainMenu::Destroy()
{
}

int CMainMenu::ProcessInput()	//process mouse input (left button click)
{
	D3DXVECTOR3 pos = GINPUT->GetCurMousePos();
	POINT pt = { (LONG)pos.x,(LONG)pos.y };

	if (PtInRect(&m_btnNew._btnRect, pt))
		SendMessage(GetActiveWindow(), WM_NEW_GAME, 0, 0);
	else if (PtInRect(&m_btnResume._btnRect, pt))
		SendMessage(GetActiveWindow(), WM_RESUME_GAME, 0, 0);
	else if (PtInRect(&m_btnRank._btnRect, pt))
		MessageBox(GetActiveWindow(), "Rank!", "Rank!", 0);
	else
		return 0;
}

int CMainMenu::Update()
{
	return 0;
}

int CMainMenu::Render()
{
	if (GSPRITE)
	{
		GSPRITE->Draw(m_texUIpack.GetTexture(), &m_panMetal._srcRect, nullptr, 0, &m_panMetal._pos, &D3DXVECTOR2(4.0f, 2.0f), D3DXCOLOR(1, 1, 1, 1));
		GSPRITE->Draw(m_texUIpack.GetTexture(), &m_panPlate._srcRect, nullptr, 0, &m_panPlate._pos, &D3DXVECTOR2(4.5f, 1.5f), D3DXCOLOR(1, 1, 1, 1));
		GSPRITE->Draw(m_texButtons.GetTexture(), &m_btnNew._srcRect, nullptr, 0, &m_btnNew._pos, nullptr, D3DXCOLOR(1, 1, 1, 1));
		GSPRITE->Draw(m_texButtons.GetTexture(), &m_btnResume._srcRect, nullptr, 0, &m_btnResume._pos, nullptr, D3DXCOLOR(1, 1, 1, 1));
		GSPRITE->Draw(m_texButtons.GetTexture(), &m_btnRank._srcRect, nullptr, 0, &m_btnRank._pos, nullptr, D3DXCOLOR(1, 1, 1, 1));
	}
	else
		return -1;

	RECT rc;
	::SetRect(&rc, 335, 210, 500, 300);
	if (GFONT)
	{
		GFONT->DrawText(NULL, "- menu -", -1, &rc, 0, D3DXCOLOR(1, 1, 1, 1));
	}
	else
		return -1;

	return 0;
}
