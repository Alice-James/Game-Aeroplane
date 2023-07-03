#pragma once

#include <graphics.h>
#include "config.h"
#include "transparentimage.h"


/* 英雄飞机 */
class Hero {
public:
	Hero(IMAGE& img)
		:img(img), lives(HP)
	{
		rect.left = swidth / 2 - img.getwidth() / 2;// getwidth()返回 IMAGE 对象的宽度，以像素为单位。详情：https://docs.easyx.cn/zh-cn/image
		rect.right = rect.left + img.getwidth();
		rect.top = sheight - img.getheight();
		rect.bottom = sheight;
	}

	void Show() {
		transparentimage(NULL, rect.left, rect.top, &img, BLACK);

		setlinecolor(GREEN);
		setlinestyle(PS_SOLID, 5);
		line(rect.left, rect.top - img.getheight() / 8, rect.left + (img.getwidth() / HP * lives), rect.top - img.getheight() / 8);
	}

	void Control() {// 用鼠标控制英雄飞机
		ExMessage msg;// ExMessage结构体用于保存鼠标消息，详情：https://docs.easyx.cn/zh-cn/exmessage
		// peekmessage()函数用于获取一个消息，并立即返回。详情：https://docs.easyx.cn/zh-cn/peekmessage
		// 使用非阻塞函数peekmessage()而不是阻塞函数getmessage()，因为即使不操控英雄飞机，背景图和敌机也要移动
		if (peekmessage(&msg, EX_MOUSE)) {// peekmessage()是否获取到了鼠标信息
			rect.left = msg.x - img.getwidth() / 2;
			rect.right = rect.left + img.getwidth();
			rect.top = msg.y - img.getheight() / 2;
			rect.bottom = rect.top + img.getheight();
		}
	}

	RECT& GetRect() {
		return rect;
	}

	bool hurt() {
		lives--;
		return (lives <= 0) ? false : true;
	}
	bool hurt(int x) {
		lives -= x;
		return (lives <= 0) ? false : true;
	}

	void heal() {
		lives++;
	}

private:
	IMAGE& img;
	RECT rect;// 用矩形边框判断是否相撞

	int lives;
};
