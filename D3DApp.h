//-----------------------------------------------------------------------------
// Interface of the CD3DApp class
//-----------------------------------------------------------------------------
#pragma once

class CD3DApp
{
public:
	HRESULT Create(HINSTANCE hInst);
	HRESULT InitD3D();
	int Run();
	void CleanUp();
	int Render3D();

	virtual int Init()				{return 0;}
	virtual void Destroy()			{		  }
	virtual int Render()			{return 0;}
	virtual int Update()			{return 0;}

	virtual LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	CD3DApp();
	virtual ~CD3DApp();

protected:
	CHAR				m_sCls[128];
	HINSTANCE			m_hInst;
	HWND				m_hWnd;
	DWORD				m_dWinStyle;

	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pd3dDevice;
	LPD3DXSPRITE		m_pd3dSprite;

	BOOL				m_bWindow;
	BOOL				m_bShowCusor;

public:
	LPDIRECT3DDEVICE9	GetDevice() { return m_pd3dDevice; };
};

