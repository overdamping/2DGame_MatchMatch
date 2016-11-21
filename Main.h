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
	//IGameScene* 	m_pMainMenu;
	//std::stack<std::unique_ptr<IGameScene>> scenes;

	LPD3DXFONT		m_pFont;
	CGameSprite*	m_pSprite;
	CGameInput*		m_pGameInput;
	CCamera*		m_pCamera;

public:
	CGameSprite*	GetSprite() { return m_pSprite; }
	LPD3DXFONT		GetDXFont() { return m_pFont;   }
	CCamera*		GetCamera() { return m_pCamera; }
};

extern CMain* g_pApp;

