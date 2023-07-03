#include "AddEnemy.h"
#include "RectDuangRect.h"

bool AddEnemy(vector<Enemy*>& ep, IMAGE& enemyimg, IMAGE* boom) {
	Enemy* e = new Enemy(enemyimg, abs(rand()) % (swidth - enemyimg.getwidth()), boom);
	for (auto& i : ep) {
		if (RectDuangRect(i->GetRect(), e->GetRect())) {
			delete e;
			return false;
		}
	}
	ep.push_back(e);
	return true;
}
bool AddEnemy(vector<midEnemy*>& ep, IMAGE& enemyimg, IMAGE* boom) {
	midEnemy* e = new midEnemy(enemyimg, abs(rand()) % (swidth - enemyimg.getwidth()), boom);
	for (auto& i : ep) {
		if (RectDuangRect(i->GetRect(), e->GetRect())) {
			delete e;
			return false;
		}
	}
	ep.push_back(e);
	return true;
}
bool AddEnemy(vector<miniEnemy*>& ep, IMAGE& enemyimg, IMAGE* boom, int x) {
	miniEnemy* e = new miniEnemy(enemyimg, swidth / 3 * x + abs(rand()) % (swidth / 3 - enemyimg.getwidth()), boom);
	//for (auto& i : ep) {
	//	if (RectDuangRect(i->GetRect(), e->GetRect())) {
	//		delete e;
	//		return false;
	//	}
	//}
	ep.push_back(e);
	return true;
}
bool AddEnemy(vector<giantEnemy*>& ep, IMAGE& enemyimg, IMAGE* boom) {
	giantEnemy* e = new giantEnemy(enemyimg, abs(rand()) % (swidth - enemyimg.getwidth()), boom);
	for (auto& i : ep) {
		if (RectDuangRect(i->GetRect(), e->GetRect())) {
			delete e;
			return false;
		}
	}
	ep.push_back(e);
	return true;
}
bool AddEnemy(vector<bossEnemy*>& ep, IMAGE& enemyimg, IMAGE* boom) {
	bossEnemy* e = new bossEnemy(enemyimg, 0, boom);
	ep.push_back(e);
	return true;
}
