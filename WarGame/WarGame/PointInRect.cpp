#include "PointInRect.h"


bool PointInRect(int x, int y, RECT& r) {
    return (r.left <= x && x <= r.right && r.top <= y && y <= r.bottom);
}
