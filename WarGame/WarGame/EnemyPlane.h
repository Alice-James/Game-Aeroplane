#pragma once

#include <graphics.h>
#include "config.h"
#include "transparentimage.h"
#include "music.h"

/* 敌机 */
class Enemy {
public:
	Enemy(IMAGE& img, int x, IMAGE*& boom)
		:img(img), isDead(false), boomsum(0), ep_speed(EP_SPEED)
	{
		selfboom[0] = boom[0];
		selfboom[1] = boom[1];
		selfboom[2] = boom[2];
		rect.left = x;
		rect.right = x + img.getwidth();
		rect.top = -img.getheight();
		rect.bottom = 0;
	}

	bool Show() {
		if (isDead) {
			if (boomsum == 15)
				return false;
			transparentimage(NULL, rect.left, rect.top, selfboom + boomsum / 5, BLACK);
			boomsum++;

			return true;
		}

		if (rect.top >= sheight) return false;// 敌机已经飞出屏幕
		rect.top += ep_speed;
		rect.bottom += ep_speed;
		transparentimage(NULL, rect.left, rect.top, &img, BLACK);

		return true;
	}

	RECT& GetRect() {
		return rect;
	}

	void Dies() {
		isDead = true;
	}

	bool dying() {
		return isDead;
	}

protected:
	IMAGE& img;
	RECT rect;
	IMAGE selfboom[3];
	bool isDead;
	int boomsum;
	int ep_speed;
};

/* 中型敌机 */
//添加了生命值系统
//添加了血条显示
class midEnemy : public Enemy{
public:
	midEnemy(IMAGE& img, int x, IMAGE*& boom)
		: Enemy(img, x, boom), lives(midEnemyHP), ep_speed(MID_EP_SPEED)
	{
		selfboom[0] = boom[0];
		selfboom[1] = boom[1];
		selfboom[2] = boom[2];
		rect.left = x;
		rect.right = x + img.getwidth();
		rect.top = -img.getheight();
		rect.bottom = 0;
	}

	bool Show() {
		if (isDead) {
			if (boomsum == 15)
				return false;
			transparentimage(NULL, rect.left, rect.top, selfboom + boomsum / 5, BLACK);
			boomsum++;

			return true;
		}

		if (rect.top >= sheight) return false;// 敌机已经飞出屏幕
		rect.top += ep_speed;
		rect.bottom += ep_speed;
		transparentimage(NULL, rect.left, rect.top, &img, BLACK);
		setlinecolor(RED);
		setlinestyle(PS_SOLID, 5);
		line(rect.left, rect.bottom + img.getheight() / 8, rect.left + (img.getwidth() / midEnemyHP * lives), rect.bottom + img.getheight() / 8);

		return true;
	}

	bool hurt() {
		lives--;
		if (lives <= 0) {
			isDead = true;
		}
		return isDead;
	}

	int how_many_lives() {
		return lives;
	}

protected:
	int lives;
	int ep_speed;
};

/* 小型敌机 */
class miniEnemy : public Enemy{
public:
	miniEnemy(IMAGE& img, int x, IMAGE*& boom)
		: Enemy(img, x, boom), ep_speed(MINI_EP_SPEED)
	{
		selfboom[0] = boom[0];
		selfboom[1] = boom[1];
		selfboom[2] = boom[2];
		rect.left = x;
		rect.right = x + img.getwidth();
		rect.top = -img.getheight();
		rect.bottom = 0;
	}

	bool Show() {
		if (isDead) {
			if (boomsum == 15)
				return false;
			transparentimage(NULL, rect.left, rect.top, selfboom + boomsum / 5, BLACK);
			boomsum++;

			return true;
		}

		if (rect.top >= sheight) return false;// 敌机已经飞出屏幕
		rect.top += ep_speed;
		rect.bottom += ep_speed;
		int temp = rand() % 15 * ((rand() % 2) ? 1 : -1);
		rect.left += temp;
		rect.right += temp;
		transparentimage(NULL, rect.left, rect.top, &img, BLACK);

		return true;
	}

protected:
	int ep_speed;
};

/* 大型敌机 */
class giantEnemy : public midEnemy {
public:
	giantEnemy(IMAGE& img, int x, IMAGE*& boom)
		: midEnemy(img, x, boom), lives(giantEnemyHP), ep_speed(GIANT_EP_SPEED)
	{
		selfboom[0] = boom[0];
		selfboom[1] = boom[1];
		selfboom[2] = boom[2];
		rect.left = x;
		rect.right = x + img.getwidth();
		rect.top = -img.getheight();
		rect.bottom = 0;
	}

	bool Show() {
		if (isDead) {
			if (boomsum == 15)
				return false;
			transparentimage(NULL, rect.left, rect.top, selfboom + boomsum / 5, BLACK);
			boomsum++;

			return true;
		}

		if (rect.top >= sheight) return false;// 敌机已经飞出屏幕
		rect.top += ep_speed;
		rect.bottom += ep_speed;
		int temp = rand() % 15 * ((rand() % 2) ? 1 : -1);
		rect.left += temp;
		rect.right += temp;
		transparentimage(NULL, rect.left, rect.top, &img, BLACK);
		setlinecolor(RED);
		setlinestyle(PS_SOLID, 5);
		line(rect.left, rect.bottom + img.getheight() / 8, rect.left + (img.getwidth() / giantEnemyHP * lives), rect.bottom + img.getheight() / 8);

		return true;
	}

	bool hurt() {
		lives--;
		if (lives <= 0)
			isDead = true;
		return isDead;
	}

protected:
	int lives;
	int ep_speed;
};

/* BOSS */
class bossEnemy : public midEnemy {
public:
	bossEnemy(IMAGE& img, int x, IMAGE*& boom)
		: midEnemy(img, x, boom), lives(bossEnemyHP)
	{
		selfboom[0] = boom[0];
		selfboom[1] = boom[1];
		selfboom[2] = boom[2];
		rect.left = x;
		rect.right = x + img.getwidth();
		rect.top = 0;
		rect.bottom = img.getheight();
	}

	bool Show() {
		if (isDead) {
			if (boomsum == 15)
				return false;
			transparentimage(NULL, rect.left, rect.top, selfboom + boomsum / 5, BLACK);
			boomsum++;

			return true;
		}

		if (rect.top >= sheight) return false;// 敌机已经飞出屏幕
		transparentimage(NULL, rect.left, rect.top, &img, BLACK);
		setlinecolor(RED);
		setlinestyle(PS_SOLID, 10);
		line(rect.left, rect.bottom + img.getheight() / 8, rect.left + (img.getwidth() / bossEnemyHP * lives), rect.bottom + img.getheight() / 8);

		return true;
	}

	bool hurt() {
		lives--;
		if (lives <= 0)
			isDead = true;
		return isDead;
	}

protected:
	int lives;
};
