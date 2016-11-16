//-----------------------------------------------------------------------------
//Interface of the CCamera class
//-----------------------------------------------------------------------------
class CCamera
{
public:
	CCamera();
	virtual ~CCamera();

	int		Create(LPDIRECT3DDEVICE9 pDev);
	int		Update();

	void	GetViewMatrix(D3DXMATRIX* v) const;

	void	GetPosition(D3DXVECTOR3* pos) const;
	void	SetPosition(const D3DXVECTOR3* pos);
	void	GetUp(D3DXVECTOR3 *up) const;
	void	GetLook(D3DXVECTOR3* look) const;

private:
	D3DXMATRIX		m_mtViw;		// View Matrix
	D3DXMATRIX		m_mtPrj;		// Projection Matrix

	D3DXVECTOR3		m_vcEye;		// Camera position
	D3DXVECTOR3		m_vcLook;		// Look vector
	D3DXVECTOR3		m_vcUp;			// up vector
};
