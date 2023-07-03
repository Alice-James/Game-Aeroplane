#pragma once

#include <graphics.h>
#include "transparentimage.h"


class Bullet {
public:
	Bullet(IMAGE& img, RECT pr)
		:img(img)
	{
		rect.left = pr.left + (pr.right - pr.left) / 2 - img.getwidth() / 2;
		rect.right = rect.left + img.getwidth();
		rect.top = pr.top - img.getheight();
		rect.bottom = pr.top;
	}

	bool Show() {
		if (rect.bottom <= 0)
			return false;
		rect.top -= BS_SPEED;
		rect.bottom -= BS_SPEED;
		transparentimage(NULL, rect.left, rect.top, &img, BLACK);

		return true;
	}

	RECT& GetRect() {
		return rect;
	}

protected:
	IMAGE& img;
	RECT rect;
};

class EBullet : public Bullet {
public:
	EBullet(IMAGE& img, RECT pr)
		:Bullet(img, pr)
	{
		rect.left = pr.left + (pr.right - pr.left) / 2 - img.getwidth() / 2;
		rect.right = rect.left + img.getwidth();
		rect.top = pr.bottom;
		rect.bottom = rect.top + img.getheight();
	}

	bool Show() {
		if (rect.top >= sheight) return false;
		rect.top += EBS_SPEED;
		rect.bottom += EBS_SPEED;
		transparentimage(NULL, rect.left, rect.top, &img, BLACK);

		return true;
	}
};

class BossSkill_1 : public EBullet {
public:
	BossSkill_1(IMAGE& img, RECT pr)
		:EBullet(img, pr)
	{
		rect.left = pr.left + (pr.right - pr.left) / 2 - img.getwidth() / 2;
		rect.right = rect.left + img.getwidth();
		rect.top = pr.bottom;
		rect.bottom = rect.top + img.getheight();
	}

	bool Show() {
		if (rect.top >= sheight) return false;
		rect.top += EBS_SPEED_BOSS1;
		rect.bottom += EBS_SPEED_BOSS1;
		transparentimage(NULL, rect.left, rect.top, &img, BLACK);

		return true;
	}

};

class BossSkill_2 : public EBullet {
public:
	BossSkill_2(IMAGE& img, RECT pr)
		:EBullet(img, pr)
	{
		rect.left = pr.left + (pr.right - pr.left) / 5 * ((rand() % 2) ? 1 : 4) - img.getwidth() / 2;
		rect.right = rect.left + img.getwidth();
		rect.top = pr.bottom;
		rect.bottom = rect.top + img.getheight();
	}

	bool Show() {
		if (rect.top >= sheight) return false;
		rect.top += EBS_SPEED_BOSS2;
		rect.bottom += EBS_SPEED_BOSS2;
		transparentimage(NULL, rect.left, rect.top, &img, BLACK);

		return true;
	}

};

class BossSkill_3 : public EBullet {
public:
	BossSkill_3(IMAGE& img, RECT pr)
		:EBullet(img, pr)
	{
		rect.left = abs(rand()) % (swidth - img.getwidth());
		rect.right = rect.left + img.getwidth();
		rect.top = pr.bottom;
		rect.bottom = rect.top + img.getheight();
	}

	bool Show() {
		if (rect.top >= sheight) return false;
		rect.top += EBS_SPEED_BOSS3;
		rect.bottom += EBS_SPEED_BOSS3;
		transparentimage(NULL, rect.left, rect.top, &img, BLACK);

		return true;
	}

};

/* 双发子弹(左) */
class Bullet2_1 : public Bullet {
public:
	Bullet2_1(IMAGE& img, RECT pr)
		:Bullet(img, pr)
	{
		rect.left = pr.left + (pr.right - pr.left) / 4 - img.getwidth() / 2;
		rect.right = rect.left + img.getwidth();
		rect.top = pr.top - img.getheight();
		rect.bottom = pr.top;
	}

	bool Show() {
		if (rect.bottom <= 0)
			return false;
		rect.top -= BS_SPEED;
		rect.bottom -= BS_SPEED;
		transparentimage(NULL, rect.left, rect.top, &img, BLACK);

		return true;
	}
};
/* 双发子弹(右) */
class Bullet2_2 : public Bullet {
public:
	Bullet2_2(IMAGE& img, RECT pr)
		:Bullet(img, pr)
	{
		rect.left = pr.left + (pr.right - pr.left) / 4 * 3 - img.getwidth() / 2;
		rect.right = rect.left + img.getwidth();
		rect.top = pr.top - img.getheight();
		rect.bottom = pr.top;
	}

	bool Show() {
		if (rect.bottom <= 0)
			return false;
		rect.top -= BS_SPEED;
		rect.bottom -= BS_SPEED;
		transparentimage(NULL, rect.left, rect.top, &img, BLACK);

		return true;
	}
};

/* 分叉子弹（中） */
class Bullet3_1 : public Bullet {
public:
	Bullet3_1(IMAGE& img, RECT pr)
		:Bullet(img, pr)
	{
		rect.left = pr.left + (pr.right - pr.left) / 2 - img.getwidth() / 2;
		rect.right = rect.left + img.getwidth();
		rect.top = pr.top - img.getheight();
		rect.bottom = pr.top;
	}

	bool Show() {
		if (rect.bottom <= 0)
			return false;
		rect.top -= BS_SPEED;
		rect.bottom -= BS_SPEED;
		transparentimage(NULL, rect.left, rect.top, &img, BLACK);

		return true;
	}
};
/* 分叉子弹（左） */
class Bullet3_2 : public Bullet {
public:
	Bullet3_2(IMAGE& img, RECT pr)
		:Bullet(img, pr)
	{
		rect.left = pr.left + (pr.right - pr.left) / 2 - img.getwidth() / 2;
		rect.right = rect.left + img.getwidth();
		rect.top = pr.top - img.getheight();
		rect.bottom = pr.top;
	}

	bool Show() {
		if (rect.bottom <= 0)
			return false;
		rect.top -= BS_SPEED;
		rect.bottom -= BS_SPEED;
		rect.left -= BS_SPEED_3_2;
		rect.right -= BS_SPEED_3_2;
		transparentimage(NULL, rect.left, rect.top, &img, BLACK);

		return true;
	}
};
/* 分叉子弹（右） */
class Bullet3_3 : public Bullet {
public:
	Bullet3_3(IMAGE& img, RECT pr)
		:Bullet(img, pr)
	{
		rect.left = pr.left + (pr.right - pr.left) / 2 - img.getwidth() / 2;
		rect.right = rect.left + img.getwidth();
		rect.top = pr.top - img.getheight();
		rect.bottom = pr.top;
	}

	bool Show() {
		if (rect.bottom <= 0)
			return false;
		rect.top -= BS_SPEED;
		rect.bottom -= BS_SPEED;
		rect.left += BS_SPEED_3_3;
		rect.right += BS_SPEED_3_3;
		transparentimage(NULL, rect.left, rect.top, &img, BLACK);

		return true;
	}
};

/* 穿甲弹(可以穿透敌机) */
class Bullet4 : public Bullet {
public:
	Bullet4(IMAGE& img, RECT pr)
		:Bullet(img, pr)
	{
		rect.left = pr.left + (pr.right - pr.left) / 2 - img.getwidth() / 2;
		rect.right = rect.left + img.getwidth();
		rect.top = pr.top - img.getheight();
		rect.bottom = pr.top;
	}

	bool Show() {
		if (rect.bottom <= 0)
			return false;
		rect.top -= BS_SPEED;
		rect.bottom -= BS_SPEED;
		transparentimage(NULL, rect.left, rect.top, &img, BLACK);

		return true;
	}
};
