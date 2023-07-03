#pragma once
#include <windows.h>

/* 判断一个点坐标是否在一个矩形区域内部 */
bool PointInRect(int x, int y, RECT& r);
