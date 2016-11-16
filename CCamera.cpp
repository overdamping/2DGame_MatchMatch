//-----------------------------------------------------------------------------
//Implementation of the CCamera class
//-----------------------------------------------------------------------------
#include "StdAfx.h"

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
}


INT CCamera::Create(LPDIRECT3DDEVICE9 pDev)
{
	m_vcEye = D3DXVECTOR3(0.0f, 0.0f, 10.0f);
	m_vcLook= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vcUp	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//setting up the projection transformation
	D3DXMatrixPerspectiveFovLH(&m_mtPrj,
		D3DXToRadian(45),							//the horizontal field of view
		(FLOAT)SCREEN_WIDTH / (FLOAT)SCREEN_HEIGHT,	//aspect ratio
		1.0f,										//the near view-plane
		100.0f);									//the far view-plane

	pDev->SetTransform(D3DTS_PROJECTION, &m_mtPrj);

	return 0;
}

void CCamera::GetViewMatrix(D3DXMATRIX * v) const
{
	*v = m_mtViw;
}


INT CCamera::Update()
{
	//if(g_pApp->m_pInput->KeyState(VK_RIGHT))
	//{
	//	m_vcEye.x += 1.f;
	//}

	//if(g_pApp->m_pInput->KeyState(VK_LEFT))
	//{
	//	m_vcEye.x -= 1.f;
	//}

	//if(g_pApp->m_pInput->KeyState(VK_UP))
	//{
	//	m_vcEye.y += 1.f;
	//}

	//if(g_pApp->m_pInput->KeyState(VK_DOWN))
	//{
	//	m_vcEye.y -= 1.f;
	//}

	//setting up the view transformation
	D3DXMatrixLookAtLH(&m_mtViw, 
		&m_vcEye,		//camera position
		&m_vcLook,		//the look-at position
		&m_vcUp);		//the up-direction

	return 0;
}

void CCamera::GetPosition(D3DXVECTOR3 * pos) const
{
	*pos = m_vcEye;
}

void CCamera::SetPosition(const D3DXVECTOR3 * pos)
{
	m_vcEye = *pos;
}

void CCamera::GetUp(D3DXVECTOR3 * up) const
{
	*up = m_vcUp;
}

void CCamera::GetLook(D3DXVECTOR3 * look) const
{
	*look = m_vcLook;
}
