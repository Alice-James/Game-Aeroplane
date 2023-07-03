#include "Over.h"
#include <graphics.h>
#include "config.h"

void Over(int kill) {
	TCHAR* str = new TCHAR[128];
	_stprintf_s(str, 128, _T("击杀数：%d"), kill);

	settextcolor(RED);
	outtextxy(swidth / 2 - textwidth(str) / 2, sheight / 5, str);

	// 获取键盘事件（按Enter返回）
	settextstyle(40, 0, _T("黑体"));
	settextcolor(BLACK);
	outtextxy(swidth / 2 - textwidth(_T("按Enter返回")) / 2, sheight / 2, _T("按Enter返回"));

	while (true) {
		ExMessage msg;
		getmessage(&msg, EX_KEY);// 获取按键消息
		if (msg.vkcode == 0x0D) {// vkcode是按键的虚拟键码，0x0D是Enter键对应的value。详情：https://docs.easyx.cn/zh-cn/exmessage
			return;
		}
	}
}

void Over(int kill, bool flag) {
	TCHAR* str = new TCHAR[128];
	_stprintf_s(str, 128, (flag ? _T("WIN") : _T("LOST")), kill);

	settextstyle(120, 120, _T("黑体"));
	settextcolor(RED);
	outtextxy(swidth / 2 - textwidth(str) / 2, sheight / 5, str);

	TCHAR* str1 = new TCHAR[128];
	_stprintf_s(str1, 128, _T("击杀数：%d"), kill);

	settextstyle(40, 0, _T("楷体"));
	settextcolor(RED);
	outtextxy(swidth / 2 - textwidth(str1) / 2, sheight / 5 * 2, str1);

	// 获取键盘事件（按Enter返回）
	settextstyle(40, 0, _T("楷体"));
	settextcolor(BLACK);
	outtextxy(swidth / 2 - textwidth(_T("按Enter返回")) / 2, sheight / 5 * 3, _T("按Enter返回"));

	while (true) {
		ExMessage msg;
		getmessage(&msg, EX_KEY);// 获取按键消息
		if (msg.vkcode == 0x0D) {// vkcode是按键的虚拟键码，0x0D是Enter键对应的value。详情：https://docs.easyx.cn/zh-cn/exmessage
			return;
		}
	}
}

void Over(int *kill, int score) {
	settextstyle(40, 0, _T("楷体"));

	/* 得分 */
	TCHAR* str_1 = new TCHAR[128];
	_stprintf_s(str_1, 128, _T("得分：%d"), score);
	settextcolor(RED);
	outtextxy(swidth / 2 - textwidth(str_1) / 2, sheight / 5, str_1);

	/* 击杀数 */
	TCHAR* str_2 = new TCHAR[128];
	_stprintf_s(str_2, 128, _T("击杀数：%d"), kill[0] + kill[1] + kill[2] + kill[3] + kill[4]);
	settextcolor(RED);
	outtextxy(swidth / 2 - textwidth(str_2) / 2, sheight / 5 * 2, str_2);

	// 获取键盘事件（按Enter返回）
	settextstyle(40, 0, _T("黑体"));
	settextcolor(BLACK);
	outtextxy(swidth / 2 - textwidth(_T("按Enter返回")) / 2, sheight / 5 * 3, _T("按Enter返回"));

	while (true) {
		ExMessage msg;
		getmessage(&msg, EX_KEY);// 获取按键消息
		if (msg.vkcode == 0x0D) {// vkcode是按键的虚拟键码，0x0D是Enter键对应的value。详情：https://docs.easyx.cn/zh-cn/exmessage
			return;
		}
	}
}

void Over(int *kill, int score, bool flag) {
	/* 胜负 */
	TCHAR* str = new TCHAR[128];
	_stprintf_s(str, 128, (flag ? _T("WIN") : _T("LOST")), kill);
	settextstyle(120, 120, _T("黑体"));
	settextcolor(RED);
	outtextxy(swidth / 2 - textwidth(str) / 2, sheight / 7, str);

	/* 得分 */
	TCHAR* str_1 = new TCHAR[128];
	_stprintf_s(str_1, 128, _T("得分：%d"), score);
	settextstyle(40, 0, _T("楷体"));
	settextcolor(RED);
	outtextxy(swidth / 2 - textwidth(str_1) / 2, sheight / 7 * 2, str_1);

	/* 击杀数 */
	TCHAR* str_2 = new TCHAR[128];
	_stprintf_s(str_2, 128, _T("击杀数：%d"), kill[0] + kill[1] + kill[2] + kill[3] + kill[4]);
	settextstyle(40, 0, _T("楷体"));
	settextcolor(RED);
	outtextxy(swidth / 2 - textwidth(str_2) / 2, sheight / 7 * 3, str_2);

	// 获取键盘事件（按Enter返回）
	settextstyle(40, 0, _T("黑体"));
	settextcolor(BLACK);
	outtextxy(swidth / 2 - textwidth(_T("按Enter返回")) / 2, sheight / 7 * 4, _T("按Enter返回"));

	while (true) {
		ExMessage msg;
		getmessage(&msg, EX_KEY);// 获取按键消息
		if (msg.vkcode == 0x0D) {// vkcode是按键的虚拟键码，0x0D是Enter键对应的value。详情：https://docs.easyx.cn/zh-cn/exmessage
			return;
		}
	}
}
