//-----------------------------------------------------------------------------
//Implementation of the CMain class
//-----------------------------------------------------------------------------
#pragma once
#include "StdAfx.h"

CMain::CMain()
{
	m_pSprite		= nullptr;
	m_pFont			= nullptr; 
	m_pGameScene	= nullptr;
	m_pMainMenu		= nullptr; 
	m_pEndMenu		= nullptr; 
	m_pHiscore		= nullptr; 
	m_pGameInput	= nullptr; 
	m_pCamera		= nullptr;
}


CMain::~CMain()
{
	CMain::Destroy();
}

int CMain::Init()
{
	//create and initialize play scenes, menus and input object
	SAFE_INIT(m_pGameScene, CGamePlay);							
	SAFE_INIT(m_pMainMenu, CMainMenu);
	SAFE_INIT(m_pEndMenu, CEndMenu);
	SAFE_INIT(m_pHiscore, CHiscore);
	SAFE_INIT(m_pGameInput, CGameInput);						 

	//sprite creation
	if (!m_pSprite)
	{
		m_pSprite = new CGameSprite();
		if (FAILED(m_pSprite->Create(m_pd3dSprite)))
			return -1;
	}

	//camera cration
	if (!m_pCamera)
	{
		m_pCamera = new CCamera();
		if (FAILED(m_pCamera->Create(m_pd3dDevice)))
			return -1;
	}

	//font creattion
	if (AddFontResourceEx("font/08SeoulNamsanB.ttf", FR_PRIVATE | FR_NOT_ENUM, NULL) == 0)
		return -1;

	D3DXFONT_DESC desc;
	desc.CharSet = HANGUL_CHARSET;
	desc.Height = 26;
	desc.Width = 0;
	desc.Weight = FW_BOLD;
	desc.Quality = ANTIALIASED_QUALITY;
	desc.MipLevels = 1;
	desc.Italic = FALSE;
	desc.OutputPrecision = OUT_DEFAULT_PRECIS;
	desc.PitchAndFamily = FF_DONTCARE;
	strcpy_s(desc.FaceName, "08서울남산체 B");
	
	if (FAILED(D3DXCreateFontIndirect(m_pd3dDevice, &desc, &m_pFont)))
		return -1;

	//setting rendering state
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);			//turn off advanced 3D lighting
	m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);		//turn off culling (render both sides of each polygon)
	m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);		//disable z-buffering

	m_pd3dDevice->SetFVF(CUSTOMFVF);

	return 0;
}

void CMain::Destroy()
{
	while (!menus.empty())
	{
		menus.top().release();
		menus.pop();
	}
	SAFE_DELEETE(m_pGameScene);
	SAFE_DELEETE(m_pMainMenu);
	SAFE_DELEETE(m_pEndMenu);
	SAFE_DELEETE(m_pHiscore);
	SAFE_RELEASE(m_pFont);
	SAFE_DELEETE(m_pSprite);
	SAFE_DELEETE(m_pGameInput);
	SAFE_DELEETE(m_pCamera);
}

int CMain::Update()
{
	if (menus.empty())	//update game scene
	{
		SAFE_UPDATE(m_pGameScene);
	}
	else
	{
		if (FAILED(menus.top().get()->Update()))	//update current menu
			return -1;
	}
		
	SAFE_UPDATE(m_pCamera);							//camera update
	return 0;
}

int CMain::Render()
{
	//clear the buffer
	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//get the view matrix
	D3DXMATRIX mt;
	if (m_pCamera)
	{
		m_pCamera->GetViewMatrix(&mt);
		m_pd3dDevice->SetTransform(D3DTS_VIEW, &mt);
	}
	else 
		return -1;

	//begin the Scene
	if(FAILED(m_pd3dDevice->BeginScene()))
		return -1;

	//render the game scene
	if (m_pGameScene)
	{
		if (FAILED(m_pGameScene->Render()))
			return -1;
	}

	//if menu stack is not empty, render stack top
	if (!menus.empty())
	{
		if (FAILED(menus.top().get()->Render()))	
			return -1;
	}
	
	//end the scene
	m_pd3dDevice->EndScene();
	return 0;
}

LRESULT CMain::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) //press ESC key 
			{
				if (menus.empty())	//if menu stack is empty, enter main menu
				{
					assert(m_pMainMenu);
					menus.push(std::unique_ptr<IGameScene>(m_pMainMenu));
					assert(menus.top().get() == m_pMainMenu);
				}
				else	//exit current menu(except when it's end menu)
				{
					if (menus.top().get() != m_pEndMenu)
					{
						menus.top().release();
						menus.pop();
					}
				}
			}
			return 0;
		case WM_LBUTTONDOWN:	//left mouse button down
			if(GINPUT)
				GINPUT->LButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		case WM_LBUTTONUP:		//left mouse button up
			if (GINPUT)
			{
				GINPUT->LButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				if (GINPUT->LButtonClicked())	//process mouse input(left button click)
				{
					if (!menus.empty())
						menus.top().get()->ProcessInput();	
					else
						m_pGameScene->ProcessInput();
				}
			}
			return 0;
		case WM_NEW_GAME:			//load new game
			menus.top().release();
			menus.pop();
			assert(menus.empty());
			SAFE_DELEETE(m_pGameScene);
			SAFE_INIT(m_pGameScene, CGamePlay);		//create new game play scene
			assert(m_pGameScene);
			return 0;
		case WM_RESUME_GAME:		//resume game
			menus.top().release();	//pop the main menu from menu stack
			menus.pop();
			assert(menus.empty());
			return 0;
		case WM_GAME_WON:			//player won the game				
			assert(menus.empty());
			dynamic_cast<CEndMenu*>(m_pEndMenu)->SetFinalScore(wParam);	
			menus.push(std::unique_ptr<IGameScene>(m_pEndMenu));		//show end menu with final score
			assert(menus.top().get() == m_pEndMenu);
			dynamic_cast<CHiscore*>(m_pHiscore)->UpdateRecord(wParam);	//update score records
			return 0;
		case WM_HISCORE:	//show ranking menu
			assert(m_pHiscore);
			menus.push(std::unique_ptr<IGameScene>(m_pHiscore));	
			assert(menus.top().get() == m_pHiscore);
			return 0;
	}

	return CD3DApp::MsgProc(hWnd, msg, wParam, lParam);
}