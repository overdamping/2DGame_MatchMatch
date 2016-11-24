//-----------------------------------------------------------------------------
// Implementation of the CD3DApp class
//-----------------------------------------------------------------------------
#pragma once
#include "StdAfx.h"

static CD3DApp* g_pD3DApp;

CD3DApp::CD3DApp()
{
	g_pD3DApp = this;
	strcpy_s(m_sCls, "Match Match");

	m_hInst			= NULL;
	m_hWnd			= NULL;
	m_dWinStyle		= WS_OVERLAPPEDWINDOW | WS_VISIBLE;

	m_pD3D			= nullptr;			// D3D
	m_pd3dDevice	= nullptr;			// Device
	m_pd3dSprite	= nullptr;			// 2D Sprite

	m_bShowCusor	= TRUE;
	m_bWindow		= TRUE;			// Window mode

}

HRESULT CD3DApp::Create(HINSTANCE hInst)
{
	m_hInst	= hInst;

	//Register window class
	WNDCLASS wc;
	memset(&wc,0, sizeof(wc));
	
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0L;
	wc.cbWndExtra = 0L;
	wc.hInstance = m_hInst;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_sCls;

	RegisterClass(&wc);

	//Create the application's window
	RECT rc;
	SetRect(&rc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	AdjustWindowRect(&rc, m_dWinStyle, FALSE);

	int iScnDydW = ::GetSystemMetrics(SM_CXSCREEN);
	int iScnDydH = ::GetSystemMetrics(SM_CYSCREEN);

	m_hWnd = CreateWindow( m_sCls
		,m_sCls
		,m_dWinStyle
		,(iScnDydW - (rc.right - rc.left))/2
		,(iScnDydH - (rc.bottom - rc.top))/2
		,(rc.right - rc.left)
		,(rc.bottom - rc.top)
		,GetDesktopWindow()
		,NULL
		,m_hInst
		,NULL );

	//Initialize Direct3D
	if(FAILED(InitD3D()))
		return -1;

	if (FAILED(Init()))
		return -1;

	//show window
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
	::ShowCursor(m_bShowCusor);

	return 0;
}

HRESULT CD3DApp::InitD3D()
{
	//Create D3D
	if(NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return -1;

	//Create Device
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed				= m_bWindow;
	d3dpp.SwapEffect			= D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil= TRUE;
	d3dpp.AutoDepthStencilFormat= D3DFMT_D16;

	if(FAILED (m_pD3D->CreateDevice(D3DADAPTER_DEFAULT
									,	D3DDEVTYPE_HAL
									,	m_hWnd
									,	D3DCREATE_MIXED_VERTEXPROCESSING
									,	&d3dpp
									,	&m_pd3dDevice )))
		return -1;
	
	//Create DX Sprite
	if(FAILED (D3DXCreateSprite(m_pd3dDevice, &m_pd3dSprite)))
		return -1;

	return 0;
}

int CD3DApp::Run()
{
	MSG msg;
	memset(&msg, 0, sizeof(msg));

	while(msg.message!=WM_QUIT)	// Enter the message loop
	{
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if(FAILED(Render3D()))
				break;
			m_pd3dDevice->Present(0, 0, 0, 0);
		}
	}

	UnregisterClass(m_sCls, m_hInst);
	return 0;
}

//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
void CD3DApp::CleanUp()
{
	Destroy();

	SAFE_RELEASE(m_pd3dSprite);
	SAFE_RELEASE(m_pd3dDevice);
	SAFE_RELEASE(m_pD3D);
}

int CD3DApp::Render3D()
{
	if(NULL == m_pd3dDevice)
		return -1;

	if(FAILED(Update()))
		return -1;

	if(FAILED(Render()))
		return -1;

	return 0;
}

//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT CD3DApp::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_DESTROY:
			CleanUp();
			PostQuitMessage(0);
			return 0;
		case WM_PAINT:
			Render();
			ValidateRect(hWnd, NULL);
			return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT WINAPI CD3DApp::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return g_pD3DApp->MsgProc(hWnd, msg, wParam, lParam);
}

CD3DApp::~CD3DApp()
{
}
