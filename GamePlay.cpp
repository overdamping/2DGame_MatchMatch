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
	//texture creation
	if (FAILED(m_texBackground.Create(GDEVICE, "texture/wood_texture.bmp")))
		return -1;

	m_texCard[0].Create(GDEVICE, "texture/ace.png");
	m_texCard[1].Create(GDEVICE, "texture/castle.png");
	m_texCard[2].Create(GDEVICE, "texture/fishing.png");
	m_texCard[3].Create(GDEVICE, "texture/horus.png");
	m_texCard[4].Create(GDEVICE, "texture/key.png");
	m_texCard[5].Create(GDEVICE, "texture/rocket.png");
	m_texCard[6].Create(GDEVICE, "texture/sniffing-dog.png");
	m_texCard[7].Create(GDEVICE, "texture/wolf-head.png");
	m_texCard[8].Create(GDEVICE, "texture/backFace.png");
	
	//Card objects creation
	CreateCards();

	//setting indices to -1
	ndxFirstClk = -1;
	ndxSecondClk = -1;

	//initialize counters
	cntMatchedPair = 0;
	cntAttemps = 0;

	return 0;
}

void CGamePlay::CreateCards()
{
	std::vector<int> tmpOld = {0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7};
	std::vector<int> tmpNew(0);
	while (!tmpOld.empty())	
	{
		srand((unsigned)time(NULL));
		int ndx = rand() % tmpOld.size();
		tmpNew.insert(tmpNew.end(), tmpOld[ndx]);
		tmpOld.erase(tmpOld.begin()+ndx);
	}

	for (int i = 0; i<16; i++)
	{
		m_cards[i].Create(tmpNew[i],				//card ID
			-2.3 + (i / 4)*(INTERVAL + CARD_WIDTH),	//x position
			-2 + (i % 4)*(INTERVAL + CARD_HEIGHT),	//y position
			&m_texCard[tmpNew[i]],					//front face texture
			&m_texCard[8]);							//back face taxture
	}
}

void CGamePlay::Destroy()
{
}

int CGamePlay::Render()
{
	//backgroud and card rendering 
	if (GSPRITE)
	{
		GSPRITE->Draw(m_texBackground.GetTexture(), &m_texBackground.GetImageRect(), nullptr, 0, nullptr, nullptr, D3DXCOLOR(1, 1, 1, 1));
		for (int ndx = 0; ndx < 16; ndx++)
		{
			if (FAILED(m_cards[ndx].Render()))
				return -1;
		}
	}
	else
		return -1;
	
	//Game Score(attempts) rendering
	RECT rc = {600, 35, 800, 60};
	char strBuf[80] = "Attemps : ";
	char scrBuf[20];
	_itoa_s(cntAttemps, scrBuf, sizeof(scrBuf), 10);
	strcat_s(strBuf, scrBuf);

	if (GFONT)
		GFONT->DrawText(NULL, strBuf, -1, &rc, 0, D3DXCOLOR(1, 1, 1, 1));
	else
		return -1;

	return 0;
}

int CGamePlay::ProcessInput()	//process mouse input (left button click)
{
	D3DXVECTOR3 pos = GINPUT->GetCurMousePos();
	Ray ray = CalcPickingRay(pos.x, pos.y);	//calculate picking ray

	for (int ndx = 0; ndx < 16; ndx++)
	{
		if (RayQuadIntersectionTest(ray, m_cards[ndx].GetQuadVertices()) && !m_cards[ndx].IsFound())
		{
			if (ndxFirstClk == -1)	//first card clicked
			{
				ndxFirstClk = ndx;
				m_cards[ndxFirstClk].Flip(FALSE);
				return 0;
			}
			else
				if (ndxSecondClk == -1 && ndx != ndxFirstClk)	//second card clicked
				{
					ndxSecondClk = ndx;
					m_cards[ndxSecondClk].Flip(FALSE);
					m_fTimeBgn = timeGetTime() * 0.001f;		
					return 0;
				}
		}
	}
	return 0;
}

int CGamePlay::GetGameScore() const
{
	return cntAttemps;
}

int CGamePlay::Update()
{
	//Card pair matching
	if (ndxSecondClk != -1)
	{
		m_fTimeEnd = timeGetTime() * 0.001f;
		if (m_fTimeEnd - m_fTimeBgn >= 0.2)	//delay for 0.2sec after second card clicked
		{
			if (m_cards[ndxFirstClk].Equals(&m_cards[ndxSecondClk]))	//pair matching success
			{
				m_cards[ndxFirstClk].Found();
				m_cards[ndxSecondClk].Found();
				cntMatchedPair++;
			}
			else	//pair matching fail
			{												
				m_cards[ndxFirstClk].Flip(TRUE);
				m_cards[ndxSecondClk].Flip(TRUE);
				cntAttemps++;	//number of attemps incresed
			}
			ndxFirstClk = -1;
			ndxSecondClk = -1;
		}
	}

	//Game won : All card pairs are matched
	if (cntMatchedPair == 8)
		SendMessage(GetActiveWindow(), WM_GAME_WON, cntAttemps, 0);

	return 0;
}
