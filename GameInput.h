//-----------------------------------------------------------------------------
//Interface of the CGameInput class
//-----------------------------------------------------------------------------
#pragma once

class CGameInput
{
public:
	CGameInput();
	~CGameInput();

	int Init();
public:
	D3DXVECTOR3 GetCurMousePos() const;

	void LButtonDown(int posX, int posY);
	void LButtonUp(int posX, int posY);
	BOOL LButtonClicked() const;
private:
	void SetMousePos(int posX, int posY);

private:
	D3DXVECTOR3 m_mousePosCur;
	D3DXVECTOR3 m_mousePosOld;

	float m_fTimeBgn;
	float m_fTimeEnd;
};

extern CGameInput* g_pGameInput;
