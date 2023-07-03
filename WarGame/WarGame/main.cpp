// 飞机大战
#include <iostream>
#include <graphics.h>// Easyx头文件，详情：https://docs.easyx.cn/zh-cn/intro
#include "Welcome.h"
#include "PointInRect.h"
#include "config.h"
#include "Play.h"
#include <conio.h>
#include "Select.h"

using namespace std;


int main() {
	// 初始化绘图窗口, 详情：https://docs.easyx.cn/zh-cn/initgraph
	initgraph(swidth, sheight, EX_NOMINIMIZE | EX_SHOWCONSOLE); // 创建一个尺寸为 swidth * sheight 的绘图窗口，同时显示控制台窗口，并禁用绘图窗口的最小化按钮
	bool is_live = true;// 游戏是否在进行
	while (is_live) {
		Welcome();//欢迎界面
		is_live = Play(Select());
	}

	return 0;
}