//-----------------------------------------------------------------------------
//Interface of the CMain class
//-----------------------------------------------------------------------------
#pragma once

class CMain :public CD3DApp
{
public:
	CMain();
	~CMain();

	virtual int Init();
	virtual void Destroy();

	virtual int Update();
	virtual int Render();

	virtual LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
	IGameScene*		m_pGameScene;
	LPD3DXFONT		m_pFont;
	CGameSprite*	m_pSprite;
	CGameInput*		m_pGameInput;
public:
	CGameSprite*	GetSprite() { return m_pSprite; }
	LPD3DXFONT		GetDXFont() { return m_pFont;   }
};

extern CMain* g_pApp;

