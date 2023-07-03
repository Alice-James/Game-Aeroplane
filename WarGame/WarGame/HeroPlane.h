#pragma once

#include <graphics.h>
#include "config.h"
#include "transparentimage.h"


/* Ӣ�۷ɻ� */
class Hero {
public:
	Hero(IMAGE& img)
		:img(img), lives(HP)
	{
		rect.left = swidth / 2 - img.getwidth() / 2;// getwidth()���� IMAGE ����Ŀ�ȣ�������Ϊ��λ�����飺https://docs.easyx.cn/zh-cn/image
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

	void Control() {// ��������Ӣ�۷ɻ�
		ExMessage msg;// ExMessage�ṹ�����ڱ��������Ϣ�����飺https://docs.easyx.cn/zh-cn/exmessage
		// peekmessage()�������ڻ�ȡһ����Ϣ�����������ء����飺https://docs.easyx.cn/zh-cn/peekmessage
		// ʹ�÷���������peekmessage()��������������getmessage()����Ϊ��ʹ���ٿ�Ӣ�۷ɻ�������ͼ�͵л�ҲҪ�ƶ�
		if (peekmessage(&msg, EX_MOUSE)) {// peekmessage()�Ƿ��ȡ���������Ϣ
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
	RECT rect;// �þ��α߿��ж��Ƿ���ײ

	int lives;
};
