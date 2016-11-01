//-----------------------------------------------------------------------------
//Implementation of the CMain class
//-----------------------------------------------------------------------------
#pragma once
#include "StdAfx.h"

CMain::CMain() :m_pSprite(nullptr), m_pFont(nullptr), m_pGameScene(nullptr), m_pGameInput(nullptr)
{
}


CMain::~CMain()
{
	CMain::Destroy();
}

int CMain::Init()
{
	//create and initialize game scene
	if (!m_pGameScene)
	{
		m_pGameScene = new CGamePlay();
		if (FAILED(m_pGameScene->Init()))
			return -1;
	}

	if (!m_pSprite)
	{
		m_pSprite = new CGameSprite();
		if (FAILED(m_pSprite->Create(m_pd3dSprite)))
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

	if(FAILED(D3DXCreateFontIndirect(m_pd3dDevice, &desc, &m_pFont)))
		return -1;

	if (!m_pGameInput)
	{
		m_pGameInput = new CGameInput();
		if (FAILED(m_pGameInput->Init()))
			return -1;
	}

	return 0;
}

void CMain::Destroy()
{
	SAFE_DELEETE(m_pGameScene);
	SAFE_RELEASE(m_pFont);
	SAFE_DELEETE(m_pSprite);
	SAFE_DELEETE(m_pGameInput);
}

int CMain::Update()
{
	if (!m_pGameInput)
		return -1;
	
	if (!m_pGameScene)
		return -1;
	
	m_pGameInput->Update();
	m_pGameScene->Update();

	return 0;
}

int CMain::Render()
{
	//Clear the buffer
	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,120,160), 1.0f, 0);

	//Begin the Scene
	if(FAILED(m_pd3dDevice->BeginScene()))
		return -1;

	//Game Scene Rendering
	if (m_pSprite)
	{
		if (m_pGameScene)
		{
			if (FAILED(m_pGameScene->Render()))
				return -1;
		}
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
	}

	return CD3DApp::MsgProc(hWnd, msg, wParam, lParam);
}