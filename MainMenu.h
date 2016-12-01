//-----------------------------------------------------------------------------
//Interface of the CMainMenu class
//-----------------------------------------------------------------------------
#pragma once

class CMainMenu : public IGameScene
{
public:
	CMainMenu();
	~CMainMenu();

	int Init();
	void Destroy();

	int ProcessInput();
	int Render();
	int Update() {return 0;};

private:
	CGameTexture m_texUIpack;
	CGameTexture m_texButtons;
	
	Panel m_panMetal;
	Panel m_panPlate;

	Button m_btnNew;
	Button m_btnResume;
	Button m_btnRank;
};

