#include "PrintScore.h"
#include <graphics.h>
#include "config.h"

void PrintScore(int *kill, int score) {
	int h = 0;
	
	/* 得分 */
	TCHAR* str1 = new TCHAR[128];
	_stprintf_s(str1, 128, _T("得分：%d"), score);
	settextstyle(20, 0, _T("楷体"));
	settextcolor(RED);
	outtextxy(swidth- textwidth(str1), 0, str1);

	h += textheight(str1);

	/* 击杀数 */
	TCHAR str[5][128];
	for (int i = 0; i < 5; i++) {
		if (kill[i] > 0) {
			switch (i) {
			case 0:
				_stprintf_s(str[i], 128, _T("Normal: %d"), kill[i]);
				break;
			case 1:
				_stprintf_s(str[i], 128, _T("Mid: %d"), kill[i]);
				break;
			case 2:
				_stprintf_s(str[i], 128, _T("Mini: %d"), kill[i]);
				break;
			case 3:
				_stprintf_s(str[i], 128, _T("Giant: %d"), kill[i]);
				break;
			case 4:
				_stprintf_s(str[i], 128, _T("Boss: %d"), kill[i]);
				break;
			}
			outtextxy(swidth - textwidth(str[i]), h, str[i]);
			h += textheight(str1);
		}
	}
}
