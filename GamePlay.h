//-----------------------------------------------------------------------------
//Interface of the CGamePlay class
//-----------------------------------------------------------------------------
#pragma once
#include "GameScene.h"

class CGamePlay : public IGameScene
{
public:
	CGamePlay();
	~CGamePlay();

	int Init();
	void Destroy();

	int ProcessInput();
	int Update();
	int Render();
private:
	void CreateCards();

private:
	//float interval = 10;
	//float cardWidth = 128;
	//float cardHeight = 128;

	CGameTexture			m_texBackground;	//Background texture
	CGameTexture			m_texCard[9];		//Card textures
	CCard					m_cards[16];		//Card objects
	CScoreBoard				m_gameScore;		//Game Score board

	//indices for pair matching
	int ndxFirstClk;
	int ndxSecondClk;

	float m_fTimeBgn;
	float m_fTimeEnd;
};

