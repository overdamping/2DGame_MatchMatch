//-----------------------------------------------------------------------------
//Implementation of the CMain class
//-----------------------------------------------------------------------------
#pragma once
#include "StdAfx.h"

CMain::CMain() :m_pSprite(nullptr), m_pFont(nullptr), m_pGameScene(nullptr), m_pMainMenu(nullptr), m_pGameInput(nullptr), m_pCamera(nullptr)
{
	
}


CMain::~CMain()
{
	CMain::Destroy();
}

int CMain::Init()
{
	SAFE_INIT(m_pGameScene, CGamePlay);							//create and init game play scene
	scenes.push(std::unique_ptr<IGameScene>(m_pGameScene));		//push the scene into scene stack
	
	SAFE_INIT(m_pMainMenu, CMainMenu);							//create and init game main menu
	SAFE_INIT(m_pGameInput, CGameInput);						//create and init input object

	if (!m_pSprite)
	{
		m_pSprite = new CGameSprite();
		if (FAILED(m_pSprite->Create(m_pd3dSprite)))
			return -1;
	}

	if (!m_pCamera)
	{
		m_pCamera = new CCamera();
		if (FAILED(m_pCamera->Create(m_pd3dDevice)))
			return -1;
	}

	D3DXFONT_DESC desc;
	desc.CharSet = HANGUL_CHARSET;
	desc.Height = 28;
	desc.Width = 0;
	desc.Weight = FW_NORMAL;
	desc.Quality = DEFAULT_QUALITY;
	desc.MipLevels = 1;
	desc.Italic = 0;
	desc.OutputPrecision = OUT_DEFAULT_PRECIS;
	desc.PitchAndFamily = FF_DONTCARE;

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
	while (!scenes.empty())
	{
		scenes.top().release();
		scenes.pop();
	}
	SAFE_DELEETE(m_pGameScene);
	SAFE_DELEETE(m_pMainMenu);
	SAFE_RELEASE(m_pFont);
	SAFE_DELEETE(m_pSprite);
	SAFE_DELEETE(m_pGameInput);
	SAFE_DELEETE(m_pCamera);
}

int CMain::Update()
{
	if (!scenes.empty())
	{
		if (FAILED(scenes.top().get()->Update()))	//update current game scene
			return -1;
	}
	else
		return -1;

	SAFE_UPDATE(m_pCamera);							//camera update
	return 0;
}

int CMain::Render()
{
	//clear the buffer
	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

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

	//render the current game scene
	if (!scenes.empty())
	{
		if (FAILED(scenes.top().get()->Render()))	
			return -1;
	}
	else
		return -1;
	
	//end the scene
	m_pd3dDevice->EndScene();
	return 0;
}

LRESULT CMain::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE)							//press ESC key
			{
				if (scenes.top().get() == m_pGameScene)			//enter main menu from game play scene
				{
					scenes.push(std::unique_ptr<IGameScene>(m_pMainMenu));
					assert(scenes.top().get() == m_pMainMenu);
					break;
				}
			}
			return 0;
		case WM_LBUTTONDOWN:
			if(GINPUT)
				GINPUT->LButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		case WM_LBUTTONUP:
			if (GINPUT)
			{
				GINPUT->LButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				if (GINPUT->LButtonClicked())
				{
					assert(!scenes.empty());
					scenes.top().get()->ProcessInput();			//process mouse input(left button click)
				}
			}
			return 0;
		case WM_NEW_GAME:											//load new game
			scenes.top().release();									//pop the main menu
			scenes.pop();
			assert(scenes.top().get() == m_pGameScene);
			scenes.top().release();									//pop the current play scene
			scenes.pop();
			assert(scenes.empty());
			SAFE_DELEETE(m_pGameScene);
			SAFE_INIT(m_pGameScene, CGamePlay);						//create new game play scene
			scenes.push(std::unique_ptr<IGameScene>(m_pGameScene));	//push to scene stack
			return 0;
		case WM_RESUME_GAME:									//resume game
			scenes.top().release();								//pop the main menu from scene stack
			scenes.pop();
			assert(scenes.top().get() == m_pGameScene);
			return 0;
	}

	return CD3DApp::MsgProc(hWnd, msg, wParam, lParam);
}