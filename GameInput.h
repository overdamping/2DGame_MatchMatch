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
	int Update();
public:
	D3DXVECTOR3 GetCurMousePos() const;
	BOOL IsPressed(int vKey);
	BOOL IsClicked(RECT area);
private:
	void SetMousePos();

private:
	D3DXVECTOR3 m_mousePosCur;
	D3DXVECTOR3 m_mousePosOld;

};

extern CGameInput* g_pGameInput;
