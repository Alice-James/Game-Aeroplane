#pragma once

#include <graphics.h>
#include "config.h"


/* ���� */
class BG {
public:
	BG(IMAGE& img)
		:img(img), y(-sheight)
	{

	}
	void Show() {
		if (y == 0) y = -sheight;
		y += 2;
		putimage(0, y, &img);// putimage���������ڵ�ǰ�豸�ϻ���ָ��ͼ�����飺https://docs.easyx.cn/zh-cn/putimage
	}

private:
	IMAGE& img;
	int y;// ������
};
