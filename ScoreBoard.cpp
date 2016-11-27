//-----------------------------------------------------------------------------
// Implementation of the CScoreBoard class
//-----------------------------------------------------------------------------
#pragma once
#include "StdAfx.h"

CScoreBoard::CScoreBoard()
{
}


CScoreBoard::~CScoreBoard()
{
}

int CScoreBoard::Create(float posX, float posY, float width, float height)
{
	m_cntAttemps = 0;
	::SetRect(&m_boardRect, posX, posY, posX + width, posY + height);
	return 0;
}

int CScoreBoard::Render()
{
	char strBuff[80];
	char scrBuff[20];
	strcpy_s(strBuff, "Attempts : ");
	_itoa_s(m_cntAttemps, scrBuff, 20, 10);
	strcat_s(strBuff, scrBuff);

	if (GFONT)
	{
		GFONT->DrawText(NULL, strBuff, -1, &m_boardRect, 0, D3DXCOLOR(1, 1, 1, 1));
		return 0;
	}
	else 
		return -1;
}

int CScoreBoard::GetGameScore() const
{
	return m_cntAttemps;
}

void CScoreBoard::ScoreIncrease()
{
	m_cntAttemps++;
}
