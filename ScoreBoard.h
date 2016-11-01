//-----------------------------------------------------------------------------
//Interface of the CScoreBoard class
//-----------------------------------------------------------------------------
#pragma once

class CScoreBoard
{
public:
	CScoreBoard();
	~CScoreBoard();

	int Create(float posX, float posY, float width, float height);
	int Render();
public:
	int GetGameScore() const;
	void ScoreIncrease();

private:
	int m_score;
	RECT m_boardRect;
};

