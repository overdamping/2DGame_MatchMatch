//-----------------------------------------------------------------------------
//Interface of the CEndMenu class
//-----------------------------------------------------------------------------
#pragma once

class CEndMenu : public IGameScene
{
public:
	CEndMenu(int finalScore);
	~CEndMenu();

	int Init();
	void Destroy();

	int ProcessInput();
	int Update();
	int Render();

private:
	int score;
	CGameTexture m_texUIpack;
	CGameTexture m_texButtons;

	Panel m_panMetal;
	Panel m_panPlate;

	Button m_btnNew;
	Button m_btnRank;
};

