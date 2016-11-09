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

void CGameInput::SetMousePos(int posX, int posY)
{
	memcpy(&m_mousePosOld, &m_mousePosCur, sizeof(m_mousePosCur));
	m_mousePosCur.x = posX;
	m_mousePosCur.y = posY;
}

BOOL CGameInput::LButtonClicked() const
{
	return (m_fTimeEnd - m_fTimeBgn <= 0.2 || m_mousePosCur == m_mousePosOld);
}

void CGameInput::LButtonDown(int posX, int posY)
{
	SetMousePos(posX, posY);
	m_fTimeBgn = timeGetTime() * 0.001f;
}

void CGameInput::LButtonUp(int posX, int posY)
{
	SetMousePos(posX, posY);
	m_fTimeEnd = timeGetTime() * 0.001f;
}

D3DXVECTOR3 CGameInput::GetCurMousePos() const
{
	return m_mousePosCur;
}
