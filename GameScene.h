//-----------------------------------------------------------------------------
//Interface of the CGameScene class
//-----------------------------------------------------------------------------
#pragma once

class CGameScene
{
public:
	CGameScene() {};
	virtual ~CGameScene() {};

	virtual int Init() = 0;
	virtual void Destroy() = 0;

	virtual int Update() = 0;
	virtual int Render() = 0;
};

