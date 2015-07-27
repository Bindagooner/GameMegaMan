#include "Camera.h"

CCamera* CCamera::_instance = NULL;

CCamera::CCamera()
{
	D3DXMatrixIdentity(&_matrixTransform);
	_matrixTransform._22 = -1;
	this->setCamPosition(D3DXVECTOR2(0, (float)SCREEN_HEIGHT));
}


CCamera::~CCamera()
{
	if (_instance != NULL) _instance == NULL;
}

CCamera* CCamera::getInstance()
{
	if (_instance == NULL)
		_instance = new CCamera();
	return _instance;
}

void CCamera::setCamPosition(D3DXVECTOR2 pos, bool isFollow)
{
	//if (isFollow)
	//{
	//	_camPosition.x = pos.x - SCREEN_WIDTH / 2.0f;
	//	_camPosition.y = pos.y + SCREEN_HEIGHT / 2.0f;
	//}
	//else
	//{
	//	_camPosition.x = pos.x;
	//	_camPosition.y = pos.y;
	//}


	//// Xác định lại vị trí viewport nếu ra khỏi biên.
	//_camPosition.x = _camPosition.x >= _limitLeft ? _camPosition.x : _limitLeft;
	//_camPosition.x = _camPosition.x >= _limitRight ? _limitRight : _camPosition.x;
	//_camPosition.y = _camPosition.y >= _limitBottom ? _camPosition.y : _limitBottom;
	//_camPosition.y = _camPosition.y >= _limitTop ? _limitTop : _camPosition.y;

	//// Cập nhật lại biên trái và dưới, để megaman ko thể đi lùi.
	//_limitLeft = _camPosition.x;
	//_limitBottom = _camPosition.y;

	/*_camPosition.x = pos.x - SCREEN_WIDTH / 2;
	if (_camPosition.x < 0) _camPosition.x = 0;
	_camPosition.y = pos.y + SCREEN_HEIGHT / 2.0f;*/

	//// Xác định lại vị trí viewport nếu ra khỏi biên.
	//_camPosition.x = _camPosition.x >= _limitLeft ? _camPosition.x : _limitLeft;
	//_camPosition.x = _camPosition.x >= _limitRight ? _limitRight : _camPosition.x;
	//_camPosition.y = _camPosition.y >= _limitBottom ? _camPosition.y : _limitBottom;
	//_camPosition.y = _camPosition.y >= _limitTop ? _limitTop : _camPosition.y;

	//// Cập nhật lại biên trái và dưới, để megaman ko thể đi lùi.
	//_limitLeft = _camPosition.x;
	//_limitBottom = _camPosition.y;

	// không cho di chuyển ra màn hình
	_camPosition = convertCameraPositionOnPath(pos);

	// xac dinh ma tran bien doi
	_matrixTransform._41 = -_camPosition.x;
	_matrixTransform._42 = _camPosition.y;
}

D3DXVECTOR2 CCamera::transform(D3DXVECTOR2 pos)
{
	D3DXVECTOR4 result;	
	D3DXVec3Transform(&result, &D3DXVECTOR3(pos.x, pos.y, 0.0f), &_matrixTransform);
	return D3DXVECTOR2(static_cast<int>(result.x), static_cast<int>(result.y));
}

D3DXVECTOR2 CCamera::getViewportPos()
{
	return _camPosition;
}

RECT CCamera::getViewport()
{
	RECT rs;
	rs.left = _camPosition.x;
	rs.top = _camPosition.y;
	rs.right = rs.left + SCREEN_WIDTH;
	rs.bottom = rs.top - SCREEN_HEIGHT;
	return rs;
}

void CCamera::setLimit(float mapWidth, float mapHeight)
{
	_limitLeft = 0;
	_limitRight = mapWidth - SCREEN_WIDTH;
	_limitBottom = SCREEN_HEIGHT;
	_limitTop = mapHeight >= SCREEN_HEIGHT ? mapHeight : SCREEN_HEIGHT;
}

void CCamera::setPath(vector<D3DXVECTOR2> paths)
{
	_paths = paths;
	if (paths.size() == 0)
	{
		_startPathIndex = _endPathIndex = -1;
		return;
	}
	_startPathIndex = 0;
	_endPathIndex = paths.size() == 1 ? 0 : 1;
	return;
}

D3DXVECTOR2 CCamera::convertCameraPositionOnPath(D3DXVECTOR2 oldPosition)
{
	if (_paths.size() == 0)
		return oldPosition;
	if (_startPathIndex == _endPathIndex)
		return D3DXVECTOR2(_paths[_startPathIndex].x - SCREEN_WIDTH / 2, _paths[_startPathIndex].y + SCREEN_HEIGHT / 2);
	//Nếu hướng di chuyển mở rộng chiều ngang
	if (abs(_paths[_endPathIndex].x - _paths[_startPathIndex].x) > 0)
	{
		// Trường hợp di chuyển trong vùng tâm
		if (oldPosition.x > _paths[_startPathIndex].x  && oldPosition.x < _paths[_endPathIndex].x)
			return D3DXVECTOR2(oldPosition.x - SCREEN_WIDTH / 2, _paths[_startPathIndex].y + SCREEN_HEIGHT / 2);

		// Kiểm tra di chuyển tại _startPathIndex
		if (oldPosition.x <= _paths[_startPathIndex].x)
		{
			// Nếu _startPathIndex = 0 thì không di chuyển camera
			if (_startPathIndex <= 0)
			{
				_startPathIndex = 0;
				return D3DXVECTOR2(_paths[0].x - SCREEN_WIDTH / 2, _paths[0].y + SCREEN_HEIGHT / 2);
			}

			if (_paths[_startPathIndex - 1].y>_paths[_startPathIndex].y)
			{
				if (oldPosition.y >= _paths[_startPathIndex].y&& oldPosition.y <= _paths[_startPathIndex].y + SCREEN_HEIGHT / 2)
					return D3DXVECTOR2(_paths[_startPathIndex].x - SCREEN_WIDTH / 2, oldPosition.y + SCREEN_HEIGHT / 2);
				if (oldPosition.y<_paths[_startPathIndex].y)
					return D3DXVECTOR2(_paths[_startPathIndex].x - SCREEN_WIDTH / 2, _paths[_startPathIndex].y + SCREEN_HEIGHT / 2);
				if (oldPosition.y>_paths[_startPathIndex].y + SCREEN_HEIGHT / 2)
				{
					_endPathIndex = _startPathIndex;
					_startPathIndex = _endPathIndex - 1;
					return convertCameraPositionOnPath(oldPosition);
				}
			}
			else
			{
				if (oldPosition.y <= _paths[_startPathIndex].y&& oldPosition.y >= _paths[_startPathIndex].y + SCREEN_HEIGHT / 2)
					return D3DXVECTOR2(_paths[_startPathIndex].x - SCREEN_WIDTH / 2, oldPosition.y + SCREEN_HEIGHT / 2);
				if (oldPosition.y > _paths[_startPathIndex].y)
					return D3DXVECTOR2(_paths[_startPathIndex].x - SCREEN_WIDTH / 2, _paths[_startPathIndex].y + SCREEN_HEIGHT / 2);
				if (oldPosition.y<_paths[_startPathIndex].y + SCREEN_HEIGHT / 2)
				{
					_endPathIndex = _startPathIndex;
					_startPathIndex = _endPathIndex - 1;
					return convertCameraPositionOnPath(oldPosition);
				}
			}
		}

		// Kiểm tra di chuyển tại _endPathIndex
		if (oldPosition.x >= _paths[_endPathIndex].x)
		{
			// Nếu _endPathIndex = _paths.size()-1 thì không di chuyển camera
			if (_endPathIndex >= _paths.size() - 1)
			{
				_endPathIndex = _paths.size() - 1;
				return D3DXVECTOR2(_paths[_paths.size() - 1].x - SCREEN_WIDTH / 2, _paths[_paths.size() - 1].y + SCREEN_HEIGHT / 2);
			}

			if (_paths[_endPathIndex + 1].y > _paths[_endPathIndex].y)
			{
				if (oldPosition.y >= _paths[_endPathIndex].y&& oldPosition.y <= _paths[_endPathIndex].y + SCREEN_HEIGHT / 2)
					return D3DXVECTOR2(_paths[_endPathIndex].x - SCREEN_WIDTH / 2, oldPosition.y + SCREEN_HEIGHT / 2);
				if (oldPosition.y<_paths[_endPathIndex].y)
					return D3DXVECTOR2(_paths[_endPathIndex].x - SCREEN_WIDTH / 2, _paths[_endPathIndex].y + SCREEN_HEIGHT / 2);
				if (oldPosition.y>_paths[_endPathIndex].y + SCREEN_HEIGHT / 2)
				{
					_startPathIndex = _endPathIndex;
					_endPathIndex = _startPathIndex + 1;
					return convertCameraPositionOnPath(oldPosition);
				}
			}
			else
			{
				if (oldPosition.y <= _paths[_endPathIndex].y&& oldPosition.y >= _paths[_endPathIndex].y + SCREEN_HEIGHT / 2)
					return D3DXVECTOR2(_paths[_endPathIndex].x - SCREEN_WIDTH / 2, oldPosition.y + SCREEN_HEIGHT / 2);
				if (oldPosition.y > _paths[_endPathIndex].y)
					return D3DXVECTOR2(_paths[_endPathIndex].x - SCREEN_WIDTH / 2, _paths[_endPathIndex].y + SCREEN_HEIGHT / 2);
				if (oldPosition.y < _paths[_endPathIndex].y + SCREEN_HEIGHT / 2)
				{
					_startPathIndex = _endPathIndex;
					_endPathIndex = _startPathIndex + 1;
					return convertCameraPositionOnPath(oldPosition);
				}
			}
		}
	}
	// Nếu như hướng di chuyển mở rộng chiều dọc
	if (abs(_paths[_endPathIndex].y - _paths[_startPathIndex].y) > 0)
	{
#pragma region Nếu chiều dọc đi lên

		if (_paths[_endPathIndex].y > _paths[_startPathIndex].y)
		{
			// Trường hợp di chuyển trong vùng tâm
			if (oldPosition.y < _paths[_endPathIndex].y  && oldPosition.y > _paths[_startPathIndex].y)
				return D3DXVECTOR2(_paths[_startPathIndex].x - SCREEN_WIDTH / 2, oldPosition.y + SCREEN_HEIGHT / 2);

			// Kiểm tra di chuyển tại _startPathIndex
			if (oldPosition.y <= _paths[_startPathIndex].y)
			{
				// Nếu _startPathIndex = 0 thì không di chuyển camera
				if (_startPathIndex <= 0)
				{
					_startPathIndex = 0;
					return D3DXVECTOR2(_paths[0].x - SCREEN_WIDTH / 2, _paths[0].y + SCREEN_HEIGHT / 2);
				}

				if (oldPosition.x <= _paths[_startPathIndex].x&& oldPosition.x >= _paths[_startPathIndex].x - SCREEN_WIDTH / 2)
					return D3DXVECTOR2(oldPosition.x - SCREEN_WIDTH / 2, _paths[_startPathIndex].y + SCREEN_HEIGHT / 2);
				if (oldPosition.x > _paths[_startPathIndex].x)
					return D3DXVECTOR2(_paths[_startPathIndex].x - SCREEN_WIDTH / 2, _paths[_startPathIndex].y + SCREEN_HEIGHT / 2);
				if (oldPosition.x<_paths[_startPathIndex].x - SCREEN_WIDTH / 2)
				{
					_endPathIndex = _startPathIndex;
					_startPathIndex = _endPathIndex - 1;
					return convertCameraPositionOnPath(oldPosition);
				}
			}

			// Kiểm tra di chuyển tại _endPathIndex
			if (oldPosition.y >= _paths[_endPathIndex].y)
			{
				// Nếu _endPathIndex = _paths.size()-1 thì không di chuyển camera
				if (_endPathIndex >= _paths.size() - 1)
				{
					_endPathIndex = _paths.size() - 1;
					return D3DXVECTOR2(_paths[_paths.size() - 1].x - SCREEN_WIDTH / 2, _paths[_paths.size() - 1].y + SCREEN_HEIGHT / 2);
				}

				if (oldPosition.x >= _paths[_endPathIndex].x&& oldPosition.x <= _paths[_endPathIndex].x + SCREEN_WIDTH / 2)
					return D3DXVECTOR2(oldPosition.x - SCREEN_WIDTH / 2, _paths[_endPathIndex].y + SCREEN_HEIGHT / 2);
				if (oldPosition.x<_paths[_endPathIndex].x)
					return D3DXVECTOR2(_paths[_endPathIndex].x - SCREEN_WIDTH / 2, _paths[_endPathIndex].y + SCREEN_HEIGHT / 2);
				if (oldPosition.x>_paths[_endPathIndex].x + SCREEN_WIDTH / 2)
				{
					_startPathIndex = _endPathIndex;
					_endPathIndex = _startPathIndex + 1;
					return convertCameraPositionOnPath(oldPosition);
				}
			}
		}

#pragma endregion
#pragma region Nếu chiều dọc đi xuống

		else
		{
			// Trường hợp di chuyển trong vùng tâm
			if (oldPosition.y < _paths[_startPathIndex].y  && oldPosition.y > _paths[_endPathIndex].y)
				return D3DXVECTOR2(_paths[_startPathIndex].x - SCREEN_WIDTH / 2, oldPosition.y + SCREEN_HEIGHT / 2);

			// Kiểm tra di chuyển tại _startPathIndex
			if (oldPosition.y >= _paths[_startPathIndex].y)
			{
				// Nếu _startPathIndex = 0 thì không di chuyển camera
				if (_startPathIndex <= 0)
				{
					_startPathIndex = 0;
					return D3DXVECTOR2(_paths[0].x - SCREEN_WIDTH / 2, _paths[0].y + SCREEN_HEIGHT / 2);
				}

				if (oldPosition.x <= _paths[_startPathIndex].x&& oldPosition.x >= _paths[_startPathIndex].x - SCREEN_WIDTH / 2)
					return D3DXVECTOR2(oldPosition.x - SCREEN_WIDTH / 2, _paths[_startPathIndex].y + SCREEN_HEIGHT / 2);
				if (oldPosition.x>_paths[_startPathIndex].x)
					return D3DXVECTOR2(_paths[_startPathIndex].x - SCREEN_WIDTH / 2, _paths[_startPathIndex].y + SCREEN_HEIGHT / 2);
				if (oldPosition.x<_paths[_startPathIndex].x - SCREEN_WIDTH / 2)
				{
					_endPathIndex = _startPathIndex;
					_startPathIndex = _endPathIndex - 1;
					return convertCameraPositionOnPath(oldPosition);
				}
			}

			// Kiểm tra di chuyển tại _endPathIndex
			if (oldPosition.y <= _paths[_endPathIndex].y)
			{
				// Nếu _endPathIndex = _paths.size()-1 thì không di chuyển camera
				if (_endPathIndex >= _paths.size() - 1)
				{
					_endPathIndex = _paths.size() - 1;
					return D3DXVECTOR2(_paths[_paths.size() - 1].x - SCREEN_WIDTH / 2, _paths[_paths.size() - 1].y + SCREEN_HEIGHT / 2);
				}

				if (oldPosition.x >= _paths[_endPathIndex].x&& oldPosition.x <= _paths[_endPathIndex].x + SCREEN_WIDTH / 2)
					return D3DXVECTOR2(oldPosition.x - SCREEN_WIDTH / 2, _paths[_endPathIndex].y + SCREEN_HEIGHT / 2);
				if (oldPosition.x<_paths[_endPathIndex].x)
					return D3DXVECTOR2(_paths[_endPathIndex].x - SCREEN_WIDTH / 2, _paths[_endPathIndex].y + SCREEN_HEIGHT / 2);
				if (oldPosition.x>_paths[_endPathIndex].x + SCREEN_WIDTH / 2)
				{
					_startPathIndex = _endPathIndex;
					_endPathIndex = _startPathIndex + 1;
					return convertCameraPositionOnPath(oldPosition);
				}
			}
		}

#pragma endregion
	}
}