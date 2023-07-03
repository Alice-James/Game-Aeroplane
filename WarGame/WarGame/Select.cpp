#include <graphics.h>
#include "Select.h"
#include "PointInRect.h"
#include "config.h"

using namespace std;

int Select() {
    setbkcolor(WHITE);
    cleardevice();

    LPCTSTR title1 = _T("无尽模式");
    LPCTSTR title2 = _T("闯关模式");
    LPCTSTR texit = _T("返回");

    BeginBatchDraw();

    RECT tplayr1, tplayr2, texitr;
    settextstyle(40, 0, _T("楷体"));

    tplayr1.left = swidth / 2 - textwidth(title1) / 2;
    tplayr1.right = tplayr1.left + textwidth(title1);
    tplayr1.top = sheight / 5 * 1;
    tplayr1.bottom = tplayr1.top + textheight(title1);

    tplayr2.left = swidth / 2 - textwidth(title2) / 2;
    tplayr2.right = tplayr2.left + textwidth(title2);
    tplayr2.top = sheight / 5 * 2;
    tplayr2.bottom = tplayr2.top + textheight(title2);

    texitr.left = swidth / 2 - textwidth(texit) / 2;
    texitr.right = texitr.left + textwidth(texit);
    texitr.top = sheight / 5 * 3;
    texitr.bottom = texitr.top + textheight(texit);

    outtextxy(tplayr1.left, tplayr1.top, title1);
    outtextxy(tplayr2.left, tplayr2.top, title2);
    outtextxy(texitr.left, texitr.top, texit);

    EndBatchDraw();

    /* 获取鼠标事件 */
    while (true) {
        ExMessage msg;
        getmessage(&msg, EX_MOUSE);
        if (msg.lbutton) {
            if (PointInRect(msg.x, msg.y, tplayr1))
                return Select(1);
            if (PointInRect(msg.x, msg.y, tplayr2))
                return Select(2);
            if (PointInRect(msg.x, msg.y, texitr))
                return 0;
        }
    }
}

int Select(int index) {
    setbkcolor(WHITE);
    cleardevice();

    switch (index) {
    case 0:
        return 0;
    case 1: {
        LPCTSTR title = _T("无尽模式");
        LPCTSTR texit = _T("返回");
        LPCTSTR tmode[5] = { _T("1"), _T("2"),_T("3"),_T("4"),_T("5") };

        BeginBatchDraw();// BeginBatchDraw和EndBatchDraw用于消除频闪

        setbkcolor(WHITE);
        cleardevice();
        settextstyle(40, 0, _T("楷体"));
        settextcolor(BLACK);
        outtextxy(swidth / 2 - textwidth(title) / 2, sheight / 5, title);

        RECT mode_1[5];
        settextstyle(40, 0, _T("楷体"));

        mode_1[0].left = swidth / 6 * 1 - textwidth(tmode[0]) / 2;
        mode_1[0].right = mode_1[0].left + textwidth(tmode[0]);
        mode_1[0].top = sheight / 5 * 2;
        mode_1[0].bottom = mode_1[0].top + textheight(tmode[0]);
        outtextxy(mode_1[0].left, mode_1[0].top, tmode[0]);

        mode_1[1].left = swidth / 6 * 2 - textwidth(tmode[1]) / 2;
        mode_1[1].right = mode_1[1].left + textwidth(tmode[1]);
        mode_1[1].top = sheight / 5 * 2;
        mode_1[1].bottom = mode_1[1].top + textheight(tmode[1]);
        outtextxy(mode_1[1].left, mode_1[1].top, tmode[1]);

        mode_1[2].left = swidth / 6 * 3 - textwidth(tmode[2]) / 2;
        mode_1[2].right = mode_1[2].left + textwidth(tmode[2]);
        mode_1[2].top = sheight / 5 * 2;
        mode_1[2].bottom = mode_1[2].top + textheight(tmode[2]);
        outtextxy(mode_1[2].left, mode_1[2].top, tmode[2]);

        mode_1[3].left = swidth / 6 * 4 - textwidth(tmode[3]) / 2;
        mode_1[3].right = mode_1[3].left + textwidth(tmode[3]);
        mode_1[3].top = sheight / 5 * 2;
        mode_1[3].bottom = mode_1[3].top + textheight(tmode[3]);
        outtextxy(mode_1[3].left, mode_1[3].top, tmode[3]);

        mode_1[4].left = swidth / 6 * 5 - textwidth(tmode[4]) / 2;
        mode_1[4].right = mode_1[4].left + textwidth(tmode[4]);
        mode_1[4].top = sheight / 5 * 2;
        mode_1[4].bottom = mode_1[4].top + textheight(tmode[4]);
        outtextxy(mode_1[4].left, mode_1[4].top, tmode[4]);

        RECT texitr;
        settextstyle(40, 0, _T("楷体"));

        texitr.left = swidth / 2 - textwidth(texit) / 2;
        texitr.right = texitr.left + textwidth(texit);
        texitr.top = sheight / 5 * 3;
        texitr.bottom = texitr.top + textheight(texit);
        outtextxy(texitr.left, texitr.top, texit);

        EndBatchDraw();

        /* 获取鼠标事件 */
        while (true) {
            ExMessage msg;
            getmessage(&msg, EX_MOUSE);
            if (msg.lbutton) {
                if (PointInRect(msg.x, msg.y, texitr))// 如果点击"返回"按钮
                    return 0;// 退出程序
                if (PointInRect(msg.x, msg.y, mode_1[0]))
                    return 101;
                if (PointInRect(msg.x, msg.y, mode_1[1]))
                    return 102;
                if (PointInRect(msg.x, msg.y, mode_1[2]))
                    return 103;
                if (PointInRect(msg.x, msg.y, mode_1[3]))
                    return 104;
                if (PointInRect(msg.x, msg.y, mode_1[4]))
                    return 105;
            }
        }
    }

    case 2: {
        LPCTSTR title = _T("闯关模式");
        LPCTSTR texit = _T("返回");
        LPCTSTR tmode[5] = { _T("1"), _T("2"),_T("3"),_T("4"),_T("5") };

        BeginBatchDraw();// BeginBatchDraw和EndBatchDraw用于消除频闪

        setbkcolor(WHITE);
        cleardevice();
        settextstyle(40, 0, _T("楷体"));
        settextcolor(BLACK);
        outtextxy(swidth / 2 - textwidth(title) / 2, sheight / 5, title);

        RECT mode_2[5];
        settextstyle(40, 0, _T("楷体"));

        mode_2[0].left = swidth / 6 * 1 - textwidth(tmode[0]) / 2;
        mode_2[0].right = mode_2[0].left + textwidth(tmode[0]);
        mode_2[0].top = sheight / 5 * 2;
        mode_2[0].bottom = mode_2[0].top + textheight(tmode[0]);
        outtextxy(mode_2[0].left, mode_2[0].top, tmode[0]);

        mode_2[1].left = swidth / 6 * 2 - textwidth(tmode[1]) / 2;
        mode_2[1].right = mode_2[1].left + textwidth(tmode[1]);
        mode_2[1].top = sheight / 5 * 2;
        mode_2[1].bottom = mode_2[1].top + textheight(tmode[1]);
        outtextxy(mode_2[1].left, mode_2[1].top, tmode[1]);

        mode_2[2].left = swidth / 6 * 3 - textwidth(tmode[2]) / 2;
        mode_2[2].right = mode_2[2].left + textwidth(tmode[2]);
        mode_2[2].top = sheight / 5 * 2;
        mode_2[2].bottom = mode_2[2].top + textheight(tmode[2]);
        outtextxy(mode_2[2].left, mode_2[2].top, tmode[2]);

        mode_2[3].left = swidth / 6 * 4 - textwidth(tmode[3]) / 2;
        mode_2[3].right = mode_2[3].left + textwidth(tmode[3]);
        mode_2[3].top = sheight / 5 * 2;
        mode_2[3].bottom = mode_2[3].top + textheight(tmode[3]);
        outtextxy(mode_2[3].left, mode_2[3].top, tmode[3]);

        mode_2[4].left = swidth / 6 * 5 - textwidth(tmode[4]) / 2;
        mode_2[4].right = mode_2[4].left + textwidth(tmode[4]);
        mode_2[4].top = sheight / 5 * 2;
        mode_2[4].bottom = mode_2[4].top + textheight(tmode[4]);
        outtextxy(mode_2[4].left, mode_2[4].top, tmode[4]);

        RECT texitr;
        settextstyle(40, 0, _T("楷体"));

        texitr.left = swidth / 2 - textwidth(texit) / 2;
        texitr.right = texitr.left + textwidth(texit);
        texitr.top = sheight / 5 * 3;
        texitr.bottom = texitr.top + textheight(texit);
        outtextxy(texitr.left, texitr.top, texit);

        EndBatchDraw();

        /* 获取鼠标事件 */
        while (true) {
            ExMessage msg;
            getmessage(&msg, EX_MOUSE);
            if (msg.lbutton) {
                if (PointInRect(msg.x, msg.y, texitr))// 如果点击"返回"按钮
                    return 0;// 退出程序
                if (PointInRect(msg.x, msg.y, mode_2[0]))
                    return 201;
                if (PointInRect(msg.x, msg.y, mode_2[1]))
                    return 202;
                if (PointInRect(msg.x, msg.y, mode_2[2]))
                    return 203;
                if (PointInRect(msg.x, msg.y, mode_2[3]))
                    return 204;
                if (PointInRect(msg.x, msg.y, mode_2[4]))
                    return 205;
            }
        }
    }
    }
}