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
	RECT GetCardRect();
	void FlipCard();
	BOOL Equals(const CCard* card) const;

public:
	BOOL foundFlag;
private:
	int cardID;
	D3DXVECTOR2 m_cardPos;
	CGameTexture* m_pFrontFace;
	CGameTexture* m_pBackFace;
	BOOL isFlipped;
};

