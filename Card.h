#pragma once

class CCard
{
public:
	CCard();
	~CCard();

	int Create(int id, float posX, float posY, CGameTexture* pFrontFace, CGameTexture* pBackFace);
	int Render();
	void Destroy();
public:
	//RECT GetCardRect() const;
	BOOL Equals(const CCard* card) const;

public:
	BOOL isfound;
	BOOL isFlipped;
private:
	int m_cardID;
	//D3DXVECTOR2 m_cardPos;
	//RECT m_cardRect;
	CGameTexture* m_pFrontFace;
	CGameTexture* m_pBackFace;

	CUSTOMVERTEX vertices[4];	//fix
};

