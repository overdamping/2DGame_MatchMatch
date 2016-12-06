//-----------------------------------------------------------------------------
//Implementation of the CEndMenu class
//-----------------------------------------------------------------------------
#include "StdAfx.h"

CEndMenu::CEndMenu()
{
}


CEndMenu::~CEndMenu()
{
	Destroy();
}

int CEndMenu::Init()
{
	//UI texture creation
	if (FAILED(m_texUIpack.Create(GDEVICE, "texture/uipackSpace_sheet.png")))
		return -1;

	//button texture creation
	if (FAILED(m_texButtons.Create(GDEVICE, "texture/sheet_white2x.png")))
		return -1;

	//message creation
	m_strMsg = new char[80];
	memset(m_strMsg, 0, sizeof(m_strMsg));

	//setting panels and buttons using xml
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<> * root_node;

	//read the xml file into a vector
	std::ifstream fileUI("texture/uipackSpace_sheet.xml");
	if (fileUI.fail()) return -1;
	std::vector<char> bufferUI((std::istreambuf_iterator<char>(fileUI)), std::istreambuf_iterator<char>());
	fileUI.close();
	bufferUI.push_back('\0');

	//parse the buffer into doc using xml parsing library 
	doc.parse<0>(&bufferUI[0]);	
	root_node = doc.first_node("TextureAtlas");	//find out root node

	//iterate over the subtextures
	for (rapidxml::xml_node<> * subtexture_node = root_node->first_node("SubTexture"); subtexture_node; subtexture_node = subtexture_node->next_sibling())
	{
		if (!strcmp(subtexture_node->first_attribute("name")->value(), "metalPanel.png"))
		{
			m_panMetal = Panel(atoi(subtexture_node->first_attribute("x")->value()),
				atoi(subtexture_node->first_attribute("y")->value()),
				atoi(subtexture_node->first_attribute("width")->value()),
				atoi(subtexture_node->first_attribute("height")->value()),
				200, 200);
		}
		if (!strcmp(subtexture_node->first_attribute("name")->value(), "metalPanel_plate.png"))
		{
			m_panPlate = Panel(atoi(subtexture_node->first_attribute("x")->value()),
				atoi(subtexture_node->first_attribute("y")->value()),
				atoi(subtexture_node->first_attribute("width")->value()),
				atoi(subtexture_node->first_attribute("height")->value()),
				220, 255);
		}
	}

	//read and parse xml the same way above
	std::ifstream fileBut("texture/sheet_white2x.xml");
	if (fileBut.fail()) return -1;
	std::vector<char> bufferBut((std::istreambuf_iterator<char>(fileBut)), std::istreambuf_iterator<char>());
	fileBut.close();
	bufferBut.push_back('\0');

	doc.parse<0>(&bufferBut[0]);
	root_node = doc.first_node("TextureAtlas");

	for (rapidxml::xml_node<> * subtexture_node = root_node->first_node("SubTexture"); subtexture_node; subtexture_node = subtexture_node->next_sibling())
	{
		if (!strcmp(subtexture_node->first_attribute("name")->value(), "return.png"))
		{
			m_btnNew = Button(atoi(subtexture_node->first_attribute("x")->value()),
				atoi(subtexture_node->first_attribute("y")->value()),
				atoi(subtexture_node->first_attribute("width")->value()),
				atoi(subtexture_node->first_attribute("height")->value()),
				260, 245);
		}
		if (!strcmp(subtexture_node->first_attribute("name")->value(), "leaderboardsComplex.png"))
		{
			m_btnRank = Button(atoi(subtexture_node->first_attribute("x")->value()),
				atoi(subtexture_node->first_attribute("y")->value()),
				atoi(subtexture_node->first_attribute("width")->value()),
				atoi(subtexture_node->first_attribute("height")->value()),
				440, 245);
		}
	}

	return 0;
}

void CEndMenu::Destroy()
{
	delete(m_strMsg);
}

int CEndMenu::ProcessInput()	//process mouse input (left button click)
{
	D3DXVECTOR3 pos = GINPUT->GetCurMousePos();
	POINT pt = {(LONG)pos.x,(LONG)pos.y};

	if (PtInRect(&m_btnNew._btnRect, pt))
		SendMessage(GetActiveWindow(), WM_NEW_GAME, 0, 0);
	else if (PtInRect(&m_btnRank._btnRect, pt))
		SendMessage(GetActiveWindow(), WM_HISCORE, 0, 0);

	return 0;
}

int CEndMenu::Render()
{
	if (GSPRITE)
	{
		GSPRITE->Draw(m_texUIpack.GetTexture(), &m_panMetal._srcRect, nullptr, 0, &m_panMetal._pos, &D3DXVECTOR2(4.0f, 2.0f), D3DXCOLOR(1, 1, 1, 1));
		GSPRITE->Draw(m_texUIpack.GetTexture(), &m_panPlate._srcRect, nullptr, 0, &m_panPlate._pos, &D3DXVECTOR2(4.5f, 1.5f), D3DXCOLOR(1, 1, 1, 1));
		GSPRITE->Draw(m_texButtons.GetTexture(), &m_btnNew._srcRect, nullptr, 0, &m_btnNew._pos, nullptr, D3DXCOLOR(1, 1, 1, 1));
		GSPRITE->Draw(m_texButtons.GetTexture(), &m_btnRank._srcRect, nullptr, 0, &m_btnRank._pos, nullptr, D3DXCOLOR(1, 1, 1, 1));
	}
	else
		return -1;

	RECT rc;
	if (GFONT)
	{
		::SetRect(&rc, 225, 220, 640, 300);
		GFONT->DrawText(NULL, m_strMsg, -1, &rc, 0, D3DXCOLOR(1, 1, 1, 1));
		::SetRect(&rc, 270, 340, 370, 370);
		GFONT->DrawText(NULL, "새 게임", -1, &rc, 0, D3DXCOLOR(1, 1, 1, 1));
		::SetRect(&rc, 465, 340, 565, 370);
		GFONT->DrawText(NULL, "순위", -1, &rc, 0, D3DXCOLOR(1, 1, 1, 1));
	}
	else
		return -1;
	return 0;
}

void CEndMenu::SetFinalScore(int score)
{
	char strbuf[80] = "축하합니다! 당신의 점수는 ";
	char scrBuf[20];
	_itoa_s(score, scrBuf, 20, 10);
	strcat_s(strbuf, 80, scrBuf);
	strcat_s(strbuf, 80, "점");
	strcpy_s(m_strMsg, 80, strbuf);
}
