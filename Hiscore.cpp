//-----------------------------------------------------------------------------
//Implementation of the CHighScore class
//-----------------------------------------------------------------------------
#include "StdAfx.h"

CHiscore::CHiscore()
{
}


CHiscore::~CHiscore()
{
	Destroy();
}

int CHiscore::Init()
{
	//UI texture creation
	if (FAILED(m_texUIpack.Create(GDEVICE, "texture/uipackSpace_sheet.png")))
		return -1;

	//button texture creation
	if (FAILED(m_texButtons.Create(GDEVICE, "texture/sheet_white2x.png")))
		return -1;

	//setting panels and buttons using xml
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<> * root_node;

	//read the xml file into a vector
	std::ifstream fileUI("texture/uipackSpace_sheet.xml");	
	if (fileUI.fail()) return -1;
	std::vector<char> bufferUI((std::istreambuf_iterator<char>(fileUI)), std::istreambuf_iterator<char>());
	bufferUI.push_back('\0');

	//parse the buffer using the xml file parsing library into doc
	doc.parse<0>(&bufferUI[0]);	
	root_node = doc.first_node("TextureAtlas");	//find our root node

	//iterate over the subtexture
	for (rapidxml::xml_node<> * subtexture_node = root_node->first_node("SubTexture"); subtexture_node; subtexture_node = subtexture_node->next_sibling())
	{
		if (!strcmp(subtexture_node->first_attribute("name")->value(), "metalPanel.png"))
		{
			m_panMetal = Panel(atoi(subtexture_node->first_attribute("x")->value()),
				atoi(subtexture_node->first_attribute("y")->value()),
				atoi(subtexture_node->first_attribute("width")->value()),
				atoi(subtexture_node->first_attribute("height")->value()),
				220, 150);
		}
		if (!strcmp(subtexture_node->first_attribute("name")->value(), "metalPanel_plate.png"))
		{
			m_panPlate = Panel(atoi(subtexture_node->first_attribute("x")->value()),
				atoi(subtexture_node->first_attribute("y")->value()),
				atoi(subtexture_node->first_attribute("width")->value()),
				atoi(subtexture_node->first_attribute("height")->value()),
				240, 205);
		}
	}

	return 0;
}

void CHiscore::Destroy()
{
}

int CHiscore::Render()
{
	if (GSPRITE)
	{
		GSPRITE->Draw(m_texUIpack.GetTexture(), &m_panMetal._srcRect, nullptr, 0, &m_panMetal._pos, &D3DXVECTOR2(2.5f, 3.5f), D3DXCOLOR(1, 1, 1, 1));
		GSPRITE->Draw(m_texUIpack.GetTexture(), &m_panPlate._srcRect, nullptr, 0, &m_panPlate._pos, &D3DXVECTOR2(2.6f, 3.15f), D3DXCOLOR(1, 1, 1, 1));
	}
	else
		return -1;

	RECT rc;
	if (GFONT)
	{
		::SetRect(&rc, 300, 165, 400, 215);
		GFONT->DrawText(NULL, "- ¼øÀ§ -", -1, &rc, 0, D3DXCOLOR(1, 1, 1, 1));
	}
	else
		return -1;

	return 0;
}
