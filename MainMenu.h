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
};

