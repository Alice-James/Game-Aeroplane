#include <graphics.h>
#include "Welcome.h"
#include "PointInRect.h"
#include "config.h"

using namespace std;

void Welcome() {
    LPCTSTR title = _T("飞机大战");// LPCTSTR是一种字符串，_T是类型转换
    LPCTSTR tplay = _T("开始游戏");
    LPCTSTR texit = _T("退出游戏");

    BeginBatchDraw();// BeginBatchDraw和EndBatchDraw用于消除频闪，详情：https://docs.easyx.cn/zh-cn/other-func

    /* 显示"飞机大战"四个字 */
    setbkcolor(WHITE);// setbkcolor函数用于设置当前设备绘图背景色，详情：https://docs.easyx.cn/zh-cn/setbkcolor
    cleardevice();// cleardevice函数使用当前背景色清空绘图设备，详情：https://docs.easyx.cn/zh-cn/cleardevice
    settextstyle(60, 0, _T("黑体"));// settextstyle函数用于设置当前文字样式，详情：https://docs.easyx.cn/zh-cn/settextstyle
    settextcolor(BLACK);// settextcolor函数用于设置当前文字颜色，详情：https://docs.easyx.cn/zh-cn/settextcolor
    outtextxy(swidth / 2 - textwidth(title) / 2, sheight / 5, title);// outtextxy函数用于在指定位置输出字符串，详情：https://docs.easyx.cn/zh-cn/outtextxy
    // textwidth函数用于获取字符串实际占用的像素宽度，详情：https://docs.easyx.cn/zh-cn/textwidth

    /* 显示"开始游戏"和"退出游戏"按钮 */
    RECT tplayr, texitr;// RECT是Windows API中的一个结构体，用于表示一个矩形区域。它通常用于处理窗口、图形和用户界面等方面的编程。详情：https://learn.microsoft.com/zh-cn/windows/win32/api/windef/ns-windef-rect
    settextstyle(40, 0, _T("楷体"));

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

    /* 获取鼠标事件 */
    while (true) {
        ExMessage msg;// ExMessage结构体用于保存鼠标消息，详情：https://docs.easyx.cn/zh-cn/exmessage
        getmessage(&msg, EX_MOUSE);// getmessage函数用于获取一个消息。如果当前消息队列中没有，就一直等待。详情：https://docs.easyx.cn/zh-cn/getmessage
        if (msg.lbutton) {
            if (PointInRect(msg.x, msg.y, tplayr))// 如果点击"开始游戏"按钮
                return;// 跳出开始界面，执行后续步骤
            if (PointInRect(msg.x, msg.y, texitr))// 如果点击"退出游戏"按钮
                exit(0);// 退出程序
        }
    }
}
