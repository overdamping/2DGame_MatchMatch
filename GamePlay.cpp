//-----------------------------------------------------------------------------
//Implementation of the CGamePlay class
//-----------------------------------------------------------------------------
#pragma once
#include "Stdafx.h"

CGamePlay::CGamePlay()
{
}


CGamePlay::~CGamePlay()
{
	Destroy();
}

int CGamePlay::Init() 
{
	//Texture creation
	if (FAILED(m_texBackground.Create(GDEVICE, "Texture/wood_texture.bmp")))
		return -1;

	m_texCard[0].Create(GDEVICE, "Texture/ace.png");
	m_texCard[1].Create(GDEVICE, "Texture/castle.png");
	m_texCard[2].Create(GDEVICE, "Texture/fishing.png");
	m_texCard[3].Create(GDEVICE, "Texture/horus.png");
	m_texCard[4].Create(GDEVICE, "Texture/key.png");
	m_texCard[5].Create(GDEVICE, "Texture/rocket.png");
	m_texCard[6].Create(GDEVICE, "Texture/sniffing-dog.png");
	m_texCard[7].Create(GDEVICE, "Texture/wolf-head.png");
	m_texCard[8].Create(GDEVICE, "Texture/backFace.png");
	
	//Card objects creation
	CreateCards();

	//Score board creation
	m_gameScore.Create(585, 29, 215, 30);

	//setting indices
	ndxFirstClk = -1;
	ndxSecondClk = -1;

	return 0;
}

void CGamePlay::CreateCards()
{
	std::vector<int> tempOld = {0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7};
	std::vector<int> tempNew(0);
	while (!tempOld.empty())
	{
		srand((unsigned)time(NULL));
		int ndx = rand() % tempOld.size();
		tempNew.insert(tempNew.end(), tempOld[ndx]);
		tempOld.erase(tempOld.begin()+ndx);
	}

	for (int i = 0; i<16; i++)
	{
		m_cards[i].Create(tempNew[i],
			-2.3 + (i / 4)*(INTERVAL + CARD_WIDTH),
			-2 + (i % 4)*(INTERVAL + CARD_HEIGHT),
			&m_texCard[tempNew[i]],
			&m_texCard[8]);
	}
}

void CGamePlay::Destroy()
{
}

int CGamePlay::Render()
{
		//Background rendering
		if(!GSPRITE || FAILED(GSPRITE->Draw(m_texBackground.GetTexture(), &m_texBackground.GetImageRect(), nullptr, 0, nullptr, nullptr, D3DXCOLOR(1, 1, 1, 1))))
			return -1;

		//Game cards rendering
		for (int i = 0; i < 16; i++)
		{
			if (!GSPRITE || FAILED(m_cards[i].Render()))
				return -1;
		}

		//Game Score rendering
		if (FAILED(m_gameScore.Render()))
			return -1;

	return 0;
}

int CGamePlay::ProcessInput()							//process mouse input (left button click)
{
	D3DXVECTOR3 pos = GINPUT->GetCurMousePos();
	Ray ray = CalcPickingRay(pos.x, pos.y);				//get picking ray

	for (int ndx = 0; ndx < 16; ndx++)
	{
		if (RayQuadIntersectionTest(ray, m_cards[ndx].GetQuadVertices()) && !m_cards[ndx].isfound)
		{
			if (ndxFirstClk == -1)								//first card clicked
			{
				ndxFirstClk = ndx;
				m_cards[ndxFirstClk].isFlipped = FALSE;
				return 0;
			}
			else
				if (ndxSecondClk == -1 && ndx != ndxFirstClk)	//second card clicked
				{
					ndxSecondClk = ndx;
					m_cards[ndxSecondClk].isFlipped = FALSE;
					m_fTimeBgn = timeGetTime() * 0.001f;		
					return 0;
				}
		}
	}
	return 0;
}

int CGamePlay::Update()
{
	//Card pair matching
	if (ndxSecondClk != -1)
	{
		m_fTimeEnd = timeGetTime() * 0.001f;
		if (m_fTimeEnd - m_fTimeBgn >= 0.2)			//delay for 0.2sec after second card clicked
		{
			if (m_cards[ndxFirstClk].Equals(&m_cards[ndxSecondClk]))
			{
				m_cards[ndxFirstClk].isfound = TRUE;
				m_cards[ndxSecondClk].isfound = TRUE;
				m_gameScore.ScoreIncrease();
			}
			else
			{
				m_cards[ndxFirstClk].isFlipped = TRUE;
				m_cards[ndxSecondClk].isFlipped = TRUE;
			}
			ndxFirstClk = -1;
			ndxSecondClk = -1;
		}
	}

	//Game End : All card pairs ard founded
	if (m_gameScore.GetGameScore() == 8)
		PostQuitMessage(0);

	return 0;
}
