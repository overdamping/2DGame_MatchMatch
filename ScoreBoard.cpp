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
	m_score = 0;

	m_boardRect.left = posX;
	m_boardRect.right = posX+width;
	m_boardRect.top = posY;
	m_boardRect.bottom = posY+height;

	return 0;
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
