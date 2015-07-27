#include "QuadNode.h"

using namespace std;

struct IDGreater{
	bool operator()(CGameObject* lx, CGameObject* rx) const {
		return lx->getID() < rx->getID();
	}
};

CQuadNode::CQuadNode()
{
	_pLTNode = NULL;
	_pRTNode = NULL;
	_pLBNode = NULL;
	_pRBNode = NULL;
}

CQuadNode::CQuadNode(int idNode, D3DXVECTOR2 pos, D3DXVECTOR2 size, vector<int> objectIDs, map<int, CGameObject*> &objects)
{
	_pLTNode = NULL;
	_pRTNode = NULL;
	_pLBNode = NULL;
	_pRBNode = NULL;

	_idNode = idNode;
	_posNode = pos;
	_sizeNode = size;

	for (int i = 0; i < objectIDs.size(); i++)
	{
		map<int, CGameObject*>::iterator result;
		result = objects.find(objectIDs[i]);

		if (result != objects.end())
			_listObject.push_back(result->second);
	}
}

CQuadNode::~CQuadNode()
{
	if (_pLTNode)
		delete _pLTNode;
	if (_pRTNode)
		delete _pRTNode;
	if (_pLBNode)
		delete _pLBNode;
	if (_pRBNode)
		delete _pRBNode;
}

void CQuadNode::getObjectInVP(RECT viewport, vector<CGameObject*>* listObject)
{
	Box nodebox = { _posNode.x, _posNode.y, _sizeNode.x, _sizeNode.y, 0.0f, 0.0f };

	Box viewportbox = { (float)viewport.left, (float)viewport.top, (float)abs(viewport.right - viewport.left), (float)abs(viewport.top - viewport.bottom), 0.0f, 0.0f };

	if (nodebox.isIntersect(viewportbox))
	{
		// Nếu không có các node con, thêm các đối tượng hiện tại mà node đang giữ vào listObjects
		if (!this->_pLTNode && !this->_pRTNode && !this->_pLBNode && !this->_pRBNode)
		{
			listObject->insert(listObject->end(), _listObject.begin(), _listObject.end());
			sort(listObject->begin(), listObject->end(), IDGreater());						// Sắp xếp lại các đối tượng
			listObject->erase(std::unique(listObject->begin(), listObject->end()), listObject->end());	// Xóa  các phần tử giống nhau trong danh sách
		}
		else
		{
			this->_pLTNode->getObjectInVP(viewport, listObject);
			this->_pRTNode->getObjectInVP(viewport, listObject);
			this->_pLBNode->getObjectInVP(viewport, listObject);
			this->_pRBNode->getObjectInVP(viewport, listObject);
		}
	}
}

void CQuadNode::addNode(CQuadNode *node)
{
	if (_idNode * 4 + 1 == node->_idNode)
	{
		_pRTNode= node;
		return;
	}
	if (_idNode * 4 + 2 == node->_idNode)
	{
		_pLTNode = node;
		return;
	}
	if (_idNode * 4 + 3 == node->_idNode)
	{
		_pLBNode = node;
		return;
	}
	if (_idNode * 4 + 4 == node->_idNode)
	{
		_pRBNode = node;
		return;
	}
	if (_pRTNode != NULL)
		_pRTNode->addNode(node);

	if (_pRTNode != NULL)
		_pLTNode->addNode(node);

	if (_pRBNode != NULL)
		_pRBNode->addNode(node);

	if (_pLBNode != NULL)
		_pLBNode->addNode(node);
}