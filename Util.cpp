#pragma once
#include "StdAfx.h"

Ray CalcPickingRay(int screen_x, int screen_y)
{
	Ray ray;

	float px = 0.0f;
	float py = 0.0f;

	//get viewport
	D3DVIEWPORT9 vp;
	GDEVICE->GetViewport(&vp);

	//get projection matrix
	D3DXMATRIX MatProj;
	GDEVICE->GetTransform(D3DTS_PROJECTION, &MatProj);

	px = ((2.0f*screen_x) / vp.Width) - 1.0f;
	py = (((2.0f*(float)screen_y) / vp.Height) - 1.0f)*-1.0f;
	px = px / MatProj._11;
	py = py / MatProj._22;

	ray._direction = D3DXVECTOR3(px, py, 1.0f);

	//get the inverse of the view matrix
	D3DXMATRIX viewMat, inverseViewMatrix;
	GCAMERA->GetViewMatrix(&viewMat);
	D3DXMatrixInverse(&inverseViewMatrix, 0, &viewMat);

	//calculate the direction of the picking ray in world space
	D3DXVec3TransformNormal(
		&ray._direction,
		&ray._direction,
		&inverseViewMatrix);

	//get the origin of the picking ray(which is the position of the camera) in world space
	GCAMERA->GetPosition(&ray._origin);

	//normalize the ray direction
	D3DXVec3Normalize(&ray._direction, &ray._direction);

	return ray;
}

bool RayQuadIntersectionTest(Ray r, const CUSTOMVERTEX* quadVertices)
{
	bool res = D3DXIntersectTri(&quadVertices[0]._pos, &quadVertices[1]._pos, &quadVertices[2]._pos, &r._origin, &r._direction, nullptr, nullptr, nullptr);
	res = res || D3DXIntersectTri(&quadVertices[2]._pos, &quadVertices[1]._pos, &quadVertices[3]._pos, &r._origin, &r._direction, nullptr, nullptr, nullptr);
	
	return res;
}



