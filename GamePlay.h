//-----------------------------------------------------------------------------
//Interface of the CGamePlay class
//-----------------------------------------------------------------------------
#pragma once
#include "GameScene.h"

class CGamePlay : public CGameScene
{
public:
	CGamePlay();
	virtual ~CGamePlay();

	virtual int Init();
	virtual void Destroy();

	virtual int Update();
	virtual int Render();
private:
	void CreateCards();

private:
	//Game grid information
	float interval = 10;
	float cardWidth = 128;
	float cardHeight = 128;

	CGameTexture			m_texBackground;	//Background texture
	CGameTexture			m_texCard[9];		//Card textures
	CCard					m_cards[16];		//Card objects
	CScoreBoard			m_pGameScore;		//Game Score board

	//indices for pair matching
	int ndxFirstClk;
	int ndxSecondClk;
};

