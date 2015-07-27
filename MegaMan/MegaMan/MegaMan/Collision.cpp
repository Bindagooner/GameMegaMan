#include "Collision.h"


CCollision::CCollision()
{
}


CCollision::~CCollision()
{
}

Box CCollision::getSweptBroadphaseBox(Box b, float t)
{
	Box broadphaseBox;
	broadphaseBox.x = b.vX > 0 ? b.x : b.x + b.vX * t;
	broadphaseBox.y = b.vY < 0 ? b.y : b.y + b.vY * t;
	broadphaseBox.width = b.vX > 0 ? b.vX * t + b.width : b.width - b.vX * t;
	broadphaseBox.height = b.vY > 0 ? b.vY * t + b.height : b.height - b.vY * t;
	//broadphaseBox.vX = b.vX;
	//broadphaseBox.vY = b.vY;

	return broadphaseBox;

	/*Box re;
	re.x = b.vX > 0 ? b.x : b.x - abs(b.vX)*t;
	re.y = b.vY > 0 ? b.y + abs(b.vY)*t : b.y;
	re.vX = b.vX;
	re.vY = b.vY;
	re.width = b.width + abs(b.vX)*t;
	re.height = b.height + abs(b.vY)*t;

	return re;*/
}

bool CCollision::checkBeforeAABB(Box b1, Box b2)
{
	return !(b1.x + b1.width < b2.x || b1.x > b2.x + b2.width || b1.y < b2.y - b2.height || b1.y - b1.height > b2.y);
}

float CCollision::SweepAABB(Box b1, Box b2, float& normalx, float& normaly, float timeFrame)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// Xác định khoảng cách bắt đầu và kết thúc va chạm theo hay chiều x, y.
	if (b1.vX > 0.0f)
	{
		xInvEntry = b2.x - (b1.x + b1.width);
		xInvExit = (b2.x + b2.width) - b1.x;
	}
	else
	{
		xInvEntry = (b2.x + b2.width) - b1.x;
		xInvExit = b2.x - (b1.x + b1.width);
	}

	if (b1.vY > 0.0f)
	{
		yInvEntry = (b2.y - b2.height) - b1.y;
		yInvExit = b2.y - (b1.y - b1.height);
	}
	else
	{
		yInvEntry = b2.y - (b1.y - b1.height);
		yInvExit = (b2.y - b2.height) - b1.y;
	}

	float xEntry, xExit;
	float yEntry, yExit;

	// Tìm thời gian bắt đầu và kết thúc va chạm theo 2 trục x, y.
	if (b1.vX == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / b1.vX;
		xExit = xInvExit / b1.vX;
	}

	if (b1.vY == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / b1.vY;
		yExit = yInvExit / b1.vY;
	}

	// Kết hợp thời gian bắt đầu và kết thúc va chạm theo 2 trục x, y
	// Tìm thời gian bắt đầu và kết thúc va chạm tổng hợp.
	float entryTime = __max(xEntry, yEntry);
	float exitTime = __min(xExit, yExit);

	// Khi không có va chạm trong frame này.
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > timeFrame || yEntry > timeFrame)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return timeFrame;
	}
	else // Khi xảy ra va chạm.
	{
		// Va chạm theo chiều x.
		if (xEntry > yEntry)
		{
			// Va chạm từ trái qua phải.
			if (b1.vX > 0.0f)
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
			else // Va chạm từ phải qua trái.
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
		}
		else // Va chạm theo chiều y.
		{
			// Va chạm từ dưới lên.
			if (b1.vY > 0.0f)
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
			else // Va chạm từ trên xuống.
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
		}

		//if (entryTime < timeFrame && normalx = -1)
		//{
		//	
		//}

		return entryTime;
	}
}

