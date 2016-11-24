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
	//background texture creation
	if (FAILED(m_texBackground.Create(GDEVICE, "Texture/wood_texture.bmp")))
		return -1;

	//button texture creation
	if (FAILED(m_texButtons.Create(GDEVICE, "Texture/sheet_white2x.png")))
		return -1;

	//fix : use xml
	m_btnNew = Button(200, 500, 300, 600, 200, 250);
	m_btnResume = Button(200, 300, 300, 400, 350, 250);
	m_btnRank = Button(300, 800, 400, 900, 500, 250);

	return 0;
}

void CMainMenu::Destroy()
{
}

int CMainMenu::ProcessInput()			//process mouse input (left button click)
{
	D3DXVECTOR3 pos = GINPUT->GetCurMousePos();
	POINT pt = { (LONG)pos.x,(LONG)pos.y };

	if (PtInRect(&m_btnNew._btnRect, pt))
		SendMessage(GetActiveWindow(), WM_NEW_GAME, 0, 0);
		/*MessageBox(GetActiveWindow(), "new!", "new!", 0);*/
	else if (PtInRect(&m_btnResume._btnRect, pt))
		SendMessage(GetActiveWindow(), WM_RESUME_GAME, 0, 0);
		/*MessageBox(GetActiveWindow(), "resume!", "resume!", 0);*/
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
	//background and button rendering
	if (GSPRITE)
	{
		GSPRITE->Draw(m_texBackground.GetTexture(), &m_texBackground.GetImageRect(), nullptr, 0, nullptr, nullptr, D3DXCOLOR(1, 1, 1, 1));
		GSPRITE->Draw(m_texButtons.GetTexture(), &m_btnNew._srcRect, nullptr, 0, &m_btnNew._pos, nullptr, D3DXCOLOR(1, 1, 1, 1));
		GSPRITE->Draw(m_texButtons.GetTexture(), &m_btnResume._srcRect, nullptr, 0, &m_btnResume._pos, nullptr, D3DXCOLOR(1, 1, 1, 1));
		GSPRITE->Draw(m_texButtons.GetTexture(), &m_btnRank._srcRect, nullptr, 0, &m_btnRank._pos, nullptr, D3DXCOLOR(1, 1, 1, 1));
	}
	else
		return -1;

	//if (GFONT)
	//{
	//	GFONT->DrawText(NULL, "new game", -1, &RECT{200, 350, 250, 400}, 0, D3DXCOLOR(1, 1, 1, 1));
	//	GFONT->DrawText(NULL, "resume", -1, &RECT(), 0, D3DXCOLOR(1, 1, 1, 1));
	//	GFONT->DrawText(NULL, "ranking", -1, &RECT(), 0, D3DXCOLOR(1, 1, 1, 1));
	//}
	//else
	//	return -1;

	return 0;
}
