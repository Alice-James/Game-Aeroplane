#include "Over.h"
#include <graphics.h>
#include "config.h"

void Over(int kill) {
	TCHAR* str = new TCHAR[128];
	_stprintf_s(str, 128, _T("��ɱ����%d"), kill);

	settextcolor(RED);
	outtextxy(swidth / 2 - textwidth(str) / 2, sheight / 5, str);

	// ��ȡ�����¼�����Enter���أ�
	settextstyle(40, 0, _T("����"));
	settextcolor(BLACK);
	outtextxy(swidth / 2 - textwidth(_T("��Enter����")) / 2, sheight / 2, _T("��Enter����"));

	while (true) {
		ExMessage msg;
		getmessage(&msg, EX_KEY);// ��ȡ������Ϣ
		if (msg.vkcode == 0x0D) {// vkcode�ǰ�����������룬0x0D��Enter����Ӧ��value�����飺https://docs.easyx.cn/zh-cn/exmessage
			return;
		}
	}
}

void Over(int kill, bool flag) {
	TCHAR* str = new TCHAR[128];
	_stprintf_s(str, 128, (flag ? _T("WIN") : _T("LOST")), kill);

	settextstyle(120, 120, _T("����"));
	settextcolor(RED);
	outtextxy(swidth / 2 - textwidth(str) / 2, sheight / 5, str);

	TCHAR* str1 = new TCHAR[128];
	_stprintf_s(str1, 128, _T("��ɱ����%d"), kill);

	settextstyle(40, 0, _T("����"));
	settextcolor(RED);
	outtextxy(swidth / 2 - textwidth(str1) / 2, sheight / 5 * 2, str1);

	// ��ȡ�����¼�����Enter���أ�
	settextstyle(40, 0, _T("����"));
	settextcolor(BLACK);
	outtextxy(swidth / 2 - textwidth(_T("��Enter����")) / 2, sheight / 5 * 3, _T("��Enter����"));

	while (true) {
		ExMessage msg;
		getmessage(&msg, EX_KEY);// ��ȡ������Ϣ
		if (msg.vkcode == 0x0D) {// vkcode�ǰ�����������룬0x0D��Enter����Ӧ��value�����飺https://docs.easyx.cn/zh-cn/exmessage
			return;
		}
	}
}

void Over(int *kill, int score) {
	settextstyle(40, 0, _T("����"));

	/* �÷� */
	TCHAR* str_1 = new TCHAR[128];
	_stprintf_s(str_1, 128, _T("�÷֣�%d"), score);
	settextcolor(RED);
	outtextxy(swidth / 2 - textwidth(str_1) / 2, sheight / 5, str_1);

	/* ��ɱ�� */
	TCHAR* str_2 = new TCHAR[128];
	_stprintf_s(str_2, 128, _T("��ɱ����%d"), kill[0] + kill[1] + kill[2] + kill[3] + kill[4]);
	settextcolor(RED);
	outtextxy(swidth / 2 - textwidth(str_2) / 2, sheight / 5 * 2, str_2);

	// ��ȡ�����¼�����Enter���أ�
	settextstyle(40, 0, _T("����"));
	settextcolor(BLACK);
	outtextxy(swidth / 2 - textwidth(_T("��Enter����")) / 2, sheight / 5 * 3, _T("��Enter����"));

	while (true) {
		ExMessage msg;
		getmessage(&msg, EX_KEY);// ��ȡ������Ϣ
		if (msg.vkcode == 0x0D) {// vkcode�ǰ�����������룬0x0D��Enter����Ӧ��value�����飺https://docs.easyx.cn/zh-cn/exmessage
			return;
		}
	}
}

void Over(int *kill, int score, bool flag) {
	/* ʤ�� */
	TCHAR* str = new TCHAR[128];
	_stprintf_s(str, 128, (flag ? _T("WIN") : _T("LOST")), kill);
	settextstyle(120, 120, _T("����"));
	settextcolor(RED);
	outtextxy(swidth / 2 - textwidth(str) / 2, sheight / 7, str);

	/* �÷� */
	TCHAR* str_1 = new TCHAR[128];
	_stprintf_s(str_1, 128, _T("�÷֣�%d"), score);
	settextstyle(40, 0, _T("����"));
	settextcolor(RED);
	outtextxy(swidth / 2 - textwidth(str_1) / 2, sheight / 7 * 2, str_1);

	/* ��ɱ�� */
	TCHAR* str_2 = new TCHAR[128];
	_stprintf_s(str_2, 128, _T("��ɱ����%d"), kill[0] + kill[1] + kill[2] + kill[3] + kill[4]);
	settextstyle(40, 0, _T("����"));
	settextcolor(RED);
	outtextxy(swidth / 2 - textwidth(str_2) / 2, sheight / 7 * 3, str_2);

	// ��ȡ�����¼�����Enter���أ�
	settextstyle(40, 0, _T("����"));
	settextcolor(BLACK);
	outtextxy(swidth / 2 - textwidth(_T("��Enter����")) / 2, sheight / 7 * 4, _T("��Enter����"));

	while (true) {
		ExMessage msg;
		getmessage(&msg, EX_KEY);// ��ȡ������Ϣ
		if (msg.vkcode == 0x0D) {// vkcode�ǰ�����������룬0x0D��Enter����Ӧ��value�����飺https://docs.easyx.cn/zh-cn/exmessage
			return;
		}
	}
}
