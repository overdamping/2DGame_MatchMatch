//-----------------------------------------------------------------------------
//Implementation of the CGameInput class
//-----------------------------------------------------------------------------
#pragma once
#include "StdAfx.h"

CGameInput* g_pGameInput;

CGameInput::CGameInput()
{
	g_pGameInput = this;
}


CGameInput::~CGameInput()
{
}

int CGameInput::Init()
{
	memset(&m_mousePosCur, 0, sizeof(m_mousePosCur));
	memset(&m_mousePosOld, 0, sizeof(m_mousePosOld));
	return 0;
}

int CGameInput::Update()
{
	SetMousePos();
	return 0;
}

void CGameInput::SetMousePos()
{
	memcpy(&m_mousePosOld, &m_mousePosCur, sizeof(m_mousePosCur));

	POINT mouse;
	::GetCursorPos(&mouse);
	::ScreenToClient(::GetActiveWindow(), &mouse);

	m_mousePosCur.x = float(mouse.x);
	m_mousePosCur.y = float(mouse.y);
}

BOOL CGameInput::IsClicked(RECT area)
{
	return ((m_mousePosCur.x>area.left)
		&&(m_mousePosCur.x<area.right)
		&&(m_mousePosCur.y<area.bottom)
		&&(m_mousePosCur.y>area.top));
}

D3DXVECTOR3 CGameInput::GetCurMousePos() const
{
	return m_mousePosCur;
}

BOOL CGameInput::IsPressed(int vKey)
{
	return (GetAsyncKeyState(vKey) & 0x0001 == TRUE);
}
