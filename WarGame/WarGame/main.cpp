// �ɻ���ս
#include <iostream>
#include <graphics.h>// Easyxͷ�ļ������飺https://docs.easyx.cn/zh-cn/intro
#include "Welcome.h"
#include "PointInRect.h"
#include "config.h"
#include "Play.h"
#include <conio.h>
#include "Select.h"

using namespace std;


int main() {
	// ��ʼ����ͼ����, ���飺https://docs.easyx.cn/zh-cn/initgraph
	initgraph(swidth, sheight, EX_NOMINIMIZE | EX_SHOWCONSOLE); // ����һ���ߴ�Ϊ swidth * sheight �Ļ�ͼ���ڣ�ͬʱ��ʾ����̨���ڣ������û�ͼ���ڵ���С����ť
	bool is_live = true;// ��Ϸ�Ƿ��ڽ���
	while (is_live) {
		Welcome();//��ӭ����
		is_live = Play(Select());
	}

	return 0;
}