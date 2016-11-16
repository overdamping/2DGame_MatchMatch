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

#include "Util.h"
#include "D3DApp.h"
#include "GameSprite.h"
#include "GameTexture.h"
#include "GameInput.h"
#include "CCamera.h"
#include "Card.h"
#include "ScoreBoard.h"
#include "GameScene.h"
#include "GamePlay.h"
#include "Main.h"


#define GDEVICE				g_pApp->GetDevice()
#define GSPRITE				g_pApp->GetSprite()
#define GINPUT				g_pGameInput
#define GFONT				g_pApp->GetDXFont()

#endif