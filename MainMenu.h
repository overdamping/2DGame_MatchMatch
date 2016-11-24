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
	int Update();
	int Render();

private:
	CGameTexture m_texBackground;
	CGameTexture m_texButtons;

	Button m_btnNew;
	Button m_btnResume;
	Button m_btnRank;
};

