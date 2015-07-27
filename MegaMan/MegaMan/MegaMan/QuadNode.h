#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include <vector>
#include <algorithm>

#include "GameObject.h"
#include "Collision.h"

using namespace std;
class CQuadNode
{
private:
	int _idNode; // id của node

	D3DXVECTOR2 _posNode; // toa do diem tren trai cua node

	D3DXVECTOR2 _sizeNode; // kich thuoc node

	vector<CGameObject*> _listObject; // danh sach cac doi tuong co trong node

	CQuadNode *_pLTNode;
	CQuadNode *_pRTNode;
	CQuadNode *_pLBNode; 
	CQuadNode *_pRBNode;

public:
	CQuadNode();
	
	/// <summary>
	/// khoi tao Quadnode <see cref="CQuadNode"/> class.
	/// </summary>
	/// <param name="int">The ID node .</param>
	/// <param name="D3DXVECTOR2"> vi tri cua diem trên trái.</param>
	/// <param name="D3DXVECTOR2"> kích thước node.</param>
	/// <param name="vector<int>">The .</param>
	/// <param name="map<int, CGameObject*>">The .</param>
	CQuadNode(int idNode, D3DXVECTOR2 pos, D3DXVECTOR2 size, vector<int> objectIDs,map<int, CGameObject*> &objects);
	~CQuadNode();	
	
	/// <summary>
	/// lấy object từ viewport.
	/// </summary>
	/// <param name="viewport">The viewport.</param>
	/// <param name="listObject">The list object.</param>
	void getObjectInVP(RECT viewport, vector<CGameObject*>* listObject);
	
	/// <summary>
	/// Adds the node.
	/// </summary>
	/// <param name="node">The node.</param>
	void addNode(CQuadNode *node);
};

