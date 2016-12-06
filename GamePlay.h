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

	int Update();
	int Render();
	int ProcessInput();

	int GetGameScore() const;
private:
	void CreateCards();

private:
	CGameTexture			m_texBackground;	//Background texture
	CGameTexture			m_texCard[9];		//Card textures
	CCard					m_cards[16];		//Card objects

	//indices for pair matching
	int ndxFirstClk;
	int ndxSecondClk;

	float m_fTimeBgn;
	float m_fTimeEnd;

	int cntMatchedPair;
	int cntAttemps;
};

