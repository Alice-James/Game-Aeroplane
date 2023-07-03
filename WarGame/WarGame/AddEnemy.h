#pragma once

#include <vector>
#include "EnemyPlane.h"

using namespace std;

/* Ìí¼ÓµÐ»ú */
bool AddEnemy(vector<Enemy*> &ep, IMAGE& enemyimg, IMAGE* boom);
bool AddEnemy(vector<midEnemy*> &ep, IMAGE& enemyimg, IMAGE* boom);
bool AddEnemy(vector<miniEnemy*> &ep, IMAGE& enemyimg, IMAGE* boom, int x);
bool AddEnemy(vector<giantEnemy*> &ep, IMAGE& enemyimg, IMAGE* boom);
bool AddEnemy(vector<bossEnemy*> &ep, IMAGE& enemyimg, IMAGE* boom);
