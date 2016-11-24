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
	if (!m_pGameScene)
	{
		m_pGameScene = new CGamePlay();
		if (FAILED(m_pGameScene->Init()))
			return -1;
	}

	
	if (!m_pMainMenu)
	{
		m_pMainMenu = new CMainMenu();
		if (FAILED(m_pMainMenu->Init()))
			return -1;
	}
	

	if (!m_pSprite)
	{
		m_pSprite = new CGameSprite();
		if (FAILED(m_pSprite->Create(m_pd3dSprite)))
			return -1;
	}

	if (!m_pGameInput)
	{
		m_pGameInput = new CGameInput();
		if (FAILED(m_pGameInput->Init()))
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

	scenes.push(std::unique_ptr<IGameScene>(m_pGameScene));

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
	//if (!m_pGameScene)
	//	return -1;
	//m_pGameScene->Update();

	if (scenes.empty())
		return -1;
	scenes.top().get()->Update();

	if (!m_pCamera)
		return -1;
	m_pCamera->Update();

	return 0;
}

int CMain::Render()
{
	//Clear the buffer
	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	D3DXMATRIX mt;

	if (m_pCamera)
	{
		m_pCamera->GetViewMatrix(&mt);
		m_pd3dDevice->SetTransform(D3DTS_VIEW, &mt);
	}
	else 
		return -1;

	//Begin the Scene
	if(FAILED(m_pd3dDevice->BeginScene()))
		return -1;

	if (!scenes.empty())
	{
		if (FAILED(scenes.top().get()->Render()))
			return -1;
	}
	else
		return -1;
	
	//End the scene
	m_pd3dDevice->EndScene();
	return 0;
}

LRESULT CMain::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE)
			{
				if (scenes.top().get() == m_pGameScene)
				{
					scenes.push(std::unique_ptr<IGameScene>(m_pMainMenu));
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
					scenes.top().get()->ProcessInput();
			}
			return 0;
		case WM_NEW_GAME:
			scenes.top().release();
			scenes.pop();
			scenes.top().release();
			scenes.pop();
			SAFE_DELEETE(m_pGameScene);
			if (!m_pGameScene)
			{
				m_pGameScene = new CGamePlay();
				if (FAILED(m_pGameScene->Init()))
					return -1;
			}
			scenes.push(std::unique_ptr<IGameScene>(m_pGameScene));
			return 0;
		case WM_RESUME_GAME:
			scenes.top().release();
			scenes.pop();
			return 0;
		/*return 0;*/
	}

	return CD3DApp::MsgProc(hWnd, msg, wParam, lParam);
}