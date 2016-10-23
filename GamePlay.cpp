//-----------------------------------------------------------------------------
//Implementation of the CGamePlay class
//-----------------------------------------------------------------------------
#pragma once
#include "Stdafx.h"

CGamePlay::CGamePlay() : m_pGameScore(nullptr)
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
	
	//if (FAILED(m_texCard[0].Create(GDEVICE, "Texture/ace.png")))
	//	return -1;
	//if (FAILED(m_texCard[1].Create(GDEVICE, "Texture/castle.png")))
	//	return -1;
	//if (FAILED(m_texCard[2].Create(GDEVICE, "Texture/fishing.png")))
	//	return -1;
	//if (FAILED(m_texCard[3].Create(GDEVICE, "Texture/horus.png")))
	//	return -1;
	//if (FAILED(m_texCard[4].Create(GDEVICE, "Texture/key.png")))
	//	return -1;
	//if (FAILED(m_texCard[5].Create(GDEVICE, "Texture/rocket.png")))
	//	return -1;
	//if (FAILED(m_texCard[6].Create(GDEVICE, "Texture/sniffing-dog.png")))
	//	return -1;
	//if (FAILED(m_texCard[7].Create(GDEVICE, "Texture/wolf-head.png")))
	//	return -1;
	//if (FAILED(m_texCard[8].Create(GDEVICE, "Texture/backFace.png")))
	//	return -1;

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
	if (!m_pGameScore)
		m_pGameScore = new CScoreBoard();

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
			29 + (i / 4)*(interval + cardWidth),
			29 + (i % 4)*(interval + cardHeight),
			&m_texCard[tempNew[i]],
			&m_texCard[8]);
	}
}

void CGamePlay::Destroy()
{
	SAFE_DELEETE(m_pGameScore);
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
		if (FAILED(m_pGameScore->Render()))
			return -1;

	return 0;
}

int CGamePlay::Update()
{
	//Input processing
	if (GINPUT->IsPressed(VK_LBUTTON))
	{
		for (int ndx = 0; ndx < 16; ndx++)
		{
			if (GINPUT->IsClicked(m_cards[ndx].GetCardRect()) && !m_cards[ndx].foundFlag)
			{
				if (ndxFirstClk == -1)								//First card clicked
				{
					ndxFirstClk = ndx;
					m_cards[ndxFirstClk].FlipCard();
					return 0;
				}
				else 							
				{
					if (ndxSecondClk == -1 && ndx != ndxFirstClk)	//Second card clicked
					{
						ndxSecondClk = ndx;
						m_cards[ndxSecondClk].FlipCard();
						return 0;
					}
				}
			}
		}
	}
	
	//Card pair matching
	if (ndxSecondClk != -1)
	{
		Sleep(200);
		if (m_cards[ndxFirstClk].Equals(&m_cards[ndxSecondClk]))
		{
			m_cards[ndxFirstClk].foundFlag = TRUE;
			m_cards[ndxSecondClk].foundFlag = TRUE;
			m_pGameScore->ScoreIncrease();
		}
		else
		{
			m_cards[ndxFirstClk].FlipCard();
			m_cards[ndxSecondClk].FlipCard();
		}
		ndxFirstClk = -1;
		ndxSecondClk = -1;
	}

	//Game End : All card pairs ard founded
	if (m_pGameScore->GetGameScore() == 16)
		PostQuitMessage(0);

	return 0;
}
