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
	BOOL Equals(const CCard* card) const;
	const CUSTOMVERTEX* GetQuadVertices();

public:
	BOOL isfound;
	BOOL isFlipped;
private:
	int m_cardID;
	CGameTexture* m_pFrontFace;
	CGameTexture* m_pBackFace;
	TexQuad card;
};

