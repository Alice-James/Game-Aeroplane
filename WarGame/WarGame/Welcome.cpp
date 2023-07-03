#include <graphics.h>
#include "Welcome.h"
#include "PointInRect.h"
#include "config.h"

using namespace std;

void Welcome() {
    LPCTSTR title = _T("�ɻ���ս");// LPCTSTR��һ���ַ�����_T������ת��
    LPCTSTR tplay = _T("��ʼ��Ϸ");
    LPCTSTR texit = _T("�˳���Ϸ");

    BeginBatchDraw();// BeginBatchDraw��EndBatchDraw��������Ƶ�������飺https://docs.easyx.cn/zh-cn/other-func

    /* ��ʾ"�ɻ���ս"�ĸ��� */
    setbkcolor(WHITE);// setbkcolor�����������õ�ǰ�豸��ͼ����ɫ�����飺https://docs.easyx.cn/zh-cn/setbkcolor
    cleardevice();// cleardevice����ʹ�õ�ǰ����ɫ��ջ�ͼ�豸�����飺https://docs.easyx.cn/zh-cn/cleardevice
    settextstyle(60, 0, _T("����"));// settextstyle�����������õ�ǰ������ʽ�����飺https://docs.easyx.cn/zh-cn/settextstyle
    settextcolor(BLACK);// settextcolor�����������õ�ǰ������ɫ�����飺https://docs.easyx.cn/zh-cn/settextcolor
    outtextxy(swidth / 2 - textwidth(title) / 2, sheight / 5, title);// outtextxy����������ָ��λ������ַ��������飺https://docs.easyx.cn/zh-cn/outtextxy
    // textwidth�������ڻ�ȡ�ַ���ʵ��ռ�õ����ؿ�ȣ����飺https://docs.easyx.cn/zh-cn/textwidth

    /* ��ʾ"��ʼ��Ϸ"��"�˳���Ϸ"��ť */
    RECT tplayr, texitr;// RECT��Windows API�е�һ���ṹ�壬���ڱ�ʾһ������������ͨ�����ڴ����ڡ�ͼ�κ��û�����ȷ���ı�̡����飺https://learn.microsoft.com/zh-cn/windows/win32/api/windef/ns-windef-rect
    settextstyle(40, 0, _T("����"));

    tplayr.left = swidth / 2 - textwidth(tplay) / 2;
    tplayr.right = tplayr.left + textwidth(tplay);
    tplayr.top = sheight / 5 * 2.5;
    tplayr.bottom = tplayr.top + textheight(tplay);

    texitr.left = swidth / 2 - textwidth(texit) / 2;
    texitr.right = texitr.left + textwidth(texit);
    texitr.top = sheight / 5 * 3;
    texitr.bottom = texitr.top + textheight(texit);

    outtextxy(tplayr.left, tplayr.top, tplay);
    outtextxy(texitr.left, texitr.top, texit);

    EndBatchDraw();

    /* ��ȡ����¼� */
    while (true) {
        ExMessage msg;// ExMessage�ṹ�����ڱ��������Ϣ�����飺https://docs.easyx.cn/zh-cn/exmessage
        getmessage(&msg, EX_MOUSE);// getmessage�������ڻ�ȡһ����Ϣ�������ǰ��Ϣ������û�У���һֱ�ȴ������飺https://docs.easyx.cn/zh-cn/getmessage
        if (msg.lbutton) {
            if (PointInRect(msg.x, msg.y, tplayr))// ������"��ʼ��Ϸ"��ť
                return;// ������ʼ���棬ִ�к�������
            if (PointInRect(msg.x, msg.y, texitr))// ������"�˳���Ϸ"��ť
                exit(0);// �˳�����
        }
    }
}
