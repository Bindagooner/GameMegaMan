#include "PlayingScreen.h"


CPlayingScreen::CPlayingScreen()
{
	_pMegaMan = new CMegaMan();
	loadMap(1);
}


CPlayingScreen::~CPlayingScreen()
{
}

/// <summary>
/// Loads the map. load map, doc map tu file txt.
/// </summary>
/// <param name="idLevel">The identifier level.</param>
void CPlayingScreen::loadMap(int idLevel)
{
	string mapPath;
	string imagePath;
	switch (idLevel)
	{
	case GUTS_MAN_STAGE_LEVEL:
		mapPath = GUTS_MAN_STAGE_MAP_FILEPATH;
		imagePath = GUTS_MAN_STAGE_MAP_BMP_FILEPATH;
		break;
	case BOOM_MAN_STAGE_LEVEL:
		mapPath = BOOM_MAN_STAGE_MAP_FILEPATH;
		imagePath = BOOM_MAN_STAGE_MAP_BMP_FILEPATH;
	case CUT_MAN_STAGE_LEVEL:
		mapPath = CUT_MAN_STAGE_MAP_FILEPATH;
		imagePath = CUT_MAN_STAGE_MAP_BMP_FILEPATH;
	default:
		break;
	}
	_textureBackground = new CTexture(CDXGraphic::getInstance()->getDevice(), imagePath);

#pragma region Doc file map .txt
	ifstream fs;		// Luồng đọc file map
	string line;		// Chuỗi đọc file map

	fs.open(mapPath, ios::in);
	if (!fs.is_open())
	{
		/*OutputDebugString(L"Can not open map file");*/
		return;
	}

	istringstream iss;								// Luồng string đọc từ file
	int countObj, countNode = 0;					// Số lượng phần tử đối tượng trên màn hình
	map<int, CGameObject*> objects;						// Danh sách các đối tượng trên màn hình
	map<int, CQuadNode*> lstNodes;
	vector<int> objectIDs;							// Danh sách các objectID
	int nodeID, objID, typeID, posX, posY, width, height;	// Các biến lưu giá trị được lưu trữ của một CObject

	getline(fs, line);

	if (line.compare("#Tile_Matrix") == 0)
	{
		getline(fs, line);								// Bỏ qua dòng "Total_Row	Total_Column	Total_Tile"
		getline(fs, line);
		iss.clear();
		iss.str(line);
		iss >> _countRow >> _countColumn >> _totalTile;	// Đẩy giá trị tổng số dòng, cột, tổng số tile vào biến
		getline(fs, line);								// Bỏ qua dòng "#Tile_Matrix_Value"

		//lưu kích thước map
		_mapHeight = _countRow * TILE_SIZE;
		_mapWidth = _countColumn * TILE_SIZE;
		CCamera::getInstance()->setLimit(_mapWidth, _mapHeight);

		// Tạo mảng hai chiều lưu ma trận tile
		for (int i = 0; i < _countRow; i++)
		{
			vector<int> row;
			row.resize(_countColumn);
			_tileMatrix.push_back(row);
		}

		// Tiến hành đọc dữ liệu
		for (int i = 0; i < _countRow; i++)
		{
			getline(fs, line);
			iss.clear();
			iss.str(line);
			for (int j = 0; j < _countColumn; j++)
				iss >> _tileMatrix[i][j];
		}
		getline(fs, line);					// Bỏ qua dòng "#Tile_Matrix_End"
	}

	// Lấy danh sách các đối tượng
	
	getline(fs, line);
	if (line.compare("#Objects") == 0)
	{
		getline(fs, line);					// Bỏ quan dòng "ObjCount"
		getline(fs, line);
		iss.clear();
		iss.str(line);
		iss >> countObj;
		getline(fs, line);					// Bỏ qua dòng "ObjID	TypeID	PosX	PosY	Width	Height"

		// Đọc danh sách các đối tượng
		for (int i = 0; i < countObj; i++)
		{
			getline(fs, line);
			iss.clear();
			iss.str(line);
			iss >> objID >> typeID >> posX >> posY >> width >> height;
			CGameObject* obj;
			switch (typeID)
			{
			case ID_ENEMY_BALL:

				break;
			case ID_ENEMY_BOOM_BLUE:

				break;
			case ID_ENEMY_EYE_RED:

				break;
			case ID_ENEMY_FISH_ORANGE:

				break;
			case ID_ENEMY_INK_RED:

				break;
			case ID_ENEMY_MACHINE_AUTO_GREEN:

				break;
			case ID_ENEMY_MACHINE_ORANGE:

				break;
			case ID_ENEMY_NINJA_GREEN:

				break;
			case ID_ENEMY_BUBLE_BLUE:

				break;
			case ID_ENEMY_CUT:

				break;
			case ID_ENEMY_INK_BLUE:

				break;
			case ID_ENEMY_MACHINE_AUTO_ORGANGE:

				break;
			case ID_ENEMY_ROBOT_RED:

				break;
			case ID_ENEMY_BUBBLE_GREEN:

				break;
			case ID_ENEMY_EVELATOR_LINE_DOWN_GREEN:

				break;
			case ID_ENEMY_EVALATOR_LINE_MIDDLE_GREEN:

				break;
			case ID_ENEMY_EVALATOR_LINE_NORMAL_GREEN:

				break;
			case ID_ENEMY_HAT:

				break;
			case ID_ENEMY_ROBOT_BLUE:

				break;
			case ID_ENEMY_WORKER:

				break;
			case ID_BLOCK:
				obj = new CBlock(objID, typeID, D3DXVECTOR2(width, height), D3DXVECTOR2(posX, posY));
				obj->updateBox();
				break;
			case ID_STAIR:

				break;
			case ID_ITEM_LIFE:

				break;
			case ID_ITEM_BLOOD_BIG:

				break;
			case ID_ITEM_BLOOD_SMALL:

				break;
			case ID_ITEM_MANA:

				break;
			case ID_ITEM_MANA_SMALL:

				break;
			case ID_ROCK:
				break;
			case ID_DIE_ARROW:
				break;
			case ID_FALLING_POINT:
				obj = new CBlock(objID, typeID, D3DXVECTOR2(width, height), D3DXVECTOR2(posX, posY));
				obj->updateBox();
				break;
			}
			objects.insert(pair<int, CGameObject*>(objID, obj));
		}
		getline(fs, line);					// Bỏ qua dòng "#Objects_End"
	}

	// Đọc thông tin ma trận ma chạm

	getline(fs, line);
	if (line.compare("#Quadtree_Collision") == 0)
	{
		getline(fs, line);						// Bỏ qua dòng "NodeCount"
		getline(fs, line);
		iss.clear();
		iss.str(line);
		iss >> countNode;

		getline(fs, line);						// Bỏ qua dòng "NodeID	PosX	PosY	Width	Height	ObjectCount	ObjectIDs"
		for (int i = 0; i < countNode; i++)
		{
			getline(fs, line);
			iss.clear();
			iss.str(line);
			iss >> nodeID >> posX >> posY >> width >> height >> countObj;
			for (int j = 0; j < countObj; j++)
			{
				iss >> objID;
				objectIDs.push_back(objID);
			}
			CQuadNode *tmpNode = new CQuadNode(nodeID, D3DXVECTOR2(posX, posY), D3DXVECTOR2(width, height), objectIDs, objects);
			lstNodes.insert(pair<int, CQuadNode*>(nodeID, tmpNode));
			objectIDs.clear();
		}
	}
	getline(fs, line);							// Bỏ qua dòng "#Quadtree_Collision_End"

	//Đọc thông tin Camera Paths

		getline(fs, line);
	if (line.compare("#Camera_Path_Point") == 0)
	{
		getline(fs, line);
		iss.clear();
		iss.str(line);
		iss >> countNode;		// Đếm số lượng camera path node
		vector<D3DXVECTOR2> cameraPaths;
		for (int i = 0; i < countNode; i++)
		{
			getline(fs, line);
			iss.clear();
			iss.str(line);
			iss >> posX >> posY;
			cameraPaths.push_back(D3DXVECTOR2(posX, posY));
		}
		if (cameraPaths.size()>0)
			CCamera::getInstance()->setPath(cameraPaths);

		getline(fs, line);	// Bỏ qua dòng #Camera_Path_Point_End

		// Set giá trị path cho camera
		CCamera::getInstance()->setCamPosition(D3DXVECTOR2(cameraPaths[0].x + SCREEN_WIDTH / 2, cameraPaths[0].y + SCREEN_HEIGHT / 2));
		_pMegaMan->setPosition(D3DXVECTOR2(cameraPaths[0].x, cameraPaths[0].y + SCREEN_HEIGHT / 2));
	}
	fs.close();

	// Dựng lại cây tứ phân va chạm

	map<int, CQuadNode*>::iterator it;

	for (it = lstNodes.begin(); it != lstNodes.end(); it++)
	{
		if (it == lstNodes.begin())
			_quadNodeCollision = it->second;
		else if (it != lstNodes.end())
			_quadNodeCollision->addNode(it->second);
	}
#pragma endregion

}

void CPlayingScreen::drawBackground(RECT viewport)
{
	int startRow = (int)(viewport.bottom / TILE_SIZE) - 1;
	int endRow = (int)(viewport.top / TILE_SIZE) + 1;
	int startColumn = (int)(viewport.left / TILE_SIZE) - 1;
	int endColumn = (int)(viewport.right / TILE_SIZE) + 2;

	int bitmapColumn = sqrt((double)_totalTile) + 1;

	if (startColumn < 0)
		startColumn = 0;
	if (startRow < 0)
		startRow = 0;
	if (endColumn>_countColumn)
		endColumn = _countColumn;
	if (endRow>_countRow)
		endRow = _countRow;

	for (int i = (_countRow - endRow); i < (_countRow - startRow); i++)
	{
		for (int j = startColumn; j < endColumn; j++)
		{
			int test = _tileMatrix[i][j];
			if (_tileMatrix[i][j] != -1)
			{
				RECT desRect;
				desRect.top = (_tileMatrix[i][j] / bitmapColumn)* TILE_SIZE;
				desRect.left = (_tileMatrix[i][j] % bitmapColumn)*TILE_SIZE;
				desRect.right = desRect.left + TILE_SIZE;
				desRect.bottom = desRect.top + TILE_SIZE;

				D3DXVECTOR2 pos(j*TILE_SIZE + (TILE_SIZE / 2), (_countRow - i)*TILE_SIZE - (TILE_SIZE / 2));
				
				_textureBackground->drawTexture(desRect, pos, D3DCOLOR_XRGB(255, 255, 255));
			}
		}
	}
}

void CPlayingScreen::update(float anim_rate)
{
	//cập nhật vị trí camera
	CCamera::getInstance()->setCamPosition(_pMegaMan->getPos());
	

	// xoa doi tuong trong list
	_objectToCollision.clear();
	_quadNodeCollision->getObjectInVP(CCamera::getInstance()->getViewport(), &_objectToCollision);

	_pMegaMan->update(anim_rate);

	/// Megaman va chạm với các đội tượng trong quad tree
	_pMegaMan->updateCollision(_objectToCollision, anim_rate);

	

}

void CPlayingScreen::draw()
{
	drawBackground(CCamera::getInstance()->getViewport());
	_pMegaMan->draw(0);
}