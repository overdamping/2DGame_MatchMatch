//-----------------------------------------------------------------------------
// 2D Game App
//-----------------------------------------------------------------------------
#pragma once
#include "StdAfx.h"

CMain*	g_pApp;

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
	CMain	d3dApp;
	g_pApp = &d3dApp;

	if(FAILED(d3dApp.Create(hInst)))
		return -1;

	return d3dApp.Run();
}