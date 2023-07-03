#pragma once

#include <graphics.h>
#include "config.h"


/* 背景 */
class BG {
public:
	BG(IMAGE& img)
		:img(img), y(-sheight)
	{

	}
	void Show() {
		if (y == 0) y = -sheight;
		y += 2;
		putimage(0, y, &img);// putimage函数用于在当前设备上绘制指定图像，详情：https://docs.easyx.cn/zh-cn/putimage
	}

private:
	IMAGE& img;
	int y;// 纵坐标
};
