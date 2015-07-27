#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include <vector>
#include "DefineValue.h"

using namespace std;
class CCamera
{
private:	
	// vị trí của camera
	D3DXVECTOR2 _camPosition;
	// ma trận biến đổi tọa độ
	D3DXMATRIX _matrixTransform;
	//
	static CCamera * _instance;

	// vector lưu vị trí path đọc từ file
	vector<D3DXVECTOR2> _paths;

	int _startPathIndex, _endPathIndex;

	float _limitLeft; // giới hạn bên trái
	float _limitRight; // giới hạn bên phải
	float _limitTop; // giới hạn bên trên
	float _limitBottom; // giới hạn bên dưới
public:
	CCamera();
	~CCamera();
	static CCamera * getInstance();
		
	/// <summary>
	/// Sets the camera position.
	/// </summary>
	/// <param name="DXDXVECTOR2">The MegaMan position.</param>
	/// <param name="bool"> is follow MegaMan.</param>
	void setCamPosition(D3DXVECTOR2, bool isFollow = true);
	
	void setLimit(float mapWidth, float mapHeight);

	/// <summary>
	/// chuyen toa do the gioi game sang the gioi thuc.
	/// </summary>
	/// <param name="pos">The position.</param>
	/// <returns> D3DXVECTOR2 </returns>
	D3DXVECTOR2 transform(D3DXVECTOR2 pos);	
	/// <summary>
	/// Gets the viewport.
	/// </summary>
	/// <returns></returns>
	D3DXVECTOR2 getViewportPos();

	RECT getViewport();

	void setPath(vector<D3DXVECTOR2>);

	D3DXVECTOR2 convertCameraPositionOnPath(D3DXVECTOR2 oldposition);
};

