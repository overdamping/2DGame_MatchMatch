#pragma once

#ifndef _STDAFX_H_
#define _STDAFX_H_

#include <Windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string.h>
#include <ctime>
#include <vector>
#include <stack>
#include <memory>
#include <cassert>
#include <fstream>
#include <algorithm>
#include "rapidxml-1.13\rapidxml.hpp"

#include "Util.h"
#include "D3DApp.h"
#include "GameSprite.h"
#include "GameTexture.h"
#include "GameInput.h"
#include "CCamera.h"
#include "Card.h"
#include "GameScene.h"
#include "GamePlay.h"
#include "MainMenu.h"
#include "EndMenu.h"
#include "Hiscore.h"
#include "Main.h"

#define SCREEN_WIDTH		800
#define	SCREEN_HEIGHT		600

//Game grid information
#define	INTERVAL			0.3f
#define CARD_WIDTH			1.6f
#define CARD_HEIGHT			1.6f

#define GDEVICE				g_pApp->GetDevice()
#define GSPRITE				g_pApp->GetSprite()
#define GFONT				g_pApp->GetDXFont()
#define GCAMERA				g_pApp->GetCamera()
#define GINPUT				g_pGameInput

#define WM_NEW_GAME			(WM_APP + 0x0001)
#define WM_RESUME_GAME		(WM_APP + 0x0002)
#define	WM_GAME_WON			(WM_APP + 0X0003)
#define WM_HISCORE			(WM_APP + 0X0004)

#endif