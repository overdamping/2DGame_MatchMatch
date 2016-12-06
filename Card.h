#pragma once

enum ECardState
{
	NOTFOUND_FRONT,
	NOTFOUND_BACK,
	FOUND_FRONT,
};

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
	BOOL IsFound() const;
	void Flip(BOOL st);
	void Found();
	const CUSTOMVERTEX* GetQuadVertices();

private:
	int m_cardID;
	ECardState m_cardSt;
	CGameTexture* m_pFrontFace;
	CGameTexture* m_pBackFace;
	TexQuad m_cardQd;
};

