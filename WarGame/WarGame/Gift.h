#pragma once

#include <graphics.h>
#include "EnemyPlane.h"
#include "config.h"


/* 道具 */
class Gift {
public:
	Gift(IMAGE& img, int x)
		:img(img), isDead(false), gift_speed(GIFT_SPEED)
	{
		rect.left = x;
		rect.right = x + img.getwidth();
		rect.top = -img.getheight();
		rect.bottom = 0;
	}

	bool Show() {
		if (isDead) return true;
		if (rect.top >= sheight) return false;// 道具已经飞出屏幕
		rect.top += gift_speed;
		rect.bottom += gift_speed;
		transparentimage(NULL, rect.left, rect.top, &img, WHITE | BLACK);

		return true;
	}

	RECT& GetRect() {
		return rect;
	}

	void Dies() {
		isDead = true;
	}

protected:
	IMAGE& img;
	RECT rect;
	bool isDead;
	int gift_speed;
};
