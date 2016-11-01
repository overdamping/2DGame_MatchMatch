//-----------------------------------------------------------------------------
// Implementation of the CScoreBoard class
//-----------------------------------------------------------------------------
#pragma once
#include "StdAfx.h"

CScoreBoard::CScoreBoard()
{
	m_score = 0;
	::SetRect(&m_boardRect, 585, 29, 800, 29 + 30);
}


CScoreBoard::~CScoreBoard()
{
}

int CScoreBoard::Render()
{
	char strBuff[80];
	char scrBuff[20];
	strcpy_s(strBuff, "Found Pairs: ");
	_itoa_s(m_score, scrBuff, 20, 10);
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
	return m_score;
}

void CScoreBoard::ScoreIncrease()
{
	m_score += 1;
}
