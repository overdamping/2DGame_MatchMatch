//-----------------------------------------------------------------------------
//Interface of the CScoreBoard class
//-----------------------------------------------------------------------------
#pragma once

class CScoreBoard
{
public:
	CScoreBoard();
	~CScoreBoard();
	int Render();
public:
	int GetGameScore() const;
	void ScoreIncrease();

private:
	int m_score;
	RECT m_boardRect;
};

