#pragma once

#include <limits>

struct Box
{
	float x, y;             /* Vị trí của box */
	float width, height;    /* Chiều dài và chiều cao của box */
	float vX, vY;           /* Vận tốc của box */
	/*M+==================================================================
	Method:	    Box::Box

	Summary:	Phương thức khởi tạo của lớp box
	==================================================================-M*/
	Box(){

	}

	Box(float x, float y, float w, float h, float vx, float vy)
	{
		this->x = x;
		this->y = y;
		this->width = w;
		this->height = h;
		this->vX = vx;
		this->vY = vy;
	}

	bool isIntersect(Box box)
	{
		bool result = true;
		if (x + width < box.x
			|| box.x + box.width < x
			|| y - height > box.y
			|| box.y - box.height > y)
			result = false;
		return result;
	}
};

class CCollision
{

public:
	
	CCollision();
	~CCollision();	
	/// <summary>
	/// kiểm tra 2 đối tượng có khả năng xảy ra va chạm hay không, trước khi kiểm tra sweepAABB
	/// </summary>
	/// <param name="b1">The box 1.</param>
	/// <param name="b2">The box 2.</param>
	/// <returns></returns>
	static bool checkBeforeAABB(Box b1, Box b2);

	/*M+==================================================================
	Method:	    CCollision::GetSwpetBroadphaseBox

	Summary:	Phương thức tạo ra Broadphase box.
	==================================================================-M*/
	static Box getSweptBroadphaseBox(Box b, float t);
	
	static float SweepAABB(Box b1, Box b2, float& normalx, float& normaly, float timeFrame);
};

