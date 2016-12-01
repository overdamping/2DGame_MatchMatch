//-----------------------------------------------------------------------------
//Interface of the CHiscore class
//-----------------------------------------------------------------------------
#pragma once

class CHiscore : public IGameScene
{
public:
	CHiscore();
	~CHiscore();

	int Init();
	void Destroy();

	int ProcessInput() {return 0;};;
	int Render();
	int Update() {return 0;};

private:
	CGameTexture m_texUIpack;
	CGameTexture m_texButtons;

	Panel m_panMetal;
	Panel m_panPlate;
};

