#include "Play.h"
#include <graphics.h>
#include "config.h"
#include "background.h"
#include "HeroPlane.h"
#include "EnemyPlane.h"
#include <vector>
#include "RectDuangRect.h"
#include "AddEnemy.h"
#include "Bullet.h"
#include "Over.h"
#include <conio.h>// 用于暂停游戏
#include <iostream>
#include "Res.h"
#include "Gift.h"
#include "AddGift.h"
#include "PrintScore.h"
#include "music.h"

using namespace std;


bool Play(int index) {
	setbkcolor(WHITE);
	cleardevice();
	bool is_play = true;

	loadimage(&heroimg, _T(".\\res\\mplane.png"));// loadimage函数用于从文件中读取图像，详情：https://docs.easyx.cn/zh-cn/loadimage
	loadimage(&heroimg2, _T(".\\res\\mplane1.png"));// loadimage函数用于从文件中读取图像，详情：https://docs.easyx.cn/zh-cn/loadimage
	loadimage(&bgimg, _T(".\\res\\bg.png"), swidth, sheight * 2);// 设置图片的拉伸宽度和高度
	loadimage(&bgimg2, _T(".\\res\\bg2.png"), swidth, sheight * 2);
	loadimage(&bgimg3, _T(".\\res\\bg3.png"), swidth, sheight * 2);
	loadimage(&bgimg4, _T(".\\res\\bg4.png"), swidth, sheight * 2);
	loadimage(&bgimg5, _T(".\\res\\bg5.png"), swidth, sheight * 2);
	loadimage(&enemyimg, _T(".\\res\\enemy.png"));
	loadimage(&midEnemyimg, _T(".\\res\\n1_1.png"));
	loadimage(&miniEnemyimg, _T(".\\res\\ufo.png"));
	loadimage(&giantEnemyimg, _T(".\\res\\n2.png"));
	loadimage(&bossEnemyimg, _T(".\\res\\n_boss.png"));
	loadimage(&bulletimg, _T(".\\res\\bullet.png"));
	loadimage(&bullet4img, _T(".\\res\\bullet4.png"));
	loadimage(&ebulletimg, _T(".\\res\\ufoa_bullet.png"));
	loadimage(&bossSkill_1img, _T(".\\res\\ufo.png"));
	loadimage(&bossSkill_2img, _T(".\\res\\bullet1.png"));
	loadimage(&bossSkill_3img, _T(".\\res\\n3.png"));
	loadimage(&eboom[0], _T(".\\res\\enemy1_down3.png"));
	loadimage(&eboom[1], _T(".\\res\\enemy2_down3.png"));
	loadimage(&eboom[2], _T(".\\res\\enemy2_down4.png"));
	loadimage(&giftimg[0], _T(".\\res\\gift1.png"));
	loadimage(&giftimg[1], _T(".\\res\\CloseNormal.png"));
	loadimage(&giftimg[2], _T(".\\res\\number2.png"));
	loadimage(&giftimg[3], _T(".\\res\\number3.png"));
	loadimage(&giftimg[4], _T(".\\res\\player.png"));

	switch (index) {
		// 返回开始界面
		case 0: break;

		// 无尽模式——第1关：普通敌机
		// 密度：density = 5
		case 101: {
			/* 声明对象 */
			BG bg = BG(bgimg);// 背景
			Hero hp = Hero(heroimg);// 玩家飞机
			vector<Enemy*> ep;// 敌机向量（普通）
			vector<Bullet*> bs;// 我方子弹向量（普通）
			vector<Bullet2_1*> bs2_1;// 我方子弹向量（双发子弹（左））
			vector<Bullet2_2*> bs2_2;// 我方子弹向量（双发子弹（右））
			vector<Bullet3_1*> bs3_1;// 我方子弹向量（分叉子弹（中））
			vector<Bullet3_2*> bs3_2;// 我方子弹向量（分叉子弹（左））
			vector<Bullet3_3*> bs3_3;// 我方子弹向量（分叉子弹（右））
			vector<Bullet4*> bs4;// 我方子弹向量（穿甲弹）
			vector<EBullet*> ebs;// 敌方子弹向量（普通）
			vector<Gift*> gift;// 道具向量

			/* 定义基本变量 */
			int bsing = 0;// 控制我方子弹发射频率（普通）
			int ebsing = 0;// 控制敌方子弹发射频率（普通）
			int density = DENSITY;// 控制敌机密度（普通）

			/* 定义计数器 */
			int kill[5] = {0, 0, 0, 0, 0};// 记录整局击杀数量:{普通，中型，小型，大型，BOSS}
			int score = 0;// 记录得分：{普通：3，中型：5，小型：1，大型：7，BOSS：31}
			int kill_temp = 0;// 记录当前杀敌数量（达到一定值后归零，用于确定发送道具时机）
			int bullets_total = 0;// 记录有道具期间发射子弹总数，用于切换道具状态
			int condition = 0;// 用于切换道具状态，默认为0
			int gift_index = 0;// 用于记录道具种类

			playBgmMusic();

			/* 添加开局敌机 */
			for (int i = 0; i < density; i++) {
				AddEnemy(ep, enemyimg, eboom);
			}

			/* 进入游戏中 */
			while (is_play) {
				/* 加载背景、玩家飞机 */
				BeginBatchDraw();// BeginBatchDraw和EndBatchDraw用于消除频闪，详情：https://docs.easyx.cn/zh-cn/other-func
				bg.Show();
				Sleep(4);
				flushmessage();
				Sleep(1);
				hp.Control();
				hp.Show();

				/* 按空格暂停 */
				if (GetAsyncKeyState(VK_SPACE) & 0x0001)
					while (!(GetAsyncKeyState(VK_SPACE) & 0x0001));

				/* 添加敌方子弹 */
				ebsing++;
				if (ebsing == 101 - ebs_frequency) {
					ebsing = 0;
					for (auto& i : ep)
						ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// 敌方子弹（普通）
				}

				/* 添加敌机 */
				for (int i = 0; i < density - ep.size(); i++) {
					AddEnemy(ep, enemyimg, eboom);
				}

				/* 加载敌方子弹 */
				auto ebsit = ebs.begin();
				while (ebsit != ebs.end()) {
					// 我方飞机被击中
					if (RectDuangRect((*ebsit)->GetRect(), hp.GetRect())) {
						/* 结果 */
						is_play = hp.hurt();

						ebsit = ebs.erase(ebsit);
					}
					// 如果子弹飞出屏幕则去除
					else if (!(*ebsit)->Show())
						ebsit = ebs.erase(ebsit);
					else
						ebsit++;
				}
				
				/* 拾取道具进入对应状态 */
				switch (condition) {
					/* 正常状态 */
					case 0: {
						/* 添加我方子弹 */
						bsing++;
						if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
							bsing = 0;
							bs.push_back(new Bullet(bulletimg, hp.GetRect()));// 我方子弹（普通）
						}

						/* 加载我方子弹 */
						auto bsit = bs.begin();
						while (bsit != bs.end()) {
							// 如果子弹飞出屏幕则去除
							if (!(*bsit)->Show())
								bsit = bs.erase(bsit);
							else
								bsit++;
						}

						/* 加载敌方飞机 */
						auto it = ep.begin();
						while (it != ep.end()) {
							// 敌方飞机与我方飞机相撞
							if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
								/* 结果 */
								is_play = hp.hurt();
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
									kill_temp++;
								}

								delete (*it);// 删除类指针
								ep.erase(it);// 踢出容器
								it = ep.begin();
							}

							/* 如果我方子弹击中敌机 */
							auto bit = bs.begin();
							while (bit != bs.end()) {
								if (RectDuangRect((*bit)->GetRect(), (*it)->GetRect())) {
									/* 结果 */
									if (!(*it)->dying()) {
										(*it)->Dies();
										kill[0]++;
										kill_temp++;
									}

									delete (*bit);
									bs.erase(bit);

									break;
								}
								bit++;
							}

							// 如果敌机飞出屏幕则去除
							if (!(*it)->Show()) {
								delete (*it);// 删除类指针
								ep.erase(it);// 踢出容器
								it = ep.begin();
							}
							else
								it++;
						}
						break;// 跳出case
					}

					/* 道具1：加生命值（一次性道具） */
					case 1: {
						hp.heal();

						condition = 0;// 恢复正常状态

						break;// 跳出case
					}

					/* 道具2：清空敌机和敌方子弹（一次性道具） */
					case 2: {
						/* 清空敌方子弹 */
						auto ebsit = ebs.begin();
						while (ebsit != ebs.end()) {
							ebsit = ebs.erase(ebsit);
						}

						/* 清空敌方飞机 */
						auto it = ep.begin();
						while (it != ep.end()) {
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}

							// 如果敌机飞出屏幕则去除
							if (!(*it)->Show()) {
								delete (*it);// 删除类指针
								ep.erase(it);// 踢出容器
								it = ep.begin();
							}
							else
								it++;
						}

						condition = 0;// 恢复正常状态

						break;// 跳出case
					}

					/* 道具3：双发子弹（一段时间） */
					case 3: {
						/* 添加我方子弹 */
						bsing++;
						if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
							bsing = 0;
							bs2_1.push_back(new Bullet2_1(bulletimg, hp.GetRect()));// 我方子弹（双发子弹（左））
							bs2_2.push_back(new Bullet2_2(bulletimg, hp.GetRect()));// 我方子弹（双发子弹（右））

							/* 发射一定数量子弹后恢复正常状态 */
							bullets_total++;
							if (bullets_total >= BULLETS_MAX) {
								condition = 0;
								bullets_total = 0;
							}
						}

						/* 加载我方子弹 */
						auto bsit2_1 = bs2_1.begin();
						while (bsit2_1 != bs2_1.end()) {
							// 如果子弹飞出屏幕则去除
							if (!(*bsit2_1)->Show())
								bsit2_1 = bs2_1.erase(bsit2_1);
							else
								bsit2_1++;
						}
						auto bsit2_2 = bs2_2.begin();
						while (bsit2_2 != bs2_2.end()) {
							// 如果子弹飞出屏幕则去除
							if (!(*bsit2_2)->Show())
								bsit2_2 = bs2_2.erase(bsit2_2);
							else
								bsit2_2++;
						}

						/* 加载敌方飞机 */
						auto it = ep.begin();
						while (it != ep.end()) {
							// 敌方飞机与我方飞机相撞
							if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
								/* 结果 */
								is_play = hp.hurt();
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								delete (*it);// 删除类指针
								ep.erase(it);// 踢出容器
								it = ep.begin();
							}

							/* 如果我方子弹击中敌机 */
							auto bit2_1 = bs2_1.begin();
							while (bit2_1 != bs2_1.end()) {
								if (RectDuangRect((*bit2_1)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
									/* 结果 */
									if (!(*it)->dying()) {
										(*it)->Dies();
										kill[0]++;
									}

									delete (*bit2_1);
									bs2_1.erase(bit2_1);

									break;
								}
								bit2_1++;
							}
							auto bit2_2 = bs2_2.begin();
							while (bit2_2 != bs2_2.end()) {
								if (RectDuangRect((*bit2_2)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
									/* 结果 */
									if (!(*it)->dying()) {
										(*it)->Dies();
										kill[0]++;
									}


									delete (*bit2_2);
									bs2_2.erase(bit2_2);

									break;
								}
								bit2_2++;
							}

							// 如果敌机飞出屏幕则去除
							if (!(*it)->Show()) {
								delete (*it);// 删除类指针
								ep.erase(it);// 踢出容器
								it = ep.begin();
							}
							else
								it++;
						}
						break;// 跳出case
					}

					/* 道具4：分叉子弹（一段时间） */
					case 4: {
						/* 添加我方子弹 */
						bsing++;
						if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
							bsing = 0;
							bs3_1.push_back(new Bullet3_1(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（中））
							bs3_2.push_back(new Bullet3_2(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（左））
							bs3_3.push_back(new Bullet3_3(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（右））

							/* 发射一定数量子弹后恢复正常状态 */
							bullets_total++;
							if (bullets_total >= BULLETS_MAX) {
								condition = 0;
								bullets_total = 0;
							}
						}

						/* 加载我方子弹 */
						auto bsit3_1 = bs3_1.begin();
						while (bsit3_1 != bs3_1.end()) {
							// 如果子弹飞出屏幕则去除
							if (!(*bsit3_1)->Show())
								bsit3_1 = bs3_1.erase(bsit3_1);
							else
								bsit3_1++;
						}
						auto bsit3_2 = bs3_2.begin();
						while (bsit3_2 != bs3_2.end()) {
							// 如果子弹飞出屏幕则去除
							if (!(*bsit3_2)->Show())
								bsit3_2 = bs3_2.erase(bsit3_2);
							else
								bsit3_2++;
						}
						auto bsit3_3 = bs3_3.begin();
						while (bsit3_3 != bs3_3.end()) {
							// 如果子弹飞出屏幕则去除
							if (!(*bsit3_3)->Show())
								bsit3_3 = bs3_3.erase(bsit3_3);
							else
								bsit3_3++;
						}

						/* 加载敌方飞机 */
						auto it = ep.begin();
						while (it != ep.end()) {
							// 敌方飞机与我方飞机相撞
							if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
								/* 结果 */
								is_play = hp.hurt();
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}


								delete (*it);// 删除类指针
								ep.erase(it);// 踢出容器
								it = ep.begin();
							}

							/* 如果我方子弹击中敌机 */
							auto bit3_1 = bs3_1.begin();
							while (bit3_1 != bs3_1.end()) {
								if (RectDuangRect((*bit3_1)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
									/* 结果 */
									if (!(*it)->dying()) {
										(*it)->Dies();
										kill[0]++;
									}

									delete (*bit3_1);
									bs3_1.erase(bit3_1);

									break;
								}
								bit3_1++;
							}
							auto bit3_2 = bs3_2.begin();
							while (bit3_2 != bs3_2.end()) {
								if (RectDuangRect((*bit3_2)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
									/* 结果 */
									if (!(*it)->dying()) {
										(*it)->Dies();
										kill[0]++;
									}

									delete (*bit3_2);
									bs3_2.erase(bit3_2);

									break;
								}
								bit3_2++;
							}
							auto bit3_3 = bs3_3.begin();
							while (bit3_3 != bs3_3.end()) {
								if (RectDuangRect((*bit3_3)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
									/* 结果 */
									if (!(*it)->dying()) {
										(*it)->Dies();
										kill[0]++;
									}

									delete (*bit3_3);
									bs3_3.erase(bit3_3);

									break;
								}
								bit3_3++;
							}

							// 如果敌机飞出屏幕则去除
							if (!(*it)->Show()) {
								delete (*it);// 删除类指针
								ep.erase(it);// 踢出容器
								it = ep.begin();
							}
							else
								it++;
						}
						break;// 跳出case
					}

					/* 道具5：穿甲子弹（一段时间） */
					case 5: {
						/* 添加我方子弹 */
						bsing++;
						if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
							bsing = 0;
							bs4.push_back(new Bullet4(bullet4img, hp.GetRect()));// 我方子弹（穿甲弹）

							/* 发射一定数量子弹后恢复正常状态 */
							bullets_total++;
							if (bullets_total >= BULLETS_MAX) {
								condition = 0;
								bullets_total = 0;
							}
						}

						/* 加载我方子弹 */
						auto bsit4 = bs4.begin();
						while (bsit4 != bs4.end()) {
							// 如果子弹飞出屏幕则去除
							if (!(*bsit4)->Show())
								bsit4 = bs4.erase(bsit4);
							else
								bsit4++;
						}

						/* 加载敌方飞机 */
						auto it = ep.begin();
						while (it != ep.end()) {
							// 敌方飞机与我方飞机相撞
							if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
								/* 结果 */
								is_play = hp.hurt();
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								delete (*it);// 删除类指针
								ep.erase(it);// 踢出容器
								it = ep.begin();
							}

							/* 如果我方子弹击中敌机 */
							auto bit4 = bs4.begin();
							while (bit4 != bs4.end()) {
								if (RectDuangRect((*bit4)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
									/* 结果 */
									if (!(*it)->dying()) {
										(*it)->Dies();
										kill[0]++;
									}

									break;
								}
								bit4++;
							}

							// 如果敌机飞出屏幕则去除
							if (!(*it)->Show()) {
								delete (*it);// 删除类指针
								ep.erase(it);// 踢出容器
								it = ep.begin();
							}
							else
								it++;
						}
						break;// 跳出case
					}
				}
				
				/* 每杀一定数量敌人送一个道具 */
				if ((condition == 0) && (kill_temp >= KILL_FOR_GIFT)) {
					/* 随机发放道具（未完成） */
					gift_index = rand() % 5;
					AddGift(gift, giftimg[gift_index]);

					kill_temp = 0;
					bullets_total = 0;
				}
				/* 加载道具 */
				auto gift_it = gift.begin();
				while (gift_it != gift.end()) {
					// 成功拾取道具
					if (RectDuangRect((*gift_it)->GetRect(), hp.GetRect())) {
						condition = gift_index + 1;

						delete (*gift_it);// 删除类指针
						gift.erase(gift_it);// 踢出容器
						gift_it = gift.begin();
						break;
					}
					// 未能拾取道具（已经飞出屏幕）
					if (!(*gift_it)->Show()) {
						delete (*gift_it);// 删除类指针
						gift.erase(gift_it);// 踢出容器
						gift_it = gift.begin();
					}
					else
						gift_it++;
				}

				/* 右上角实时显示击杀数和得分 */
				score = kill[0] * 3 + kill[1] * 5 + kill[2] * 1 + kill[3] * 7 + kill[4] * 31;
				PrintScore(kill, score);

				EndBatchDraw();// BeginBatchDraw和EndBatchDraw用于消除频闪				
			}

			stopBgmMusic();
			Over(kill, score);// 结算界面
			break;
		}
		
		// 无尽模式——第2关：中型敌机
		// 密度：mid_density = 3
		case 102: {
			/* 声明对象 */
			BG bg = BG(bgimg);// 背景
			Hero hp = Hero(heroimg);// 玩家飞机
			vector<midEnemy*> mid_ep;// 敌机向量（中型）
			vector<Bullet*> bs;// 我方子弹向量（普通）
			vector<Bullet2_1*> bs2_1;// 我方子弹向量（双发子弹（左））
			vector<Bullet2_2*> bs2_2;// 我方子弹向量（双发子弹（右））
			vector<Bullet3_1*> bs3_1;// 我方子弹向量（分叉子弹（中））
			vector<Bullet3_2*> bs3_2;// 我方子弹向量（分叉子弹（左））
			vector<Bullet3_3*> bs3_3;// 我方子弹向量（分叉子弹（右））
			vector<Bullet4*> bs4;// 我方子弹向量（穿甲弹）
			vector<EBullet*> mid_ebs;// 敌方子弹向量（中型）
			vector<Gift*> gift;// 道具向量

			/* 定义基本变量 */
			int bsing = 0;// 控制我方子弹发射频率（普通）
			int mid_ebsing = 0;// 控制敌方子弹发射频率（中型）
			int mid_density = MID_DENSITY;// 控制敌机密度（中型）

			/* 定义计数器 */
			int kill[5] = { 0, 0, 0, 0, 0 };// 记录整局击杀数量:{普通，中型，小型，大型，BOSS}
			int score = 0;// 记录得分：{普通：3，中型：5，小型：1，大型：7，BOSS：31}
			int kill_temp = 0;// 记录当前杀敌数量（达到一定值后归零，用于确定发送道具时机）
			int bullets_total = 0;// 记录有道具期间发射子弹总数，用于切换道具状态
			int condition = 0;// 用于切换道具状态，默认为0
			int gift_index = 0;// 用于记录道具种类

			playBgmMusic();

			/* 添加开局敌机 */
			for (int i = 0; i < mid_density; i++) {
				AddEnemy(mid_ep, midEnemyimg, eboom);
			}

			/* 进入游戏中 */
			while (is_play) {
				/* 加载背景、玩家飞机 */
				BeginBatchDraw();// BeginBatchDraw和EndBatchDraw用于消除频闪，详情：https://docs.easyx.cn/zh-cn/other-func
				bg.Show();
				Sleep(4);
				flushmessage();
				Sleep(1);
				hp.Control();
				hp.Show();

				/* 按空格暂停 */
				if (GetAsyncKeyState(VK_SPACE) & 0x0001)
					while (!(GetAsyncKeyState(VK_SPACE) & 0x0001));

				/* 添加敌方子弹 */
				mid_ebsing++;
				if (mid_ebsing == 101 - mid_ebs_frequency) {
					mid_ebsing = 0;
					for (auto& i : mid_ep)
						mid_ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// 敌方子弹（中型）
				}

				/* 添加敌机 */
				for (int i = 0; i < mid_density - mid_ep.size(); i++) {
					AddEnemy(mid_ep, midEnemyimg, eboom);
				}

				/* 加载敌方子弹 */
				auto mid_ebsit = mid_ebs.begin();
				while (mid_ebsit != mid_ebs.end()) {
					// 我方飞机被击中
					if (RectDuangRect((*mid_ebsit)->GetRect(), hp.GetRect())) {
						/* 结果 */
						is_play = hp.hurt();

						mid_ebsit = mid_ebs.erase(mid_ebsit);
					}
					// 如果子弹飞出屏幕则去除
					else if (!(*mid_ebsit)->Show())
						mid_ebsit = mid_ebs.erase(mid_ebsit);
					else
						mid_ebsit++;
				}

				/* 拾取道具进入对应状态 */
				switch (condition) {
					/* 正常状态 */
				case 0: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs.push_back(new Bullet(bulletimg, hp.GetRect()));// 我方子弹（普通）
					}

					/* 加载我方子弹 */
					auto bsit = bs.begin();
					while (bsit != bs.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit)->Show())
							bsit = bs.erase(bsit);
						else
							bsit++;
					}

					/* 加载敌方飞机 */
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
								kill_temp++;
							}

							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*mid_it)->GetRect())) {
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if((*mid_it)->how_many_lives() == 1){
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit);
								bs.erase(bit);

								break;
							}
							bit++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					break;// 跳出case
				}

					  /* 道具1：加生命值（一次性道具） */
				case 1: {
					hp.heal();

					condition = 0;// 恢复正常状态

					break;// 跳出case
				}

					  /* 道具2：清空敌机和敌方子弹（一次性道具） */
				case 2: {
					/* 清空敌方子弹 */
					auto mid_ebsit = mid_ebs.begin();
					while (mid_ebsit != mid_ebs.end()) {
						mid_ebsit = mid_ebs.erase(mid_ebsit);
					}

					/* 清空敌方飞机 */
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						if (!(*mid_it)->dying()) {
							(*mid_it)->Dies();
							kill[1]++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}

					condition = 0;// 恢复正常状态

					break;// 跳出case
				}

					  /* 道具3：双发子弹（一段时间） */
				case 3: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs2_1.push_back(new Bullet2_1(bulletimg, hp.GetRect()));// 我方子弹（双发子弹（左））
						bs2_2.push_back(new Bullet2_2(bulletimg, hp.GetRect()));// 我方子弹（双发子弹（右））

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit2_1 = bs2_1.begin();
					while (bsit2_1 != bs2_1.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit2_1)->Show())
							bsit2_1 = bs2_1.erase(bsit2_1);
						else
							bsit2_1++;
					}
					auto bsit2_2 = bs2_2.begin();
					while (bsit2_2 != bs2_2.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit2_2)->Show())
							bsit2_2 = bs2_2.erase(bsit2_2);
						else
							bsit2_2++;
					}

					/* 加载敌方飞机 */
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit2_1);
								bs2_1.erase(bit2_1);

								break;
							}
							bit2_1++;
						}
						auto bit2_2 = bs2_2.begin();
						while (bit2_2 != bs2_2.end()) {
							if (RectDuangRect((*bit2_2)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit2_2);
								bs2_2.erase(bit2_2);

								break;
							}
							bit2_2++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					break;// 跳出case
				}

					  /* 道具4：分叉子弹（一段时间） */
				case 4: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs3_1.push_back(new Bullet3_1(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（中））
						bs3_2.push_back(new Bullet3_2(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（左））
						bs3_3.push_back(new Bullet3_3(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（右））

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit3_1 = bs3_1.begin();
					while (bsit3_1 != bs3_1.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_1)->Show())
							bsit3_1 = bs3_1.erase(bsit3_1);
						else
							bsit3_1++;
					}
					auto bsit3_2 = bs3_2.begin();
					while (bsit3_2 != bs3_2.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_2)->Show())
							bsit3_2 = bs3_2.erase(bsit3_2);
						else
							bsit3_2++;
					}
					auto bsit3_3 = bs3_3.begin();
					while (bsit3_3 != bs3_3.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_3)->Show())
							bsit3_3 = bs3_3.erase(bsit3_3);
						else
							bsit3_3++;
					}

					/* 加载敌方飞机 */
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit3_1);
								bs3_1.erase(bit3_1);

								break;
							}
							bit3_1++;
						}
						auto bit3_2 = bs3_2.begin();
						while (bit3_2 != bs3_2.end()) {
							if (RectDuangRect((*bit3_2)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit3_2);
								bs3_2.erase(bit3_2);

								break;
							}
							bit3_2++;
						}
						auto bit3_3 = bs3_3.begin();
						while (bit3_3 != bs3_3.end()) {
							if (RectDuangRect((*bit3_3)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit3_3);
								bs3_3.erase(bit3_3);

								break;
							}
							bit3_3++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					break;// 跳出case
				}

					  /* 道具5：穿甲子弹（一段时间） */
				case 5: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs4.push_back(new Bullet4(bullet4img, hp.GetRect()));// 我方子弹（穿甲弹）

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit4 = bs4.begin();
					while (bsit4 != bs4.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit4)->Show())
							bsit4 = bs4.erase(bsit4);
						else
							bsit4++;
					}

					/* 加载敌方飞机 */
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								break;
							}
							bit4++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					break;// 跳出case
				}
				}

				/* 每杀一定数量敌人送一个道具 */
				if ((condition == 0) && (kill_temp >= KILL_FOR_GIFT)) {
					/* 随机发放道具（未完成） */
					gift_index = rand() % 5;
					AddGift(gift, giftimg[gift_index]);

					kill_temp = 0;
					bullets_total = 0;
				}
				/* 加载道具 */
				auto gift_it = gift.begin();
				while (gift_it != gift.end()) {
					// 成功拾取道具
					if (RectDuangRect((*gift_it)->GetRect(), hp.GetRect())) {
						condition = gift_index + 1;

						delete (*gift_it);// 删除类指针
						gift.erase(gift_it);// 踢出容器
						gift_it = gift.begin();
						break;
					}
					// 未能拾取道具（已经飞出屏幕）
					if (!(*gift_it)->Show()) {
						delete (*gift_it);// 删除类指针
						gift.erase(gift_it);// 踢出容器
						gift_it = gift.begin();
					}
					else
						gift_it++;
				}

				/* 右上角实时显示击杀数和得分 */
				score = kill[0] * 3 + kill[1] * 5 + kill[2] * 1 + kill[3] * 7 + kill[4] * 31;
				PrintScore(kill, score);

				EndBatchDraw();// BeginBatchDraw和EndBatchDraw用于消除频闪				
			}

			stopBgmMusic();
			Over(kill, score);// 结算界面
			break;
		}

		// 无尽模式——第3关：小型敌机
		// 密度：mini_density = 8
		case 103: {
			/* 声明对象 */
			BG bg = BG(bgimg);// 背景
			Hero hp = Hero(heroimg);// 玩家飞机
			vector<miniEnemy*> mini_ep;// 敌机向量（小型）
			vector<Bullet*> bs;// 我方子弹向量（普通）
			vector<Bullet2_1*> bs2_1;// 我方子弹向量（双发子弹（左））
			vector<Bullet2_2*> bs2_2;// 我方子弹向量（双发子弹（右））
			vector<Bullet3_1*> bs3_1;// 我方子弹向量（分叉子弹（中））
			vector<Bullet3_2*> bs3_2;// 我方子弹向量（分叉子弹（左））
			vector<Bullet3_3*> bs3_3;// 我方子弹向量（分叉子弹（右））
			vector<Bullet4*> bs4;// 我方子弹向量（穿甲弹）
			vector<Gift*> gift;// 道具向量

			/* 定义基本变量 */
			int bsing = 0;// 控制我方子弹发射频率（普通）
			int mini_density = MINI_DENSITY;// 控制敌机密度（小型）

			/* 定义计数器 */
			int kill[5] = { 0, 0, 0, 0, 0 };// 记录整局击杀数量:{普通，中型，小型，大型，BOSS}
			int score = 0;// 记录得分：{普通：3，中型：5，小型：1，大型：7，BOSS：31}
			int kill_temp = 0;// 记录当前杀敌数量（达到一定值后归零，用于确定发送道具时机）
			int bullets_total = 0;// 记录有道具期间发射子弹总数，用于切换道具状态
			int condition = 0;// 用于切换道具状态，默认为0
			int gift_index = 0;// 用于记录道具种类

			/* 记录时间 */
			DWORD startTime = timeGetTime();// 获取开始时间
			int mini_time = 4000;// 小型敌机刷新时间

			playBgmMusic();

			/* 添加开局敌机 */
			for (int i = 0; i < mini_density; i++) {
				AddEnemy(mini_ep, miniEnemyimg, eboom, 1);
			}

			/* 进入游戏中 */
			while (is_play) {
				/* 加载背景、玩家飞机 */
				BeginBatchDraw();// BeginBatchDraw和EndBatchDraw用于消除频闪，详情：https://docs.easyx.cn/zh-cn/other-func
				bg.Show();
				Sleep(4);
				flushmessage();
				Sleep(1);
				hp.Control();
				hp.Show();

				/* 按空格暂停 */
				if (GetAsyncKeyState(VK_SPACE) & 0x0001)
					while (!(GetAsyncKeyState(VK_SPACE) & 0x0001));

				/* 添加敌机 */
				DWORD currentTime = timeGetTime(); // 获取当前时间
				DWORD elapsedTime = currentTime - startTime; // 计算经过的时间
				if (static_cast<int>(elapsedTime) >= mini_time) {
					int x = rand() % 3;
					for (int i = 0; i < mini_density; i++) {// 补充敌机
						AddEnemy(mini_ep, miniEnemyimg, eboom, x);
					}
					startTime = currentTime;
				}

				/* 拾取道具进入对应状态 */
				switch (condition) {
					/* 正常状态 */
				case 0: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs.push_back(new Bullet(bulletimg, hp.GetRect()));// 我方子弹（普通）
					}

					/* 加载我方子弹 */
					auto bsit = bs.begin();
					while (bsit != bs.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit)->Show())
							bsit = bs.erase(bsit);
						else
							bsit++;
					}

					/* 加载敌方飞机 */
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
								kill_temp++;
							}

							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*mini_it)->GetRect())) {
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
									kill_temp++;
								}

								delete (*bit);
								bs.erase(bit);

								break;
							}
							bit++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					break;// 跳出case
				}

					  /* 道具1：加生命值（一次性道具） */
				case 1: {
					hp.heal();

					condition = 0;// 恢复正常状态

					break;// 跳出case
				}

					  /* 道具2：清空敌机和敌方子弹（一次性道具） */
				case 2: {
					/* 清空敌方飞机 */
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						if (!(*mini_it)->dying()) {
							(*mini_it)->Dies();
							kill[2]++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}

					condition = 0;// 恢复正常状态

					break;// 跳出case
				}

					  /* 道具3：双发子弹（一段时间） */
				case 3: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs2_1.push_back(new Bullet2_1(bulletimg, hp.GetRect()));// 我方子弹（双发子弹（左））
						bs2_2.push_back(new Bullet2_2(bulletimg, hp.GetRect()));// 我方子弹（双发子弹（右））

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit2_1 = bs2_1.begin();
					while (bsit2_1 != bs2_1.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit2_1)->Show())
							bsit2_1 = bs2_1.erase(bsit2_1);
						else
							bsit2_1++;
					}
					auto bsit2_2 = bs2_2.begin();
					while (bsit2_2 != bs2_2.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit2_2)->Show())
							bsit2_2 = bs2_2.erase(bsit2_2);
						else
							bsit2_2++;
					}

					/* 加载敌方飞机 */
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
							}

							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*mini_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								delete (*bit2_1);
								bs2_1.erase(bit2_1);

								break;
							}
							bit2_1++;
						}
						auto bit2_2 = bs2_2.begin();
						while (bit2_2 != bs2_2.end()) {
							if (RectDuangRect((*bit2_2)->GetRect(), (*mini_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								delete (*bit2_2);
								bs2_2.erase(bit2_2);

								break;
							}
							bit2_2++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					break;// 跳出case
				}

					  /* 道具4：分叉子弹（一段时间） */
				case 4: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs3_1.push_back(new Bullet3_1(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（中））
						bs3_2.push_back(new Bullet3_2(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（左））
						bs3_3.push_back(new Bullet3_3(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（右））

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit3_1 = bs3_1.begin();
					while (bsit3_1 != bs3_1.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_1)->Show())
							bsit3_1 = bs3_1.erase(bsit3_1);
						else
							bsit3_1++;
					}
					auto bsit3_2 = bs3_2.begin();
					while (bsit3_2 != bs3_2.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_2)->Show())
							bsit3_2 = bs3_2.erase(bsit3_2);
						else
							bsit3_2++;
					}
					auto bsit3_3 = bs3_3.begin();
					while (bsit3_3 != bs3_3.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_3)->Show())
							bsit3_3 = bs3_3.erase(bsit3_3);
						else
							bsit3_3++;
					}

					/* 加载敌方飞机 */
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
							}

							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*mini_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								delete (*bit3_1);
								bs3_1.erase(bit3_1);

								break;
							}
							bit3_1++;
						}
						auto bit3_2 = bs3_2.begin();
						while (bit3_2 != bs3_2.end()) {
							if (RectDuangRect((*bit3_2)->GetRect(), (*mini_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								delete (*bit3_2);
								bs3_2.erase(bit3_2);

								break;
							}
							bit3_2++;
						}
						auto bit3_3 = bs3_3.begin();
						while (bit3_3 != bs3_3.end()) {
							if (RectDuangRect((*bit3_3)->GetRect(), (*mini_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								delete (*bit3_3);
								bs3_3.erase(bit3_3);

								break;
							}
							bit3_3++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					break;// 跳出case
				}

					  /* 道具5：穿甲子弹（一段时间） */
				case 5: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs4.push_back(new Bullet4(bullet4img, hp.GetRect()));// 我方子弹（穿甲弹）

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit4 = bs4.begin();
					while (bsit4 != bs4.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit4)->Show())
							bsit4 = bs4.erase(bsit4);
						else
							bsit4++;
					}

					/* 加载敌方飞机 */
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
							}

							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*mini_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								break;
							}
							bit4++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					break;// 跳出case
				}
				}

				/* 每杀一定数量敌人送一个道具 */
				if ((condition == 0) && (kill_temp >= KILL_FOR_GIFT)) {
					/* 随机发放道具（未完成） */
					gift_index = rand() % 5;
					AddGift(gift, giftimg[gift_index]);

					kill_temp = 0;
					bullets_total = 0;
				}
				/* 加载道具 */
				auto gift_it = gift.begin();
				while (gift_it != gift.end()) {
					// 成功拾取道具
					if (RectDuangRect((*gift_it)->GetRect(), hp.GetRect())) {
						condition = gift_index + 1;

						delete (*gift_it);// 删除类指针
						gift.erase(gift_it);// 踢出容器
						gift_it = gift.begin();
						break;
					}
					// 未能拾取道具（已经飞出屏幕）
					if (!(*gift_it)->Show()) {
						delete (*gift_it);// 删除类指针
						gift.erase(gift_it);// 踢出容器
						gift_it = gift.begin();
					}
					else
						gift_it++;
				}

				/* 右上角实时显示击杀数和得分 */
				score = kill[0] * 3 + kill[1] * 5 + kill[2] * 1 + kill[3] * 7 + kill[4] * 31;
				PrintScore(kill, score);

				EndBatchDraw();// BeginBatchDraw和EndBatchDraw用于消除频闪				
			}

			stopBgmMusic();
			Over(kill, score);// 结算界面
			break;
		}

		// 无尽模式——第4关：大型敌机
		// 密度：giant_density = 2
		case 104: {
			/* 声明对象 */
			BG bg = BG(bgimg);// 背景
			Hero hp = Hero(heroimg);// 玩家飞机
			vector<giantEnemy*> giant_ep;// 敌机向量（大型）
			vector<Bullet*> bs;// 我方子弹向量（普通）
			vector<Bullet2_1*> bs2_1;// 我方子弹向量（双发子弹（左））
			vector<Bullet2_2*> bs2_2;// 我方子弹向量（双发子弹（右））
			vector<Bullet3_1*> bs3_1;// 我方子弹向量（分叉子弹（中））
			vector<Bullet3_2*> bs3_2;// 我方子弹向量（分叉子弹（左））
			vector<Bullet3_3*> bs3_3;// 我方子弹向量（分叉子弹（右））
			vector<Bullet4*> bs4;// 我方子弹向量（穿甲弹）
			vector<EBullet*> giant_ebs;// 敌方子弹向量（大型）
			vector<Gift*> gift;// 道具向量

			/* 定义基本变量 */
			int bsing = 0;// 控制我方子弹发射频率（普通）
			int giant_ebsing = 0;// 控制敌方子弹发射频率（大型）
			int giant_density = GIANT_DENSITY;// 控制敌机密度（大型）

			/* 定义计数器 */
			int kill[5] = { 0, 0, 0, 0, 0 };// 记录整局击杀数量:{普通，中型，小型，大型，BOSS}
			int score = 0;// 记录得分：{普通：3，中型：5，小型：1，大型：7，BOSS：31}
			int kill_temp = 0;// 记录当前杀敌数量（达到一定值后归零，用于确定发送道具时机）
			int bullets_total = 0;// 记录有道具期间发射子弹总数，用于切换道具状态
			int condition = 0;// 用于切换道具状态，默认为0
			int gift_index = 0;// 用于记录道具种类

			playBgmMusic();

			/* 添加开局敌机 */
			for (int i = 0; i < giant_density; i++) {
				AddEnemy(giant_ep, giantEnemyimg, eboom);
			}

			/* 进入游戏中 */
			while (is_play) {
				/* 加载背景、玩家飞机 */
				BeginBatchDraw();// BeginBatchDraw和EndBatchDraw用于消除频闪，详情：https://docs.easyx.cn/zh-cn/other-func
				bg.Show();
				Sleep(4);
				flushmessage();
				Sleep(1);
				hp.Control();
				hp.Show();

				/* 按空格暂停 */
				if (GetAsyncKeyState(VK_SPACE) & 0x0001)
					while (!(GetAsyncKeyState(VK_SPACE) & 0x0001));

				/* 添加敌方子弹 */
				giant_ebsing++;
				if (giant_ebsing == 101 - giant_ebs_frequency) {
					giant_ebsing = 0;
					for (auto& i : giant_ep)
						giant_ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// 敌方子弹（大型）
				}

				/* 添加敌机 */
				for (int i = 0; i < giant_density - giant_ep.size(); i++) {
					AddEnemy(giant_ep, giantEnemyimg, eboom);
				}

				/* 加载敌方子弹 */
				auto giant_ebsit = giant_ebs.begin();
				while (giant_ebsit != giant_ebs.end()) {
					// 我方飞机被击中
					if (RectDuangRect((*giant_ebsit)->GetRect(), hp.GetRect())) {
						/* 结果 */
						is_play = hp.hurt();

						giant_ebsit = giant_ebs.erase(giant_ebsit);
					}
					// 如果子弹飞出屏幕则去除
					else if (!(*giant_ebsit)->Show())
						giant_ebsit = giant_ebs.erase(giant_ebsit);
					else
						giant_ebsit++;
				}

				/* 拾取道具进入对应状态 */
				switch (condition) {
					/* 正常状态 */
				case 0: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs.push_back(new Bullet(bulletimg, hp.GetRect()));// 我方子弹（普通）
					}

					/* 加载我方子弹 */
					auto bsit = bs.begin();
					while (bsit != bs.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit)->Show())
							bsit = bs.erase(bsit);
						else
							bsit++;
					}

					/* 加载敌方飞机 */
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*giant_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*giant_it)->dying()) {
								(*giant_it)->Dies();
								kill[3]++;
								kill_temp++;
							}

							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*giant_it)->GetRect())) {
								/* 结果 */
								if((*giant_it)->hurt()){
									kill[3]++;
									kill_temp++;
								}

								delete (*bit);
								bs.erase(bit);

								break;
							}
							bit++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}
					break;// 跳出case
				}

					  /* 道具1：加生命值（一次性道具） */
				case 1: {
					hp.heal();

					condition = 0;// 恢复正常状态

					break;// 跳出case
				}

					  /* 道具2：清空敌机和敌方子弹（一次性道具） */
				case 2: {
					/* 清空敌方子弹 */
					auto giant_ebsit = giant_ebs.begin();
					while (giant_ebsit != giant_ebs.end()) {
						giant_ebsit = giant_ebs.erase(giant_ebsit);
					}

					/* 清空敌方飞机 */
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						if (!(*giant_it)->dying()) {
							(*giant_it)->Dies();
							kill[3]++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}

					condition = 0;// 恢复正常状态

					break;// 跳出case
				}

					  /* 道具3：双发子弹（一段时间） */
				case 3: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs2_1.push_back(new Bullet2_1(bulletimg, hp.GetRect()));// 我方子弹（双发子弹（左））
						bs2_2.push_back(new Bullet2_2(bulletimg, hp.GetRect()));// 我方子弹（双发子弹（右））

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit2_1 = bs2_1.begin();
					while (bsit2_1 != bs2_1.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit2_1)->Show())
							bsit2_1 = bs2_1.erase(bsit2_1);
						else
							bsit2_1++;
					}
					auto bsit2_2 = bs2_2.begin();
					while (bsit2_2 != bs2_2.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit2_2)->Show())
							bsit2_2 = bs2_2.erase(bsit2_2);
						else
							bsit2_2++;
					}

					/* 加载敌方飞机 */
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*giant_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*giant_it)->dying()) {
								(*giant_it)->Dies();
								kill[3]++;
							}

							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*giant_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*giant_it)->hurt()) {
									kill[3]++;
									kill_temp++;
								}

								delete (*bit2_1);
								bs2_1.erase(bit2_1);

								break;
							}
							bit2_1++;
						}
						auto bit2_2 = bs2_2.begin();
						while (bit2_2 != bs2_2.end()) {
							if (RectDuangRect((*bit2_2)->GetRect(), (*giant_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*giant_it)->hurt()) {
									kill[3]++;
									kill_temp++;
								}

								delete (*bit2_2);
								bs2_2.erase(bit2_2);

								break;
							}
							bit2_2++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}
					break;// 跳出case
				}

					  /* 道具4：分叉子弹（一段时间） */
				case 4: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs3_1.push_back(new Bullet3_1(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（中））
						bs3_2.push_back(new Bullet3_2(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（左））
						bs3_3.push_back(new Bullet3_3(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（右））

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit3_1 = bs3_1.begin();
					while (bsit3_1 != bs3_1.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_1)->Show())
							bsit3_1 = bs3_1.erase(bsit3_1);
						else
							bsit3_1++;
					}
					auto bsit3_2 = bs3_2.begin();
					while (bsit3_2 != bs3_2.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_2)->Show())
							bsit3_2 = bs3_2.erase(bsit3_2);
						else
							bsit3_2++;
					}
					auto bsit3_3 = bs3_3.begin();
					while (bsit3_3 != bs3_3.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_3)->Show())
							bsit3_3 = bs3_3.erase(bsit3_3);
						else
							bsit3_3++;
					}

					/* 加载敌方飞机 */
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*giant_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*giant_it)->dying()) {
								(*giant_it)->Dies();
								kill[3]++;
							}

							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*giant_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*giant_it)->hurt()) {
									kill[3]++;
									kill_temp++;
								}

								delete (*bit3_1);
								bs3_1.erase(bit3_1);

								break;
							}
							bit3_1++;
						}
						auto bit3_2 = bs3_2.begin();
						while (bit3_2 != bs3_2.end()) {
							if (RectDuangRect((*bit3_2)->GetRect(), (*giant_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*giant_it)->hurt()) {
									kill[3]++;
									kill_temp++;
								}

								delete (*bit3_2);
								bs3_2.erase(bit3_2);

								break;
							}
							bit3_2++;
						}
						auto bit3_3 = bs3_3.begin();
						while (bit3_3 != bs3_3.end()) {
							if (RectDuangRect((*bit3_3)->GetRect(), (*giant_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*giant_it)->hurt()) {
									kill[3]++;
									kill_temp++;
								}

								delete (*bit3_3);
								bs3_3.erase(bit3_3);

								break;
							}
							bit3_3++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}
					break;// 跳出case
				}

					  /* 道具5：穿甲子弹（一段时间） */
				case 5: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs4.push_back(new Bullet4(bullet4img, hp.GetRect()));// 我方子弹（穿甲弹）

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit4 = bs4.begin();
					while (bsit4 != bs4.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit4)->Show())
							bsit4 = bs4.erase(bsit4);
						else
							bsit4++;
					}

					/* 加载敌方飞机 */
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*giant_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*giant_it)->dying()) {
								(*giant_it)->Dies();
								kill[3]++;
							}

							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*giant_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*giant_it)->hurt()) {
									kill[3]++;
									kill_temp++;
								}

								break;
							}
							bit4++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}
					break;// 跳出case
				}
				}

				/* 每杀一定数量敌人送一个道具 */
				if ((condition == 0) && (kill_temp >= KILL_FOR_GIFT)) {
					/* 随机发放道具（未完成） */
					gift_index = rand() % 5;
					AddGift(gift, giftimg[gift_index]);

					kill_temp = 0;
					bullets_total = 0;
				}
				/* 加载道具 */
				auto gift_it = gift.begin();
				while (gift_it != gift.end()) {
					// 成功拾取道具
					if (RectDuangRect((*gift_it)->GetRect(), hp.GetRect())) {
						condition = gift_index + 1;

						delete (*gift_it);// 删除类指针
						gift.erase(gift_it);// 踢出容器
						gift_it = gift.begin();
						break;
					}
					// 未能拾取道具（已经飞出屏幕）
					if (!(*gift_it)->Show()) {
						delete (*gift_it);// 删除类指针
						gift.erase(gift_it);// 踢出容器
						gift_it = gift.begin();
					}
					else
						gift_it++;
				}

				/* 右上角实时显示击杀数和得分 */
				score = kill[0] * 3 + kill[1] * 5 + kill[2] * 1 + kill[3] * 7 + kill[4] * 31;
				PrintScore(kill, score);

				EndBatchDraw();// BeginBatchDraw和EndBatchDraw用于消除频闪				
			}

			stopBgmMusic();
			Over(kill, score);// 结算界面
			break;
		}

		// 无尽模式——第5关：BOSS
		// 密度：boss_density = 31
		case 105: {
			/* 声明对象 */
			BG bg = BG(bgimg);// 背景
			Hero hp = Hero(heroimg);// 玩家飞机
			vector<bossEnemy*> boss_ep;// 敌机向量（BOSS）
			vector<Bullet*> bs;// 我方子弹向量（普通）
			vector<Bullet2_1*> bs2_1;// 我方子弹向量（双发子弹（左））
			vector<Bullet2_2*> bs2_2;// 我方子弹向量（双发子弹（右））
			vector<Bullet3_1*> bs3_1;// 我方子弹向量（分叉子弹（中））
			vector<Bullet3_2*> bs3_2;// 我方子弹向量（分叉子弹（左））
			vector<Bullet3_3*> bs3_3;// 我方子弹向量（分叉子弹（右））
			vector<Bullet4*> bs4;// 我方子弹向量（穿甲弹）
			vector<BossSkill_1*> boss_skill_1;// BOSS子弹向量（skill_1）
			vector<BossSkill_2*> boss_skill_2;// BOSS子弹向量（skill_2）
			vector<BossSkill_3*> boss_skill_3;// BOSS子弹向量（skill_3）
			vector<Gift*> gift;// 道具向量

			/* 定义基本变量 */
			int bsing = 0;// 控制我方子弹发射频率（普通）
			int boss_ebsing = 0;// 控制敌方子弹发射频率（BOSS）
			int boss_density = BOSS_DENSITY;// 控制敌机密度（BOSS）

			/* 定义计数器 */
			int kill[5] = { 0, 0, 0, 0, 0 };// 记录整局击杀数量:{普通，中型，小型，大型，BOSS}
			int score = 0;// 记录得分：{普通：3，中型：5，小型：1，大型：7，BOSS：31}
			int kill_temp = 0;// 记录当前杀敌数量（达到一定值后归零，用于确定发送道具时机）
			int bullets_total = 0;// 记录有道具期间发射子弹总数，用于切换道具状态
			int condition = 0;// 用于切换道具状态，默认为0
			int gift_index = 0;// 用于记录道具种类

			playBgmMusic();

			/* 添加开局敌机 */
			for (int i = 0; i < boss_density; i++) {
				AddEnemy(boss_ep, bossEnemyimg, eboom);
			}

			/* 进入游戏中 */
			while (is_play) {
				/* 加载背景、玩家飞机 */
				BeginBatchDraw();// BeginBatchDraw和EndBatchDraw用于消除频闪，详情：https://docs.easyx.cn/zh-cn/other-func
				bg.Show();
				Sleep(4);
				flushmessage();
				Sleep(1);
				hp.Control();
				hp.Show();

				/* 按空格暂停 */
				if (GetAsyncKeyState(VK_SPACE) & 0x0001)
					while (!(GetAsyncKeyState(VK_SPACE) & 0x0001));

				/* 添加敌方子弹 */
				boss_ebsing++;
				if (boss_ebsing == 101 - boss_ebs_frequency) {
					boss_ebsing = 0;
					for (auto& i : boss_ep) {
						// boss_skill_1发射概率：50%
						if (rand() % 2 != 0)
							boss_skill_1.push_back(new BossSkill_1(bossSkill_1img, i->GetRect()));
						// boss_skill_2发射概率：100%
						boss_skill_2.push_back(new BossSkill_2(bossSkill_2img, i->GetRect()));
						// boss_skill_3发射概率：25%
						if (rand() % 4 == 0)
							boss_skill_3.push_back(new BossSkill_3(bossSkill_3img, i->GetRect()));
					}
				}

				/* 添加敌机 */
				for (int i = 0; i < boss_density - boss_ep.size(); i++) {
					AddEnemy(boss_ep, bossEnemyimg, eboom);
				}

				/* 加载敌方子弹 */
				auto boss_skill_1it = boss_skill_1.begin();
				while (boss_skill_1it != boss_skill_1.end()) {
					// 我方飞机被击中
					if (RectDuangRect((*boss_skill_1it)->GetRect(), hp.GetRect())) {
						/* 结果 */
						is_play = hp.hurt(2);

						boss_skill_1it = boss_skill_1.erase(boss_skill_1it);
					}
					else if (!(*boss_skill_1it)->Show())
						boss_skill_1it = boss_skill_1.erase(boss_skill_1it);
					else
						boss_skill_1it++;
				}
				auto boss_skill_2it = boss_skill_2.begin();
				while (boss_skill_2it != boss_skill_2.end()) {
					// 我方飞机被击中
					if (RectDuangRect((*boss_skill_2it)->GetRect(), hp.GetRect())) {
						/* 结果 */
						is_play = hp.hurt(1);

						boss_skill_2it = boss_skill_2.erase(boss_skill_2it);
					}
					else if (!(*boss_skill_2it)->Show())
						boss_skill_2it = boss_skill_2.erase(boss_skill_2it);
					else
						boss_skill_2it++;
				}
				auto boss_skill_3it = boss_skill_3.begin();
				while (boss_skill_3it != boss_skill_3.end()) {
					// 我方飞机被击中
					if (RectDuangRect((*boss_skill_3it)->GetRect(), hp.GetRect())) {
						/* 结果 */
						is_play = hp.hurt(HP);

						boss_skill_3it = boss_skill_3.erase(boss_skill_3it);
					}
					else if (!(*boss_skill_3it)->Show())
						boss_skill_3it = boss_skill_3.erase(boss_skill_3it);
					else
						boss_skill_3it++;
				}
				
				/* 拾取道具进入对应状态 */
				switch (condition) {
					/* 正常状态 */
				case 0: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs.push_back(new Bullet(bulletimg, hp.GetRect()));// 我方子弹（普通）
					}

					/* 加载我方子弹 */
					auto bsit = bs.begin();
					while (bsit != bs.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit)->Show())
							bsit = bs.erase(bsit);
						else
							bsit++;
					}

					/* 加载敌方飞机 */
					auto boss_it = boss_ep.begin();
					while (boss_it != boss_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*boss_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt(HP);

							break;
						}

						/* 如果我方子弹击中敌机 */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*boss_it)->GetRect())) {
								/* 结果 */
								if ((*boss_it)->hurt()) {
									kill[4]++;
									kill_temp++;
								}

								delete (*bit);
								bs.erase(bit);

								break;
							}
							bit++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*boss_it)->Show()) {
							delete (*boss_it);// 删除类指针
							boss_ep.erase(boss_it);// 踢出容器
							boss_it = boss_ep.begin();
						}
						else
							boss_it++;
					}
					break;// 跳出case
				}

					  /* 道具1：加生命值（一次性道具） */
				case 1: {
					hp.heal();

					condition = 0;// 恢复正常状态

					break;// 跳出case
				}

					  /* 道具2：清空敌机和敌方子弹（一次性道具） */
				case 2: {
					/* 清空敌方子弹 */
					auto boss_skill_1it = boss_skill_1.begin();
					while (boss_skill_1it != boss_skill_1.end()) {
						boss_skill_1it = boss_skill_1.erase(boss_skill_1it);
					}
					auto boss_skill_2it = boss_skill_2.begin();
					while (boss_skill_2it != boss_skill_2.end()) {
						boss_skill_2it = boss_skill_2.erase(boss_skill_2it);
					}
					auto boss_skill_3it = boss_skill_3.begin();
					while (boss_skill_3it != boss_skill_3.end()) {
						boss_skill_3it = boss_skill_3.erase(boss_skill_3it);
					}

					/* 清空敌方飞机 */
					auto boss_it = boss_ep.begin();
					while (boss_it != boss_ep.end()) {
						if (!(*boss_it)->dying()) {
							(*boss_it)->Dies();
							kill[4]++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*boss_it)->Show()) {
							delete (*boss_it);// 删除类指针
							boss_ep.erase(boss_it);// 踢出容器
							boss_it = boss_ep.begin();
						}
						else
							boss_it++;
					}

					condition = 0;// 恢复正常状态

					break;// 跳出case
				}

					  /* 道具3：双发子弹（一段时间） */
				case 3: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs2_1.push_back(new Bullet2_1(bulletimg, hp.GetRect()));// 我方子弹（双发子弹（左））
						bs2_2.push_back(new Bullet2_2(bulletimg, hp.GetRect()));// 我方子弹（双发子弹（右））

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit2_1 = bs2_1.begin();
					while (bsit2_1 != bs2_1.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit2_1)->Show())
							bsit2_1 = bs2_1.erase(bsit2_1);
						else
							bsit2_1++;
					}
					auto bsit2_2 = bs2_2.begin();
					while (bsit2_2 != bs2_2.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit2_2)->Show())
							bsit2_2 = bs2_2.erase(bsit2_2);
						else
							bsit2_2++;
					}

					/* 加载敌方飞机 */
					auto boss_it = boss_ep.begin();
					while (boss_it != boss_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*boss_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt(HP);

							break;
						}

						/* 如果我方子弹击中敌机 */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*boss_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*boss_it)->hurt()) {
									kill[4]++;
									kill_temp++;
								}

								delete (*bit2_1);
								bs2_1.erase(bit2_1);

								break;
							}
							bit2_1++;
						}
						auto bit2_2 = bs2_2.begin();
						while (bit2_2 != bs2_2.end()) {
							if (RectDuangRect((*bit2_2)->GetRect(), (*boss_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*boss_it)->hurt()) {
									kill[4]++;
									kill_temp++;
								}

								delete (*bit2_2);
								bs2_2.erase(bit2_2);

								break;
							}
							bit2_2++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*boss_it)->Show()) {
							delete (*boss_it);// 删除类指针
							boss_ep.erase(boss_it);// 踢出容器
							boss_it = boss_ep.begin();
						}
						else
							boss_it++;
					}
					break;// 跳出case
				}

					  /* 道具4：分叉子弹（一段时间） */
				case 4: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs3_1.push_back(new Bullet3_1(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（中））
						bs3_2.push_back(new Bullet3_2(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（左））
						bs3_3.push_back(new Bullet3_3(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（右））

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit3_1 = bs3_1.begin();
					while (bsit3_1 != bs3_1.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_1)->Show())
							bsit3_1 = bs3_1.erase(bsit3_1);
						else
							bsit3_1++;
					}
					auto bsit3_2 = bs3_2.begin();
					while (bsit3_2 != bs3_2.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_2)->Show())
							bsit3_2 = bs3_2.erase(bsit3_2);
						else
							bsit3_2++;
					}
					auto bsit3_3 = bs3_3.begin();
					while (bsit3_3 != bs3_3.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_3)->Show())
							bsit3_3 = bs3_3.erase(bsit3_3);
						else
							bsit3_3++;
					}

					/* 加载敌方飞机 */
					auto boss_it = boss_ep.begin();
					while (boss_it != boss_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*boss_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt(HP);

							break;
						}

						/* 如果我方子弹击中敌机 */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*boss_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*boss_it)->hurt()) {
									kill[4]++;
									kill_temp++;
								}

								delete (*bit3_1);
								bs3_1.erase(bit3_1);

								break;
							}
							bit3_1++;
						}
						auto bit3_2 = bs3_2.begin();
						while (bit3_2 != bs3_2.end()) {
							if (RectDuangRect((*bit3_2)->GetRect(), (*boss_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*boss_it)->hurt()) {
									kill[4]++;
									kill_temp++;
								}

								delete (*bit3_2);
								bs3_2.erase(bit3_2);

								break;
							}
							bit3_2++;
						}
						auto bit3_3 = bs3_3.begin();
						while (bit3_3 != bs3_3.end()) {
							if (RectDuangRect((*bit3_3)->GetRect(), (*boss_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*boss_it)->hurt()) {
									kill[4]++;
									kill_temp++;
								}

								delete (*bit3_3);
								bs3_3.erase(bit3_3);

								break;
							}
							bit3_3++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*boss_it)->Show()) {
							delete (*boss_it);// 删除类指针
							boss_ep.erase(boss_it);// 踢出容器
							boss_it = boss_ep.begin();
						}
						else
							boss_it++;
					}
					break;// 跳出case
				}

					  /* 道具5：穿甲子弹（一段时间） */
				case 5: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs4.push_back(new Bullet4(bullet4img, hp.GetRect()));// 我方子弹（穿甲弹）

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit4 = bs4.begin();
					while (bsit4 != bs4.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit4)->Show())
							bsit4 = bs4.erase(bsit4);
						else
							bsit4++;
					}

					/* 加载敌方飞机 */
					auto boss_it = boss_ep.begin();
					while (boss_it != boss_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*boss_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt(HP);

							break;
						}

						/* 如果我方子弹击中敌机 */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*boss_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*boss_it)->hurt()) {
									kill[4]++;
									kill_temp++;
								}

								break;
							}
							bit4++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*boss_it)->Show()) {
							delete (*boss_it);// 删除类指针
							boss_ep.erase(boss_it);// 踢出容器
							boss_it = boss_ep.begin();
						}
						else
							boss_it++;
					}
					break;// 跳出case
				}
				}

				/* 每杀一定数量敌人送一个道具 */
				if ((condition == 0) && (kill_temp >= KILL_FOR_GIFT)) {
					/* 随机发放道具（未完成） */
					gift_index = rand() % 5;
					AddGift(gift, giftimg[gift_index]);

					kill_temp = 0;
					bullets_total = 0;
				}
				/* 加载道具 */
				auto gift_it = gift.begin();
				while (gift_it != gift.end()) {
					// 成功拾取道具
					if (RectDuangRect((*gift_it)->GetRect(), hp.GetRect())) {
						condition = gift_index + 1;

						delete (*gift_it);// 删除类指针
						gift.erase(gift_it);// 踢出容器
						gift_it = gift.begin();
						break;
					}
					// 未能拾取道具（已经飞出屏幕）
					if (!(*gift_it)->Show()) {
						delete (*gift_it);// 删除类指针
						gift.erase(gift_it);// 踢出容器
						gift_it = gift.begin();
					}
					else
						gift_it++;
				}

				/* 右上角实时显示击杀数和得分 */
				score = kill[0] * 3 + kill[1] * 5 + kill[2] * 1 + kill[3] * 7 + kill[4] * 31;
				PrintScore(kill, score);

				EndBatchDraw();// BeginBatchDraw和EndBatchDraw用于消除频闪				
			}

			stopBgmMusic();
			Over(kill, score);// 结算界面
			break;
		}

		// 闯关模式——第1关
		// 普通敌机
		// score 300
		case 201: {
			/* 声明对象 */
			BG bg = BG(bgimg);// 背景
			Hero hp = Hero(heroimg);// 玩家飞机
			vector<Enemy*> ep;// 敌机向量（普通）
			vector<Bullet*> bs;// 我方子弹向量（普通）
			vector<Bullet2_1*> bs2_1;// 我方子弹向量（双发子弹（左））
			vector<Bullet2_2*> bs2_2;// 我方子弹向量（双发子弹（右））
			vector<Bullet3_1*> bs3_1;// 我方子弹向量（分叉子弹（中））
			vector<Bullet3_2*> bs3_2;// 我方子弹向量（分叉子弹（左））
			vector<Bullet3_3*> bs3_3;// 我方子弹向量（分叉子弹（右））
			vector<Bullet4*> bs4;// 我方子弹向量（穿甲弹）
			vector<EBullet*> ebs;// 敌方子弹向量（普通）
			vector<Gift*> gift;// 道具向量

			/* 定义基本变量 */
			int bsing = 0;// 控制我方子弹发射频率（普通）
			int ebsing = 0;// 控制敌方子弹发射频率（普通）
			int density = DENSITY;// 控制敌机密度（普通）

			/* 定义计数器 */
			int kill[5] = { 0, 0, 0, 0, 0 };// 记录整局击杀数量:{普通，中型，小型，大型，BOSS}
			int score = 0;// 记录得分：{普通：3，中型：5，小型：1，大型：7，BOSS：31}
			int kill_temp = 0;// 记录当前杀敌数量（达到一定值后归零，用于确定发送道具时机）
			int bullets_total = 0;// 记录有道具期间发射子弹总数，用于切换道具状态
			int condition = 0;// 用于切换道具状态，默认为0
			int gift_index = 0;// 用于记录道具种类
			bool flag = false;// 判断是否过关

			playBgmMusic();

			/* 添加开局敌机 */
			for (int i = 0; i < density; i++) {
				AddEnemy(ep, enemyimg, eboom);
			}

			/* 进入游戏中 */
			while (is_play) {
				/* 加载背景、玩家飞机 */
				BeginBatchDraw();// BeginBatchDraw和EndBatchDraw用于消除频闪，详情：https://docs.easyx.cn/zh-cn/other-func
				bg.Show();
				Sleep(4);
				flushmessage();
				Sleep(1);
				hp.Control();
				hp.Show();

				/* 按空格暂停 */
				if (GetAsyncKeyState(VK_SPACE) & 0x0001)
					while (!(GetAsyncKeyState(VK_SPACE) & 0x0001));

				/* 添加敌方子弹 */
				ebsing++;
				if (ebsing == 101 - ebs_frequency) {
					ebsing = 0;
					for (auto& i : ep)
						ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// 敌方子弹（普通）
				}

				/* 添加敌机 */
				for (int i = 0; i < density - ep.size(); i++) {
					AddEnemy(ep, enemyimg, eboom);
				}

				/* 加载敌方子弹 */
				auto ebsit = ebs.begin();
				while (ebsit != ebs.end()) {
					// 我方飞机被击中
					if (RectDuangRect((*ebsit)->GetRect(), hp.GetRect())) {
						/* 结果 */
						is_play = hp.hurt();

						ebsit = ebs.erase(ebsit);
					}
					// 如果子弹飞出屏幕则去除
					else if (!(*ebsit)->Show())
						ebsit = ebs.erase(ebsit);
					else
						ebsit++;
				}

				/* 拾取道具进入对应状态 */
				switch (condition) {
					/* 正常状态 */
				case 0: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs.push_back(new Bullet(bulletimg, hp.GetRect()));// 我方子弹（普通）
					}

					/* 加载我方子弹 */
					auto bsit = bs.begin();
					while (bsit != bs.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit)->Show())
							bsit = bs.erase(bsit);
						else
							bsit++;
					}

					/* 加载敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
								kill_temp++;
							}

							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*it)->GetRect())) {
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
									kill_temp++;
								}

								delete (*bit);
								bs.erase(bit);

								break;
							}
							bit++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}
					break;// 跳出case
				}

					  /* 道具1：加生命值（一次性道具） */
				case 1: {
					hp.heal();

					condition = 0;// 恢复正常状态

					break;// 跳出case
				}

					  /* 道具2：清空敌机和敌方子弹（一次性道具） */
				case 2: {
					/* 清空敌方子弹 */
					auto ebsit = ebs.begin();
					while (ebsit != ebs.end()) {
						ebsit = ebs.erase(ebsit);
					}

					/* 清空敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						if (!(*it)->dying()) {
							(*it)->Dies();
							kill[0]++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}

					condition = 0;// 恢复正常状态

					break;// 跳出case
				}

					  /* 道具3：双发子弹（一段时间） */
				case 3: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs2_1.push_back(new Bullet2_1(bulletimg, hp.GetRect()));// 我方子弹（双发子弹（左））
						bs2_2.push_back(new Bullet2_2(bulletimg, hp.GetRect()));// 我方子弹（双发子弹（右））

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit2_1 = bs2_1.begin();
					while (bsit2_1 != bs2_1.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit2_1)->Show())
							bsit2_1 = bs2_1.erase(bsit2_1);
						else
							bsit2_1++;
					}
					auto bsit2_2 = bs2_2.begin();
					while (bsit2_2 != bs2_2.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit2_2)->Show())
							bsit2_2 = bs2_2.erase(bsit2_2);
						else
							bsit2_2++;
					}

					/* 加载敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}

							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								delete (*bit2_1);
								bs2_1.erase(bit2_1);

								break;
							}
							bit2_1++;
						}
						auto bit2_2 = bs2_2.begin();
						while (bit2_2 != bs2_2.end()) {
							if (RectDuangRect((*bit2_2)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}


								delete (*bit2_2);
								bs2_2.erase(bit2_2);

								break;
							}
							bit2_2++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}
					break;// 跳出case
				}

					  /* 道具4：分叉子弹（一段时间） */
				case 4: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs3_1.push_back(new Bullet3_1(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（中））
						bs3_2.push_back(new Bullet3_2(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（左））
						bs3_3.push_back(new Bullet3_3(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（右））

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit3_1 = bs3_1.begin();
					while (bsit3_1 != bs3_1.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_1)->Show())
							bsit3_1 = bs3_1.erase(bsit3_1);
						else
							bsit3_1++;
					}
					auto bsit3_2 = bs3_2.begin();
					while (bsit3_2 != bs3_2.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_2)->Show())
							bsit3_2 = bs3_2.erase(bsit3_2);
						else
							bsit3_2++;
					}
					auto bsit3_3 = bs3_3.begin();
					while (bsit3_3 != bs3_3.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_3)->Show())
							bsit3_3 = bs3_3.erase(bsit3_3);
						else
							bsit3_3++;
					}

					/* 加载敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}


							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								delete (*bit3_1);
								bs3_1.erase(bit3_1);

								break;
							}
							bit3_1++;
						}
						auto bit3_2 = bs3_2.begin();
						while (bit3_2 != bs3_2.end()) {
							if (RectDuangRect((*bit3_2)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								delete (*bit3_2);
								bs3_2.erase(bit3_2);

								break;
							}
							bit3_2++;
						}
						auto bit3_3 = bs3_3.begin();
						while (bit3_3 != bs3_3.end()) {
							if (RectDuangRect((*bit3_3)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								delete (*bit3_3);
								bs3_3.erase(bit3_3);

								break;
							}
							bit3_3++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}
					break;// 跳出case
				}

					  /* 道具5：穿甲子弹（一段时间） */
				case 5: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs4.push_back(new Bullet4(bullet4img, hp.GetRect()));// 我方子弹（穿甲弹）

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit4 = bs4.begin();
					while (bsit4 != bs4.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit4)->Show())
							bsit4 = bs4.erase(bsit4);
						else
							bsit4++;
					}

					/* 加载敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}

							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								break;
							}
							bit4++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}
					break;// 跳出case
				}
				}

				/* 每杀一定数量敌人送一个道具 */
				if ((condition == 0) && (kill_temp >= KILL_FOR_GIFT)) {
					/* 随机发放道具（未完成） */
					gift_index = rand() % 5;
					AddGift(gift, giftimg[gift_index]);

					kill_temp = 0;
					bullets_total = 0;
				}
				/* 加载道具 */
				auto gift_it = gift.begin();
				while (gift_it != gift.end()) {
					// 成功拾取道具
					if (RectDuangRect((*gift_it)->GetRect(), hp.GetRect())) {
						condition = gift_index + 1;

						delete (*gift_it);// 删除类指针
						gift.erase(gift_it);// 踢出容器
						gift_it = gift.begin();
						break;
					}
					// 未能拾取道具（已经飞出屏幕）
					if (!(*gift_it)->Show()) {
						delete (*gift_it);// 删除类指针
						gift.erase(gift_it);// 踢出容器
						gift_it = gift.begin();
					}
					else
						gift_it++;
				}

				/* 右上角实时显示击杀数和得分 */
				score = kill[0] * 3 + kill[1] * 5 + kill[2] * 1 + kill[3] * 7 + kill[4] * 31;
				PrintScore(kill, score);

				/* 检测是否过关 */
				if (score >= SCORE_1) {
					flag = true;
					is_play = false;
				}

				EndBatchDraw();// BeginBatchDraw和EndBatchDraw用于消除频闪				
			}

			stopBgmMusic();
			Over(kill, score, flag);// 结算界面
			break;
		}

		// 闯关模式——第2关
		// 普通敌机、中型敌机
		// score 500
		case 202: {
			/* 声明对象 */
			BG bg = BG(bgimg2);// 背景
			Hero hp = Hero(heroimg);// 玩家飞机
			vector<Enemy*> ep;// 敌机向量（普通）
			vector<midEnemy*> mid_ep;// 敌机向量（中型）
			vector<Bullet*> bs;// 我方子弹向量（普通）
			vector<Bullet2_1*> bs2_1;// 我方子弹向量（双发子弹（左））
			vector<Bullet2_2*> bs2_2;// 我方子弹向量（双发子弹（右））
			vector<Bullet3_1*> bs3_1;// 我方子弹向量（分叉子弹（中））
			vector<Bullet3_2*> bs3_2;// 我方子弹向量（分叉子弹（左））
			vector<Bullet3_3*> bs3_3;// 我方子弹向量（分叉子弹（右））
			vector<Bullet4*> bs4;// 我方子弹向量（穿甲弹）
			vector<EBullet*> ebs;// 敌方子弹向量（普通）
			vector<EBullet*> mid_ebs;// 敌方子弹向量（中型）
			vector<Gift*> gift;// 道具向量

			/* 定义基本变量 */
			int bsing = 0;// 控制我方子弹发射频率（普通）
			int ebsing = 0;// 控制敌方子弹发射频率（普通）
			int mid_ebsing = 0;// 控制敌方子弹发射频率（中型）
			int density = DENSITY;// 控制敌机密度（普通）
			int mid_density = MID_DENSITY;// 控制敌机密度（中型）

			/* 定义计数器 */
			int kill[5] = { 0, 0, 0, 0, 0 };// 记录整局击杀数量:{普通，中型，小型，大型，BOSS}
			int score = 0;// 记录得分：{普通：3，中型：5，小型：1，大型：7，BOSS：31}
			int kill_temp = 0;// 记录当前杀敌数量（达到一定值后归零，用于确定发送道具时机）
			int bullets_total = 0;// 记录有道具期间发射子弹总数，用于切换道具状态
			int condition = 0;// 用于切换道具状态，默认为0
			int gift_index = 0;// 用于记录道具种类
			bool flag = false;// 判断是否过关

			playBgmMusic();

			/* 添加开局敌机 */
			for (int i = 0; i < density; i++) {
				AddEnemy(ep, enemyimg, eboom);
			}

			/* 进入游戏中 */
			while (is_play) {
				/* 加载背景、玩家飞机 */
				BeginBatchDraw();// BeginBatchDraw和EndBatchDraw用于消除频闪，详情：https://docs.easyx.cn/zh-cn/other-func
				bg.Show();
				Sleep(4);
				flushmessage();
				Sleep(1);
				hp.Control();
				hp.Show();

				/* 按空格暂停 */
				if (GetAsyncKeyState(VK_SPACE) & 0x0001)
					while (!(GetAsyncKeyState(VK_SPACE) & 0x0001));

				/* 添加敌方子弹 */
				ebsing++;
				if (ebsing == 101 - ebs_frequency) {
					ebsing = 0;
					for (auto& i : ep)
						ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// 敌方子弹（普通）
				}
				mid_ebsing++;
				if (mid_ebsing == 101 - mid_ebs_frequency) {
					mid_ebsing = 0;
					for (auto& i : mid_ep)
						mid_ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// 敌方子弹（中型）
				}

				/* 添加敌机 */
				for (int i = 0; i < density - ep.size(); i++) {
					AddEnemy(ep, enemyimg, eboom);
				}
				for (int i = 0; i < mid_density - mid_ep.size(); i++) {
					AddEnemy(mid_ep, midEnemyimg, eboom);
				}

				/* 加载敌方子弹 */
				auto ebsit = ebs.begin();
				while (ebsit != ebs.end()) {
					// 我方飞机被击中
					if (RectDuangRect((*ebsit)->GetRect(), hp.GetRect())) {
						/* 结果 */
						is_play = hp.hurt();

						ebsit = ebs.erase(ebsit);
					}
					// 如果子弹飞出屏幕则去除
					else if (!(*ebsit)->Show())
						ebsit = ebs.erase(ebsit);
					else
						ebsit++;
				}
				auto mid_ebsit = mid_ebs.begin();
				while (mid_ebsit != mid_ebs.end()) {
					// 我方飞机被击中
					if (RectDuangRect((*mid_ebsit)->GetRect(), hp.GetRect())) {
						/* 结果 */
						is_play = hp.hurt();

						mid_ebsit = mid_ebs.erase(mid_ebsit);
					}
					// 如果子弹飞出屏幕则去除
					else if (!(*mid_ebsit)->Show())
						mid_ebsit = mid_ebs.erase(mid_ebsit);
					else
						mid_ebsit++;
				}

				/* 拾取道具进入对应状态 */
				switch (condition) {
					/* 正常状态 */
				case 0: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs.push_back(new Bullet(bulletimg, hp.GetRect()));// 我方子弹（普通）
					}

					/* 加载我方子弹 */
					auto bsit = bs.begin();
					while (bsit != bs.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit)->Show())
							bsit = bs.erase(bsit);
						else
							bsit++;
					}

					/* 加载敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
								kill_temp++;
							}

							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*it)->GetRect())) {
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
									kill_temp++;
								}

								delete (*bit);
								bs.erase(bit);

								break;
							}
							bit++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
								kill_temp++;
							}

							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*mid_it)->GetRect())) {
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit);
								bs.erase(bit);

								break;
							}
							bit++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}

					break;// 跳出case
				}

					  /* 道具1：加生命值（一次性道具） */
				case 1: {
					hp.heal();

					condition = 0;// 恢复正常状态

					break;// 跳出case
				}

					  /* 道具2：清空敌机和敌方子弹（一次性道具） */
				case 2: {
					/* 清空敌方子弹 */
					auto ebsit = ebs.begin();
					while (ebsit != ebs.end()) {
						ebsit = ebs.erase(ebsit);
					}
					auto mid_ebsit = mid_ebs.begin();
					while (mid_ebsit != mid_ebs.end()) {
						mid_ebsit = mid_ebs.erase(mid_ebsit);
					}

					/* 清空敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						if (!(*it)->dying()) {
							(*it)->Dies();
							kill[0]++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						if (!(*mid_it)->dying()) {
							(*mid_it)->Dies();
							kill[1]++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}

					condition = 0;// 恢复正常状态

					break;// 跳出case
				}

					  /* 道具3：双发子弹（一段时间） */
				case 3: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs2_1.push_back(new Bullet2_1(bulletimg, hp.GetRect()));// 我方子弹（双发子弹（左））
						bs2_2.push_back(new Bullet2_2(bulletimg, hp.GetRect()));// 我方子弹（双发子弹（右））

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit2_1 = bs2_1.begin();
					while (bsit2_1 != bs2_1.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit2_1)->Show())
							bsit2_1 = bs2_1.erase(bsit2_1);
						else
							bsit2_1++;
					}
					auto bsit2_2 = bs2_2.begin();
					while (bsit2_2 != bs2_2.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit2_2)->Show())
							bsit2_2 = bs2_2.erase(bsit2_2);
						else
							bsit2_2++;
					}

					/* 加载敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}

							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								delete (*bit2_1);
								bs2_1.erase(bit2_1);

								break;
							}
							bit2_1++;
						}
						auto bit2_2 = bs2_2.begin();
						while (bit2_2 != bs2_2.end()) {
							if (RectDuangRect((*bit2_2)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}


								delete (*bit2_2);
								bs2_2.erase(bit2_2);

								break;
							}
							bit2_2++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit2_1);
								bs2_1.erase(bit2_1);

								break;
							}
							bit2_1++;
						}
						auto bit2_2 = bs2_2.begin();
						while (bit2_2 != bs2_2.end()) {
							if (RectDuangRect((*bit2_2)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit2_2);
								bs2_2.erase(bit2_2);

								break;
							}
							bit2_2++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}

					break;// 跳出case
				}

					  /* 道具4：分叉子弹（一段时间） */
				case 4: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs3_1.push_back(new Bullet3_1(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（中））
						bs3_2.push_back(new Bullet3_2(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（左））
						bs3_3.push_back(new Bullet3_3(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（右））

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit3_1 = bs3_1.begin();
					while (bsit3_1 != bs3_1.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_1)->Show())
							bsit3_1 = bs3_1.erase(bsit3_1);
						else
							bsit3_1++;
					}
					auto bsit3_2 = bs3_2.begin();
					while (bsit3_2 != bs3_2.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_2)->Show())
							bsit3_2 = bs3_2.erase(bsit3_2);
						else
							bsit3_2++;
					}
					auto bsit3_3 = bs3_3.begin();
					while (bsit3_3 != bs3_3.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_3)->Show())
							bsit3_3 = bs3_3.erase(bsit3_3);
						else
							bsit3_3++;
					}

					/* 加载敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}


							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								delete (*bit3_1);
								bs3_1.erase(bit3_1);

								break;
							}
							bit3_1++;
						}
						auto bit3_2 = bs3_2.begin();
						while (bit3_2 != bs3_2.end()) {
							if (RectDuangRect((*bit3_2)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								delete (*bit3_2);
								bs3_2.erase(bit3_2);

								break;
							}
							bit3_2++;
						}
						auto bit3_3 = bs3_3.begin();
						while (bit3_3 != bs3_3.end()) {
							if (RectDuangRect((*bit3_3)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								delete (*bit3_3);
								bs3_3.erase(bit3_3);

								break;
							}
							bit3_3++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit3_1);
								bs3_1.erase(bit3_1);

								break;
							}
							bit3_1++;
						}
						auto bit3_2 = bs3_2.begin();
						while (bit3_2 != bs3_2.end()) {
							if (RectDuangRect((*bit3_2)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit3_2);
								bs3_2.erase(bit3_2);

								break;
							}
							bit3_2++;
						}
						auto bit3_3 = bs3_3.begin();
						while (bit3_3 != bs3_3.end()) {
							if (RectDuangRect((*bit3_3)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit3_3);
								bs3_3.erase(bit3_3);

								break;
							}
							bit3_3++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}

					break;// 跳出case
				}

					  /* 道具5：穿甲子弹（一段时间） */
				case 5: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs4.push_back(new Bullet4(bullet4img, hp.GetRect()));// 我方子弹（穿甲弹）

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit4 = bs4.begin();
					while (bsit4 != bs4.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit4)->Show())
							bsit4 = bs4.erase(bsit4);
						else
							bsit4++;
					}

					/* 加载敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}

							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								break;
							}
							bit4++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								break;
							}
							bit4++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}

					break;// 跳出case
				}
				}

				/* 每杀一定数量敌人送一个道具 */
				if ((condition == 0) && (kill_temp >= KILL_FOR_GIFT)) {
					/* 随机发放道具（未完成） */
					gift_index = rand() % 5;
					AddGift(gift, giftimg[gift_index]);

					kill_temp = 0;
					bullets_total = 0;
				}
				/* 加载道具 */
				auto gift_it = gift.begin();
				while (gift_it != gift.end()) {
					// 成功拾取道具
					if (RectDuangRect((*gift_it)->GetRect(), hp.GetRect())) {
						condition = gift_index + 1;

						delete (*gift_it);// 删除类指针
						gift.erase(gift_it);// 踢出容器
						gift_it = gift.begin();
						break;
					}
					// 未能拾取道具（已经飞出屏幕）
					if (!(*gift_it)->Show()) {
						delete (*gift_it);// 删除类指针
						gift.erase(gift_it);// 踢出容器
						gift_it = gift.begin();
					}
					else
						gift_it++;
				}

				/* 右上角实时显示击杀数和得分 */
				score = kill[0] * 3 + kill[1] * 5 + kill[2] * 1 + kill[3] * 7 + kill[4] * 31;
				PrintScore(kill, score);

				/* 检测是否过关 */
				if (score >= SCORE_2) {
					flag = true;
					is_play = false;
				}

				EndBatchDraw();// BeginBatchDraw和EndBatchDraw用于消除频闪				
			}

			stopBgmMusic();
			Over(kill, score, flag);// 结算界面
			break;
		}

		// 闯关模式——第3关
		// 普通敌机、中型敌机、小型敌机
		// score 700
		case 203: {
			/* 声明对象 */
			BG bg = BG(bgimg3);// 背景
			Hero hp = Hero(heroimg2);// 玩家飞机
			vector<Enemy*> ep;// 敌机向量（普通）
			vector<midEnemy*> mid_ep;// 敌机向量（中型）
			vector<miniEnemy*> mini_ep;// 敌机向量（小型）
			vector<Bullet*> bs;// 我方子弹向量（普通）
			vector<Bullet2_1*> bs2_1;// 我方子弹向量（双发子弹（左））
			vector<Bullet2_2*> bs2_2;// 我方子弹向量（双发子弹（右））
			vector<Bullet3_1*> bs3_1;// 我方子弹向量（分叉子弹（中））
			vector<Bullet3_2*> bs3_2;// 我方子弹向量（分叉子弹（左））
			vector<Bullet3_3*> bs3_3;// 我方子弹向量（分叉子弹（右））
			vector<Bullet4*> bs4;// 我方子弹向量（穿甲弹）
			vector<EBullet*> ebs;// 敌方子弹向量（普通）
			vector<EBullet*> mid_ebs;// 敌方子弹向量（中型）
			vector<Gift*> gift;// 道具向量

			/* 定义基本变量 */
			int bsing = 0;// 控制我方子弹发射频率（普通）
			int ebsing = 0;// 控制敌方子弹发射频率（普通）
			int mid_ebsing = 0;// 控制敌方子弹发射频率（中型）
			int density = DENSITY;// 控制敌机密度（普通）
			int mid_density = MID_DENSITY;// 控制敌机密度（中型）
			int mini_density = MINI_DENSITY;// 控制敌机密度（小型）

			/* 定义计数器 */
			int kill[5] = { 0, 0, 0, 0, 0 };// 记录整局击杀数量:{普通，中型，小型，大型，BOSS}
			int score = 0;// 记录得分：{普通：3，中型：5，小型：1，大型：7，BOSS：31}
			int kill_temp = 0;// 记录当前杀敌数量（达到一定值后归零，用于确定发送道具时机）
			int bullets_total = 0;// 记录有道具期间发射子弹总数，用于切换道具状态
			int condition = 0;// 用于切换道具状态，默认为0
			int gift_index = 0;// 用于记录道具种类
			bool flag = false;// 判断是否过关

			/* 记录时间 */
			DWORD startTime = timeGetTime();// 获取开始时间
			int mini_time = 4000;// 小型敌机刷新时间

			playBgmMusic();

			/* 添加开局敌机 */
			for (int i = 0; i < density; i++) {
				AddEnemy(ep, enemyimg, eboom);
			}

			/* 进入游戏中 */
			while (is_play) {
				/* 加载背景、玩家飞机 */
				BeginBatchDraw();// BeginBatchDraw和EndBatchDraw用于消除频闪，详情：https://docs.easyx.cn/zh-cn/other-func
				bg.Show();
				Sleep(4);
				flushmessage();
				Sleep(1);
				hp.Control();
				hp.Show();

				/* 按空格暂停 */
				if (GetAsyncKeyState(VK_SPACE) & 0x0001)
					while (!(GetAsyncKeyState(VK_SPACE) & 0x0001));

				/* 添加敌方子弹 */
				ebsing++;
				if (ebsing == 101 - ebs_frequency) {
					ebsing = 0;
					for (auto& i : ep)
						ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// 敌方子弹（普通）
				}
				mid_ebsing++;
				if (mid_ebsing == 101 - mid_ebs_frequency) {
					mid_ebsing = 0;
					for (auto& i : mid_ep)
						mid_ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// 敌方子弹（中型）
				}

				/* 添加敌机 */
				for (int i = 0; i < density - ep.size(); i++) {
					AddEnemy(ep, enemyimg, eboom);
				}
				for (int i = 0; i < mid_density - mid_ep.size(); i++) {
					AddEnemy(mid_ep, midEnemyimg, eboom);
				}
				DWORD currentTime = timeGetTime(); // 获取当前时间
				DWORD elapsedTime = currentTime - startTime; // 计算经过的时间
				if (static_cast<int>(elapsedTime) >= mini_time) {
					int x = rand() % 3;
					for (int i = 0; i < mini_density; i++) {// 补充敌机
						AddEnemy(mini_ep, miniEnemyimg, eboom, x);
					}
					startTime = currentTime;
				}

				/* 加载敌方子弹 */
				auto ebsit = ebs.begin();
				while (ebsit != ebs.end()) {
					// 我方飞机被击中
					if (RectDuangRect((*ebsit)->GetRect(), hp.GetRect())) {
						/* 结果 */
						is_play = hp.hurt();

						ebsit = ebs.erase(ebsit);
					}
					// 如果子弹飞出屏幕则去除
					else if (!(*ebsit)->Show())
						ebsit = ebs.erase(ebsit);
					else
						ebsit++;
				}
				auto mid_ebsit = mid_ebs.begin();
				while (mid_ebsit != mid_ebs.end()) {
					// 我方飞机被击中
					if (RectDuangRect((*mid_ebsit)->GetRect(), hp.GetRect())) {
						/* 结果 */
						is_play = hp.hurt();

						mid_ebsit = mid_ebs.erase(mid_ebsit);
					}
					// 如果子弹飞出屏幕则去除
					else if (!(*mid_ebsit)->Show())
						mid_ebsit = mid_ebs.erase(mid_ebsit);
					else
						mid_ebsit++;
				}

				/* 拾取道具进入对应状态 */
				switch (condition) {
					/* 正常状态 */
				case 0: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs.push_back(new Bullet(bulletimg, hp.GetRect()));// 我方子弹（普通）
					}

					/* 加载我方子弹 */
					auto bsit = bs.begin();
					while (bsit != bs.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit)->Show())
							bsit = bs.erase(bsit);
						else
							bsit++;
					}

					/* 加载敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
								kill_temp++;
							}

							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*it)->GetRect())) {
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
									kill_temp++;
								}

								delete (*bit);
								bs.erase(bit);

								break;
							}
							bit++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
								kill_temp++;
							}

							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*mid_it)->GetRect())) {
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit);
								bs.erase(bit);

								break;
							}
							bit++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
								kill_temp++;
							}

							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*mini_it)->GetRect())) {
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
									kill_temp++;
								}

								delete (*bit);
								bs.erase(bit);

								break;
							}
							bit++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}

					break;// 跳出case
				}

					  /* 道具1：加生命值（一次性道具） */
				case 1: {
					hp.heal();

					condition = 0;// 恢复正常状态

					break;// 跳出case
				}

					  /* 道具2：清空敌机和敌方子弹（一次性道具） */
				case 2: {
					/* 清空敌方子弹 */
					auto ebsit = ebs.begin();
					while (ebsit != ebs.end()) {
						ebsit = ebs.erase(ebsit);
					}
					auto mid_ebsit = mid_ebs.begin();
					while (mid_ebsit != mid_ebs.end()) {
						mid_ebsit = mid_ebs.erase(mid_ebsit);
					}

					/* 清空敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						if (!(*it)->dying()) {
							(*it)->Dies();
							kill[0]++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						if (!(*mid_it)->dying()) {
							(*mid_it)->Dies();
							kill[1]++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						if (!(*mini_it)->dying()) {
							(*mini_it)->Dies();
							kill[2]++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}

					condition = 0;// 恢复正常状态

					break;// 跳出case
				}

					  /* 道具3：双发子弹（一段时间） */
				case 3: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs2_1.push_back(new Bullet2_1(bulletimg, hp.GetRect()));// 我方子弹（双发子弹（左））
						bs2_2.push_back(new Bullet2_2(bulletimg, hp.GetRect()));// 我方子弹（双发子弹（右））

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit2_1 = bs2_1.begin();
					while (bsit2_1 != bs2_1.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit2_1)->Show())
							bsit2_1 = bs2_1.erase(bsit2_1);
						else
							bsit2_1++;
					}
					auto bsit2_2 = bs2_2.begin();
					while (bsit2_2 != bs2_2.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit2_2)->Show())
							bsit2_2 = bs2_2.erase(bsit2_2);
						else
							bsit2_2++;
					}

					/* 加载敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}

							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								delete (*bit2_1);
								bs2_1.erase(bit2_1);

								break;
							}
							bit2_1++;
						}
						auto bit2_2 = bs2_2.begin();
						while (bit2_2 != bs2_2.end()) {
							if (RectDuangRect((*bit2_2)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}


								delete (*bit2_2);
								bs2_2.erase(bit2_2);

								break;
							}
							bit2_2++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit2_1);
								bs2_1.erase(bit2_1);

								break;
							}
							bit2_1++;
						}
						auto bit2_2 = bs2_2.begin();
						while (bit2_2 != bs2_2.end()) {
							if (RectDuangRect((*bit2_2)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit2_2);
								bs2_2.erase(bit2_2);

								break;
							}
							bit2_2++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
							}

							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*mini_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								delete (*bit2_1);
								bs2_1.erase(bit2_1);

								break;
							}
							bit2_1++;
						}
						auto bit2_2 = bs2_2.begin();
						while (bit2_2 != bs2_2.end()) {
							if (RectDuangRect((*bit2_2)->GetRect(), (*mini_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								delete (*bit2_2);
								bs2_2.erase(bit2_2);

								break;
							}
							bit2_2++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}

					break;// 跳出case
				}

					  /* 道具4：分叉子弹（一段时间） */
				case 4: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs3_1.push_back(new Bullet3_1(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（中））
						bs3_2.push_back(new Bullet3_2(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（左））
						bs3_3.push_back(new Bullet3_3(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（右））

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit3_1 = bs3_1.begin();
					while (bsit3_1 != bs3_1.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_1)->Show())
							bsit3_1 = bs3_1.erase(bsit3_1);
						else
							bsit3_1++;
					}
					auto bsit3_2 = bs3_2.begin();
					while (bsit3_2 != bs3_2.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_2)->Show())
							bsit3_2 = bs3_2.erase(bsit3_2);
						else
							bsit3_2++;
					}
					auto bsit3_3 = bs3_3.begin();
					while (bsit3_3 != bs3_3.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_3)->Show())
							bsit3_3 = bs3_3.erase(bsit3_3);
						else
							bsit3_3++;
					}

					/* 加载敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}


							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								delete (*bit3_1);
								bs3_1.erase(bit3_1);

								break;
							}
							bit3_1++;
						}
						auto bit3_2 = bs3_2.begin();
						while (bit3_2 != bs3_2.end()) {
							if (RectDuangRect((*bit3_2)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								delete (*bit3_2);
								bs3_2.erase(bit3_2);

								break;
							}
							bit3_2++;
						}
						auto bit3_3 = bs3_3.begin();
						while (bit3_3 != bs3_3.end()) {
							if (RectDuangRect((*bit3_3)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								delete (*bit3_3);
								bs3_3.erase(bit3_3);

								break;
							}
							bit3_3++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit3_1);
								bs3_1.erase(bit3_1);

								break;
							}
							bit3_1++;
						}
						auto bit3_2 = bs3_2.begin();
						while (bit3_2 != bs3_2.end()) {
							if (RectDuangRect((*bit3_2)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit3_2);
								bs3_2.erase(bit3_2);

								break;
							}
							bit3_2++;
						}
						auto bit3_3 = bs3_3.begin();
						while (bit3_3 != bs3_3.end()) {
							if (RectDuangRect((*bit3_3)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit3_3);
								bs3_3.erase(bit3_3);

								break;
							}
							bit3_3++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
							}

							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*mini_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								delete (*bit3_1);
								bs3_1.erase(bit3_1);

								break;
							}
							bit3_1++;
						}
						auto bit3_2 = bs3_2.begin();
						while (bit3_2 != bs3_2.end()) {
							if (RectDuangRect((*bit3_2)->GetRect(), (*mini_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								delete (*bit3_2);
								bs3_2.erase(bit3_2);

								break;
							}
							bit3_2++;
						}
						auto bit3_3 = bs3_3.begin();
						while (bit3_3 != bs3_3.end()) {
							if (RectDuangRect((*bit3_3)->GetRect(), (*mini_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								delete (*bit3_3);
								bs3_3.erase(bit3_3);

								break;
							}
							bit3_3++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}

					break;// 跳出case
				}

					  /* 道具5：穿甲子弹（一段时间） */
				case 5: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs4.push_back(new Bullet4(bullet4img, hp.GetRect()));// 我方子弹（穿甲弹）

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit4 = bs4.begin();
					while (bsit4 != bs4.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit4)->Show())
							bsit4 = bs4.erase(bsit4);
						else
							bsit4++;
					}

					/* 加载敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}

							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								break;
							}
							bit4++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								break;
							}
							bit4++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
							}

							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*mini_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								break;
							}
							bit4++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}

					break;// 跳出case
				}
				}

				/* 每杀一定数量敌人送一个道具 */
				if ((condition == 0) && (kill_temp >= KILL_FOR_GIFT)) {
					/* 随机发放道具（未完成） */
					gift_index = rand() % 5;
					AddGift(gift, giftimg[gift_index]);

					kill_temp = 0;
					bullets_total = 0;
				}
				/* 加载道具 */
				auto gift_it = gift.begin();
				while (gift_it != gift.end()) {
					// 成功拾取道具
					if (RectDuangRect((*gift_it)->GetRect(), hp.GetRect())) {
						condition = gift_index + 1;

						delete (*gift_it);// 删除类指针
						gift.erase(gift_it);// 踢出容器
						gift_it = gift.begin();
						break;
					}
					// 未能拾取道具（已经飞出屏幕）
					if (!(*gift_it)->Show()) {
						delete (*gift_it);// 删除类指针
						gift.erase(gift_it);// 踢出容器
						gift_it = gift.begin();
					}
					else
						gift_it++;
				}

				/* 右上角实时显示击杀数和得分 */
				score = kill[0] * 3 + kill[1] * 5 + kill[2] * 1 + kill[3] * 7 + kill[4] * 31;
				PrintScore(kill, score);

				/* 检测是否过关 */
				if (score >= SCORE_3) {
					flag = true;
					is_play = false;
				}

				EndBatchDraw();// BeginBatchDraw和EndBatchDraw用于消除频闪				
			}

			stopBgmMusic();
			Over(kill, score, flag);// 结算界面
			break;
		}

		// 闯关模式——第4关
		// 普通敌机、中型敌机、小型敌机、大型敌机
		// score 1300
		case 204: {
			/* 声明对象 */
			BG bg = BG(bgimg4);// 背景
			Hero hp = Hero(heroimg2);// 玩家飞机
			vector<Enemy*> ep;// 敌机向量（普通）
			vector<midEnemy*> mid_ep;// 敌机向量（中型）
			vector<miniEnemy*> mini_ep;// 敌机向量（小型）
			vector<giantEnemy*> giant_ep;// 敌机向量（大型）
			vector<Bullet*> bs;// 我方子弹向量（普通）
			vector<Bullet2_1*> bs2_1;// 我方子弹向量（双发子弹（左））
			vector<Bullet2_2*> bs2_2;// 我方子弹向量（双发子弹（右））
			vector<Bullet3_1*> bs3_1;// 我方子弹向量（分叉子弹（中））
			vector<Bullet3_2*> bs3_2;// 我方子弹向量（分叉子弹（左））
			vector<Bullet3_3*> bs3_3;// 我方子弹向量（分叉子弹（右））
			vector<Bullet4*> bs4;// 我方子弹向量（穿甲弹）
			vector<EBullet*> ebs;// 敌方子弹向量（普通）
			vector<EBullet*> mid_ebs;// 敌方子弹向量（中型）
			vector<EBullet*> giant_ebs;// 敌方子弹向量（大型）
			vector<Gift*> gift;// 道具向量

			/* 定义基本变量 */
			int bsing = 0;// 控制我方子弹发射频率（普通）
			int ebsing = 0;// 控制敌方子弹发射频率（普通）
			int mid_ebsing = 0;// 控制敌方子弹发射频率（中型）
			int giant_ebsing = 0;// 控制敌方子弹发射频率（大型）
			int density = DENSITY;// 控制敌机密度（普通）
			int mid_density = MID_DENSITY;// 控制敌机密度（中型）
			int mini_density = MINI_DENSITY;// 控制敌机密度（小型）
			int giant_density = GIANT_DENSITY;// 控制敌机密度（大型）

			/* 定义计数器 */
			int kill[5] = { 0, 0, 0, 0, 0 };// 记录整局击杀数量:{普通，中型，小型，大型，BOSS}
			int score = 0;// 记录得分：{普通：3，中型：5，小型：1，大型：7，BOSS：31}
			int kill_temp = 0;// 记录当前杀敌数量（达到一定值后归零，用于确定发送道具时机）
			int bullets_total = 0;// 记录有道具期间发射子弹总数，用于切换道具状态
			int condition = 0;// 用于切换道具状态，默认为0
			int gift_index = 0;// 用于记录道具种类
			bool flag = false;// 判断是否过关

			/* 记录时间 */
			DWORD startTime = timeGetTime();// 获取开始时间
			int mini_time = 4000;// 小型敌机刷新时间

			playBgmMusic();

			/* 添加开局敌机 */
			for (int i = 0; i < density; i++) {
				AddEnemy(ep, enemyimg, eboom);
			}

			/* 进入游戏中 */
			while (is_play) {
				/* 加载背景、玩家飞机 */
				BeginBatchDraw();// BeginBatchDraw和EndBatchDraw用于消除频闪，详情：https://docs.easyx.cn/zh-cn/other-func
				bg.Show();
				Sleep(4);
				flushmessage();
				Sleep(1);
				hp.Control();
				hp.Show();

				/* 按空格暂停 */
				if (GetAsyncKeyState(VK_SPACE) & 0x0001)
					while (!(GetAsyncKeyState(VK_SPACE) & 0x0001));

				/* 添加敌方子弹 */
				ebsing++;
				if (ebsing == 101 - ebs_frequency) {
					ebsing = 0;
					for (auto& i : ep)
						ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// 敌方子弹（普通）
				}
				mid_ebsing++;
				if (mid_ebsing == 101 - mid_ebs_frequency) {
					mid_ebsing = 0;
					for (auto& i : mid_ep)
						mid_ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// 敌方子弹（中型）
				}
				giant_ebsing++;
				if (giant_ebsing == 101 - giant_ebs_frequency) {
					giant_ebsing = 0;
					for (auto& i : giant_ep)
						giant_ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// 敌方子弹（大型）
				}

				/* 添加敌机 */
				for (int i = 0; i < density - ep.size(); i++) {
					AddEnemy(ep, enemyimg, eboom);
				}
				for (int i = 0; i < mid_density - mid_ep.size(); i++) {
					AddEnemy(mid_ep, midEnemyimg, eboom);
				}
				DWORD currentTime = timeGetTime(); // 获取当前时间
				DWORD elapsedTime = currentTime - startTime; // 计算经过的时间
				if (static_cast<int>(elapsedTime) >= mini_time) {
					int x = rand() % 3;
					for (int i = 0; i < mini_density; i++) {// 补充敌机
						AddEnemy(mini_ep, miniEnemyimg, eboom, x);
					}
					startTime = currentTime;
				}
				for (int i = 0; i < giant_density - giant_ep.size(); i++) {
					AddEnemy(giant_ep, giantEnemyimg, eboom);
				}

				/* 加载敌方子弹 */
				auto ebsit = ebs.begin();
				while (ebsit != ebs.end()) {
					// 我方飞机被击中
					if (RectDuangRect((*ebsit)->GetRect(), hp.GetRect())) {
						/* 结果 */
						is_play = hp.hurt();

						ebsit = ebs.erase(ebsit);
					}
					// 如果子弹飞出屏幕则去除
					else if (!(*ebsit)->Show())
						ebsit = ebs.erase(ebsit);
					else
						ebsit++;
				}
				auto mid_ebsit = mid_ebs.begin();
				while (mid_ebsit != mid_ebs.end()) {
					// 我方飞机被击中
					if (RectDuangRect((*mid_ebsit)->GetRect(), hp.GetRect())) {
						/* 结果 */
						is_play = hp.hurt();

						mid_ebsit = mid_ebs.erase(mid_ebsit);
					}
					// 如果子弹飞出屏幕则去除
					else if (!(*mid_ebsit)->Show())
						mid_ebsit = mid_ebs.erase(mid_ebsit);
					else
						mid_ebsit++;
				}
				auto giant_ebsit = giant_ebs.begin();
				while (giant_ebsit != giant_ebs.end()) {
					// 我方飞机被击中
					if (RectDuangRect((*giant_ebsit)->GetRect(), hp.GetRect())) {
						/* 结果 */
						is_play = hp.hurt();

						giant_ebsit = giant_ebs.erase(giant_ebsit);
					}
					// 如果子弹飞出屏幕则去除
					else if (!(*giant_ebsit)->Show())
						giant_ebsit = giant_ebs.erase(giant_ebsit);
					else
						giant_ebsit++;
				}

				/* 拾取道具进入对应状态 */
				switch (condition) {
					/* 正常状态 */
				case 0: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs.push_back(new Bullet(bulletimg, hp.GetRect()));// 我方子弹（普通）
					}

					/* 加载我方子弹 */
					auto bsit = bs.begin();
					while (bsit != bs.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit)->Show())
							bsit = bs.erase(bsit);
						else
							bsit++;
					}

					/* 加载敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
								kill_temp++;
							}

							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*it)->GetRect())) {
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
									kill_temp++;
								}

								delete (*bit);
								bs.erase(bit);

								break;
							}
							bit++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
								kill_temp++;
							}

							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*mid_it)->GetRect())) {
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit);
								bs.erase(bit);

								break;
							}
							bit++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
								kill_temp++;
							}

							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*mini_it)->GetRect())) {
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
									kill_temp++;
								}

								delete (*bit);
								bs.erase(bit);

								break;
							}
							bit++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*giant_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*giant_it)->dying()) {
								(*giant_it)->Dies();
								kill[3]++;
								kill_temp++;
							}

							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*giant_it)->GetRect())) {
								/* 结果 */
								if ((*giant_it)->hurt()) {
									kill[3]++;
									kill_temp++;
								}

								delete (*bit);
								bs.erase(bit);

								break;
							}
							bit++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}

					break;// 跳出case
				}

					  /* 道具1：加生命值（一次性道具） */
				case 1: {
					hp.heal();

					condition = 0;// 恢复正常状态

					break;// 跳出case
				}

					  /* 道具2：清空敌机和敌方子弹（一次性道具） */
				case 2: {
					/* 清空敌方子弹 */
					auto ebsit = ebs.begin();
					while (ebsit != ebs.end()) {
						ebsit = ebs.erase(ebsit);
					}
					auto mid_ebsit = mid_ebs.begin();
					while (mid_ebsit != mid_ebs.end()) {
						mid_ebsit = mid_ebs.erase(mid_ebsit);
					}
					auto giant_ebsit = giant_ebs.begin();
					while (giant_ebsit != giant_ebs.end()) {
						giant_ebsit = giant_ebs.erase(giant_ebsit);
					}

					/* 清空敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						if (!(*it)->dying()) {
							(*it)->Dies();
							kill[0]++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						if (!(*mid_it)->dying()) {
							(*mid_it)->Dies();
							kill[1]++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						if (!(*mini_it)->dying()) {
							(*mini_it)->Dies();
							kill[2]++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						if (!(*giant_it)->dying()) {
							(*giant_it)->Dies();
							kill[3]++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}

					condition = 0;// 恢复正常状态

					break;// 跳出case
				}

					  /* 道具3：双发子弹（一段时间） */
				case 3: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs2_1.push_back(new Bullet2_1(bulletimg, hp.GetRect()));// 我方子弹（双发子弹（左））
						bs2_2.push_back(new Bullet2_2(bulletimg, hp.GetRect()));// 我方子弹（双发子弹（右））

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit2_1 = bs2_1.begin();
					while (bsit2_1 != bs2_1.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit2_1)->Show())
							bsit2_1 = bs2_1.erase(bsit2_1);
						else
							bsit2_1++;
					}
					auto bsit2_2 = bs2_2.begin();
					while (bsit2_2 != bs2_2.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit2_2)->Show())
							bsit2_2 = bs2_2.erase(bsit2_2);
						else
							bsit2_2++;
					}

					/* 加载敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}

							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								delete (*bit2_1);
								bs2_1.erase(bit2_1);

								break;
							}
							bit2_1++;
						}
						auto bit2_2 = bs2_2.begin();
						while (bit2_2 != bs2_2.end()) {
							if (RectDuangRect((*bit2_2)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}


								delete (*bit2_2);
								bs2_2.erase(bit2_2);

								break;
							}
							bit2_2++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit2_1);
								bs2_1.erase(bit2_1);

								break;
							}
							bit2_1++;
						}
						auto bit2_2 = bs2_2.begin();
						while (bit2_2 != bs2_2.end()) {
							if (RectDuangRect((*bit2_2)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit2_2);
								bs2_2.erase(bit2_2);

								break;
							}
							bit2_2++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
							}

							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*mini_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								delete (*bit2_1);
								bs2_1.erase(bit2_1);

								break;
							}
							bit2_1++;
						}
						auto bit2_2 = bs2_2.begin();
						while (bit2_2 != bs2_2.end()) {
							if (RectDuangRect((*bit2_2)->GetRect(), (*mini_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								delete (*bit2_2);
								bs2_2.erase(bit2_2);

								break;
							}
							bit2_2++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*giant_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*giant_it)->dying()) {
								(*giant_it)->Dies();
								kill[3]++;
							}

							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*giant_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*giant_it)->hurt()) {
									kill[3]++;
									kill_temp++;
								}

								delete (*bit2_1);
								bs2_1.erase(bit2_1);

								break;
							}
							bit2_1++;
						}
						auto bit2_2 = bs2_2.begin();
						while (bit2_2 != bs2_2.end()) {
							if (RectDuangRect((*bit2_2)->GetRect(), (*giant_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*giant_it)->hurt()) {
									kill[3]++;
									kill_temp++;
								}

								delete (*bit2_2);
								bs2_2.erase(bit2_2);

								break;
							}
							bit2_2++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}

					break;// 跳出case
				}

					  /* 道具4：分叉子弹（一段时间） */
				case 4: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs3_1.push_back(new Bullet3_1(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（中））
						bs3_2.push_back(new Bullet3_2(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（左））
						bs3_3.push_back(new Bullet3_3(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（右））

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit3_1 = bs3_1.begin();
					while (bsit3_1 != bs3_1.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_1)->Show())
							bsit3_1 = bs3_1.erase(bsit3_1);
						else
							bsit3_1++;
					}
					auto bsit3_2 = bs3_2.begin();
					while (bsit3_2 != bs3_2.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_2)->Show())
							bsit3_2 = bs3_2.erase(bsit3_2);
						else
							bsit3_2++;
					}
					auto bsit3_3 = bs3_3.begin();
					while (bsit3_3 != bs3_3.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_3)->Show())
							bsit3_3 = bs3_3.erase(bsit3_3);
						else
							bsit3_3++;
					}

					/* 加载敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}


							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								delete (*bit3_1);
								bs3_1.erase(bit3_1);

								break;
							}
							bit3_1++;
						}
						auto bit3_2 = bs3_2.begin();
						while (bit3_2 != bs3_2.end()) {
							if (RectDuangRect((*bit3_2)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								delete (*bit3_2);
								bs3_2.erase(bit3_2);

								break;
							}
							bit3_2++;
						}
						auto bit3_3 = bs3_3.begin();
						while (bit3_3 != bs3_3.end()) {
							if (RectDuangRect((*bit3_3)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								delete (*bit3_3);
								bs3_3.erase(bit3_3);

								break;
							}
							bit3_3++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit3_1);
								bs3_1.erase(bit3_1);

								break;
							}
							bit3_1++;
						}
						auto bit3_2 = bs3_2.begin();
						while (bit3_2 != bs3_2.end()) {
							if (RectDuangRect((*bit3_2)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit3_2);
								bs3_2.erase(bit3_2);

								break;
							}
							bit3_2++;
						}
						auto bit3_3 = bs3_3.begin();
						while (bit3_3 != bs3_3.end()) {
							if (RectDuangRect((*bit3_3)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit3_3);
								bs3_3.erase(bit3_3);

								break;
							}
							bit3_3++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
							}

							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*mini_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								delete (*bit3_1);
								bs3_1.erase(bit3_1);

								break;
							}
							bit3_1++;
						}
						auto bit3_2 = bs3_2.begin();
						while (bit3_2 != bs3_2.end()) {
							if (RectDuangRect((*bit3_2)->GetRect(), (*mini_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								delete (*bit3_2);
								bs3_2.erase(bit3_2);

								break;
							}
							bit3_2++;
						}
						auto bit3_3 = bs3_3.begin();
						while (bit3_3 != bs3_3.end()) {
							if (RectDuangRect((*bit3_3)->GetRect(), (*mini_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								delete (*bit3_3);
								bs3_3.erase(bit3_3);

								break;
							}
							bit3_3++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*giant_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*giant_it)->dying()) {
								(*giant_it)->Dies();
								kill[3]++;
							}

							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*giant_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*giant_it)->hurt()) {
									kill[3]++;
									kill_temp++;
								}

								delete (*bit3_1);
								bs3_1.erase(bit3_1);

								break;
							}
							bit3_1++;
						}
						auto bit3_2 = bs3_2.begin();
						while (bit3_2 != bs3_2.end()) {
							if (RectDuangRect((*bit3_2)->GetRect(), (*giant_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*giant_it)->hurt()) {
									kill[3]++;
									kill_temp++;
								}

								delete (*bit3_2);
								bs3_2.erase(bit3_2);

								break;
							}
							bit3_2++;
						}
						auto bit3_3 = bs3_3.begin();
						while (bit3_3 != bs3_3.end()) {
							if (RectDuangRect((*bit3_3)->GetRect(), (*giant_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*giant_it)->hurt()) {
									kill[3]++;
									kill_temp++;
								}

								delete (*bit3_3);
								bs3_3.erase(bit3_3);

								break;
							}
							bit3_3++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}

					break;// 跳出case
				}

					  /* 道具5：穿甲子弹（一段时间） */
				case 5: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs4.push_back(new Bullet4(bullet4img, hp.GetRect()));// 我方子弹（穿甲弹）

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit4 = bs4.begin();
					while (bsit4 != bs4.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit4)->Show())
							bsit4 = bs4.erase(bsit4);
						else
							bsit4++;
					}

					/* 加载敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}

							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								break;
							}
							bit4++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								break;
							}
							bit4++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
							}

							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*mini_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								break;
							}
							bit4++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*giant_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*giant_it)->dying()) {
								(*giant_it)->Dies();
								kill[3]++;
							}

							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*giant_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*giant_it)->hurt()) {
									kill[3]++;
									kill_temp++;
								}

								break;
							}
							bit4++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}

					break;// 跳出case
				}
				}

				/* 每杀一定数量敌人送一个道具 */
				if ((condition == 0) && (kill_temp >= KILL_FOR_GIFT)) {
					/* 随机发放道具（未完成） */
					gift_index = rand() % 5;
					AddGift(gift, giftimg[gift_index]);

					kill_temp = 0;
					bullets_total = 0;
				}
				/* 加载道具 */
				auto gift_it = gift.begin();
				while (gift_it != gift.end()) {
					// 成功拾取道具
					if (RectDuangRect((*gift_it)->GetRect(), hp.GetRect())) {
						condition = gift_index + 1;

						delete (*gift_it);// 删除类指针
						gift.erase(gift_it);// 踢出容器
						gift_it = gift.begin();
						break;
					}
					// 未能拾取道具（已经飞出屏幕）
					if (!(*gift_it)->Show()) {
						delete (*gift_it);// 删除类指针
						gift.erase(gift_it);// 踢出容器
						gift_it = gift.begin();
					}
					else
						gift_it++;
				}

				/* 右上角实时显示击杀数和得分 */
				score = kill[0] * 3 + kill[1] * 5 + kill[2] * 1 + kill[3] * 7 + kill[4] * 31;
				PrintScore(kill, score);

				/* 检测是否过关 */
				if (score >= SCORE_4) {
					flag = true;
					is_play = false;
				}

				EndBatchDraw();// BeginBatchDraw和EndBatchDraw用于消除频闪				
			}

			stopBgmMusic();
			Over(kill, score, flag);// 结算界面
			break;
		}

		// 闯关模式——第5关
		// 普通敌机、中型敌机、小型敌机、大型敌机、BOSS
		// score 1300
		case 205: {
			/* 声明对象 */
			BG bg = BG(bgimg5);// 背景
			Hero hp = Hero(heroimg2);// 玩家飞机
			vector<Enemy*> ep;// 敌机向量（普通）
			vector<midEnemy*> mid_ep;// 敌机向量（中型）
			vector<miniEnemy*> mini_ep;// 敌机向量（小型）
			vector<giantEnemy*> giant_ep;// 敌机向量（大型）
			vector<bossEnemy*> boss_ep;// 敌机向量（BOSS）
			vector<Bullet*> bs;// 我方子弹向量（普通）
			vector<Bullet2_1*> bs2_1;// 我方子弹向量（双发子弹（左））
			vector<Bullet2_2*> bs2_2;// 我方子弹向量（双发子弹（右））
			vector<Bullet3_1*> bs3_1;// 我方子弹向量（分叉子弹（中））
			vector<Bullet3_2*> bs3_2;// 我方子弹向量（分叉子弹（左））
			vector<Bullet3_3*> bs3_3;// 我方子弹向量（分叉子弹（右））
			vector<Bullet4*> bs4;// 我方子弹向量（穿甲弹）
			vector<EBullet*> ebs;// 敌方子弹向量（普通）
			vector<EBullet*> mid_ebs;// 敌方子弹向量（中型）
			vector<EBullet*> giant_ebs;// 敌方子弹向量（大型）
			vector<BossSkill_1*> boss_skill_1;// BOSS子弹向量（skill_1）
			vector<BossSkill_2*> boss_skill_2;// BOSS子弹向量（skill_2）
			vector<BossSkill_3*> boss_skill_3;// BOSS子弹向量（skill_3）
			vector<Gift*> gift;// 道具向量

			/* 定义基本变量 */
			int bsing = 0;// 控制我方子弹发射频率（普通）
			int ebsing = 0;// 控制敌方子弹发射频率（普通）
			int mid_ebsing = 0;// 控制敌方子弹发射频率（中型）
			int giant_ebsing = 0;// 控制敌方子弹发射频率（大型）
			int boss_ebsing = 0;// 控制敌方子弹发射频率（BOSS）
			int density = DENSITY;// 控制敌机密度（普通）
			int mid_density = MID_DENSITY;// 控制敌机密度（中型）
			int mini_density = MINI_DENSITY;// 控制敌机密度（小型）
			int giant_density = GIANT_DENSITY;// 控制敌机密度（大型）
			int boss_density = BOSS_DENSITY;// 控制敌机密度（BOSS）

			/* 定义计数器 */
			int kill[5] = { 0, 0, 0, 0, 0 };// 记录整局击杀数量:{普通，中型，小型，大型，BOSS}
			int score = 0;// 记录得分：{普通：3，中型：5，小型：1，大型：7，BOSS：31}
			int kill_temp = 0;// 记录当前杀敌数量（达到一定值后归零，用于确定发送道具时机）
			int bullets_total = 0;// 记录有道具期间发射子弹总数，用于切换道具状态
			int condition = 0;// 用于切换道具状态，默认为0
			int gift_index = 0;// 用于记录道具种类
			bool flag = false;// 判断是否过关

			/* 记录时间 */
			DWORD startTime = timeGetTime();// 获取开始时间
			int mini_time = 4000;// 小型敌机刷新时间

			playBgmMusic();

			/* 添加开局敌机 */
			for (int i = 0; i < density; i++) {
				AddEnemy(ep, enemyimg, eboom);
			}

			/* 进入游戏中 */
			while (is_play) {
				/* 加载背景、玩家飞机 */
				BeginBatchDraw();// BeginBatchDraw和EndBatchDraw用于消除频闪，详情：https://docs.easyx.cn/zh-cn/other-func
				bg.Show();
				Sleep(4);
				flushmessage();
				Sleep(1);
				hp.Control();
				hp.Show();

				/* 按空格暂停 */
				if (GetAsyncKeyState(VK_SPACE) & 0x0001)
					while (!(GetAsyncKeyState(VK_SPACE) & 0x0001));

				/* 添加敌方子弹 */
				ebsing++;
				if (ebsing == 101 - ebs_frequency) {
					ebsing = 0;
					for (auto& i : ep)
						ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// 敌方子弹（普通）
				}
				mid_ebsing++;
				if (mid_ebsing == 101 - mid_ebs_frequency) {
					mid_ebsing = 0;
					for (auto& i : mid_ep)
						mid_ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// 敌方子弹（中型）
				}
				giant_ebsing++;
				if (giant_ebsing == 101 - giant_ebs_frequency) {
					giant_ebsing = 0;
					for (auto& i : giant_ep)
						giant_ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// 敌方子弹（大型）
				}
				boss_ebsing++;
				if (boss_ebsing == 101 - boss_ebs_frequency) {
					boss_ebsing = 0;
					for (auto& i : boss_ep) {
						// boss_skill_1发射概率：50%
						if (rand() % 2 != 0)
							boss_skill_1.push_back(new BossSkill_1(bossSkill_1img, i->GetRect()));
						// boss_skill_2发射概率：100%
						boss_skill_2.push_back(new BossSkill_2(bossSkill_2img, i->GetRect()));
						// boss_skill_3发射概率：25%
						if (rand() % 4 == 0)
							boss_skill_3.push_back(new BossSkill_3(bossSkill_3img, i->GetRect()));
					}
				}

				/* 添加敌机 */
				if (score < SCORE_4) {
					for (int i = 0; i < density - ep.size(); i++) {
						AddEnemy(ep, enemyimg, eboom);
					}
					for (int i = 0; i < mid_density - mid_ep.size(); i++) {
						AddEnemy(mid_ep, midEnemyimg, eboom);
					}
					DWORD currentTime = timeGetTime(); // 获取当前时间
					DWORD elapsedTime = currentTime - startTime; // 计算经过的时间
					if (static_cast<int>(elapsedTime) >= mini_time) {
						int x = rand() % 3;
						for (int i = 0; i < mini_density; i++) {// 补充敌机
							AddEnemy(mini_ep, miniEnemyimg, eboom, x);
						}
						startTime = currentTime;
					}
					for (int i = 0; i < giant_density - giant_ep.size(); i++) {
						AddEnemy(giant_ep, giantEnemyimg, eboom);
					}
				}
				else {
					condition = 0;
					for (int i = 0; i < boss_density - boss_ep.size(); i++) {
						AddEnemy(boss_ep, bossEnemyimg, eboom);
					}
				}

				/* 加载敌方子弹 */
				auto ebsit = ebs.begin();
				while (ebsit != ebs.end()) {
					// 我方飞机被击中
					if (RectDuangRect((*ebsit)->GetRect(), hp.GetRect())) {
						/* 结果 */
						is_play = hp.hurt();

						ebsit = ebs.erase(ebsit);
					}
					// 如果子弹飞出屏幕则去除
					else if (!(*ebsit)->Show())
						ebsit = ebs.erase(ebsit);
					else
						ebsit++;
				}
				auto mid_ebsit = mid_ebs.begin();
				while (mid_ebsit != mid_ebs.end()) {
					// 我方飞机被击中
					if (RectDuangRect((*mid_ebsit)->GetRect(), hp.GetRect())) {
						/* 结果 */
						is_play = hp.hurt();

						mid_ebsit = mid_ebs.erase(mid_ebsit);
					}
					// 如果子弹飞出屏幕则去除
					else if (!(*mid_ebsit)->Show())
						mid_ebsit = mid_ebs.erase(mid_ebsit);
					else
						mid_ebsit++;
				}
				auto giant_ebsit = giant_ebs.begin();
				while (giant_ebsit != giant_ebs.end()) {
					// 我方飞机被击中
					if (RectDuangRect((*giant_ebsit)->GetRect(), hp.GetRect())) {
						/* 结果 */
						is_play = hp.hurt();

						giant_ebsit = giant_ebs.erase(giant_ebsit);
					}
					// 如果子弹飞出屏幕则去除
					else if (!(*giant_ebsit)->Show())
						giant_ebsit = giant_ebs.erase(giant_ebsit);
					else
						giant_ebsit++;
				}
				auto boss_skill_1it = boss_skill_1.begin();
				while (boss_skill_1it != boss_skill_1.end()) {
					// 我方飞机被击中
					if (RectDuangRect((*boss_skill_1it)->GetRect(), hp.GetRect())) {
						/* 结果 */
						is_play = hp.hurt(2);

						boss_skill_1it = boss_skill_1.erase(boss_skill_1it);
					}
					else if (!(*boss_skill_1it)->Show())
						boss_skill_1it = boss_skill_1.erase(boss_skill_1it);
					else
						boss_skill_1it++;
				}
				auto boss_skill_2it = boss_skill_2.begin();
				while (boss_skill_2it != boss_skill_2.end()) {
					// 我方飞机被击中
					if (RectDuangRect((*boss_skill_2it)->GetRect(), hp.GetRect())) {
						/* 结果 */
						is_play = hp.hurt(1);

						boss_skill_2it = boss_skill_2.erase(boss_skill_2it);
					}
					else if (!(*boss_skill_2it)->Show())
						boss_skill_2it = boss_skill_2.erase(boss_skill_2it);
					else
						boss_skill_2it++;
				}
				auto boss_skill_3it = boss_skill_3.begin();
				while (boss_skill_3it != boss_skill_3.end()) {
					// 我方飞机被击中
					if (RectDuangRect((*boss_skill_3it)->GetRect(), hp.GetRect())) {
						/* 结果 */
						is_play = hp.hurt(HP);

						boss_skill_3it = boss_skill_3.erase(boss_skill_3it);
					}
					else if (!(*boss_skill_3it)->Show())
						boss_skill_3it = boss_skill_3.erase(boss_skill_3it);
					else
						boss_skill_3it++;
				}

				/* 拾取道具进入对应状态 */
				switch (condition) {
					/* 正常状态 */
				case 0: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs.push_back(new Bullet(bulletimg, hp.GetRect()));// 我方子弹（普通）
					}

					/* 加载我方子弹 */
					auto bsit = bs.begin();
					while (bsit != bs.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit)->Show())
							bsit = bs.erase(bsit);
						else
							bsit++;
					}

					/* 加载敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
								kill_temp++;
							}

							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*it)->GetRect())) {
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
									kill_temp++;
								}

								delete (*bit);
								bs.erase(bit);

								break;
							}
							bit++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
								kill_temp++;
							}

							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*mid_it)->GetRect())) {
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit);
								bs.erase(bit);

								break;
							}
							bit++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
								kill_temp++;
							}

							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*mini_it)->GetRect())) {
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
									kill_temp++;
								}

								delete (*bit);
								bs.erase(bit);

								break;
							}
							bit++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*giant_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*giant_it)->dying()) {
								(*giant_it)->Dies();
								kill[3]++;
								kill_temp++;
							}

							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*giant_it)->GetRect())) {
								/* 结果 */
								if ((*giant_it)->hurt()) {
									kill[3]++;
									kill_temp++;
								}

								delete (*bit);
								bs.erase(bit);

								break;
							}
							bit++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}
					auto boss_it = boss_ep.begin();
					while (boss_it != boss_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*boss_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt(HP);

							break;
						}

						/* 如果我方子弹击中敌机 */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*boss_it)->GetRect())) {
								/* 结果 */
								if ((*boss_it)->hurt()) {
									kill[4]++;
									kill_temp++;
									flag = true;
								}

								delete (*bit);
								bs.erase(bit);

								break;
							}
							bit++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*boss_it)->Show()) {
							delete (*boss_it);// 删除类指针
							boss_ep.erase(boss_it);// 踢出容器
							boss_it = boss_ep.begin();
						}
						else
							boss_it++;
					}

					break;// 跳出case
				}

					  /* 道具1：加生命值（一次性道具） */
				case 1: {
					hp.heal();

					condition = 0;// 恢复正常状态

					break;// 跳出case
				}

					  /* 道具2：清空敌机和敌方子弹（一次性道具） */
				case 2: {
					/* 清空敌方子弹 */
					auto ebsit = ebs.begin();
					while (ebsit != ebs.end()) {
						ebsit = ebs.erase(ebsit);
					}
					auto mid_ebsit = mid_ebs.begin();
					while (mid_ebsit != mid_ebs.end()) {
						mid_ebsit = mid_ebs.erase(mid_ebsit);
					}
					auto giant_ebsit = giant_ebs.begin();
					while (giant_ebsit != giant_ebs.end()) {
						giant_ebsit = giant_ebs.erase(giant_ebsit);
					}
					auto boss_skill_1it = boss_skill_1.begin();
					while (boss_skill_1it != boss_skill_1.end()) {
						boss_skill_1it = boss_skill_1.erase(boss_skill_1it);
					}
					auto boss_skill_2it = boss_skill_2.begin();
					while (boss_skill_2it != boss_skill_2.end()) {
						boss_skill_2it = boss_skill_2.erase(boss_skill_2it);
					}
					auto boss_skill_3it = boss_skill_3.begin();
					while (boss_skill_3it != boss_skill_3.end()) {
						boss_skill_3it = boss_skill_3.erase(boss_skill_3it);
					}

					/* 清空敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						if (!(*it)->dying()) {
							(*it)->Dies();
							kill[0]++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						if (!(*mid_it)->dying()) {
							(*mid_it)->Dies();
							kill[1]++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						if (!(*mini_it)->dying()) {
							(*mini_it)->Dies();
							kill[2]++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						if (!(*giant_it)->dying()) {
							(*giant_it)->Dies();
							kill[3]++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}
					auto boss_it = boss_ep.begin();
					while (boss_it != boss_ep.end()) {
						if (!(*boss_it)->dying()) {
							(*boss_it)->Dies();
							kill[4]++;
							flag = true;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*boss_it)->Show()) {
							delete (*boss_it);// 删除类指针
							boss_ep.erase(boss_it);// 踢出容器
							boss_it = boss_ep.begin();
						}
						else
							boss_it++;
					}

					condition = 0;// 恢复正常状态

					break;// 跳出case
				}

					  /* 道具3：双发子弹（一段时间） */
				case 3: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs2_1.push_back(new Bullet2_1(bulletimg, hp.GetRect()));// 我方子弹（双发子弹（左））
						bs2_2.push_back(new Bullet2_2(bulletimg, hp.GetRect()));// 我方子弹（双发子弹（右））

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit2_1 = bs2_1.begin();
					while (bsit2_1 != bs2_1.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit2_1)->Show())
							bsit2_1 = bs2_1.erase(bsit2_1);
						else
							bsit2_1++;
					}
					auto bsit2_2 = bs2_2.begin();
					while (bsit2_2 != bs2_2.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit2_2)->Show())
							bsit2_2 = bs2_2.erase(bsit2_2);
						else
							bsit2_2++;
					}

					/* 加载敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}

							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								delete (*bit2_1);
								bs2_1.erase(bit2_1);

								break;
							}
							bit2_1++;
						}
						auto bit2_2 = bs2_2.begin();
						while (bit2_2 != bs2_2.end()) {
							if (RectDuangRect((*bit2_2)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}


								delete (*bit2_2);
								bs2_2.erase(bit2_2);

								break;
							}
							bit2_2++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit2_1);
								bs2_1.erase(bit2_1);

								break;
							}
							bit2_1++;
						}
						auto bit2_2 = bs2_2.begin();
						while (bit2_2 != bs2_2.end()) {
							if (RectDuangRect((*bit2_2)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit2_2);
								bs2_2.erase(bit2_2);

								break;
							}
							bit2_2++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
							}

							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*mini_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								delete (*bit2_1);
								bs2_1.erase(bit2_1);

								break;
							}
							bit2_1++;
						}
						auto bit2_2 = bs2_2.begin();
						while (bit2_2 != bs2_2.end()) {
							if (RectDuangRect((*bit2_2)->GetRect(), (*mini_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								delete (*bit2_2);
								bs2_2.erase(bit2_2);

								break;
							}
							bit2_2++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*giant_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*giant_it)->dying()) {
								(*giant_it)->Dies();
								kill[3]++;
							}

							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*giant_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*giant_it)->hurt()) {
									kill[3]++;
									kill_temp++;
								}

								delete (*bit2_1);
								bs2_1.erase(bit2_1);

								break;
							}
							bit2_1++;
						}
						auto bit2_2 = bs2_2.begin();
						while (bit2_2 != bs2_2.end()) {
							if (RectDuangRect((*bit2_2)->GetRect(), (*giant_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*giant_it)->hurt()) {
									kill[3]++;
									kill_temp++;
								}

								delete (*bit2_2);
								bs2_2.erase(bit2_2);

								break;
							}
							bit2_2++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}
					auto boss_it = boss_ep.begin();
					while (boss_it != boss_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*boss_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt(HP);

							break;
						}

						/* 如果我方子弹击中敌机 */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*boss_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*boss_it)->hurt()) {
									kill[4]++;
									kill_temp++;
									flag = true;
								}

								delete (*bit2_1);
								bs2_1.erase(bit2_1);

								break;
							}
							bit2_1++;
						}
						auto bit2_2 = bs2_2.begin();
						while (bit2_2 != bs2_2.end()) {
							if (RectDuangRect((*bit2_2)->GetRect(), (*boss_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*boss_it)->hurt()) {
									kill[4]++;
									kill_temp++;
									flag = true;
								}

								delete (*bit2_2);
								bs2_2.erase(bit2_2);

								break;
							}
							bit2_2++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*boss_it)->Show()) {
							delete (*boss_it);// 删除类指针
							boss_ep.erase(boss_it);// 踢出容器
							boss_it = boss_ep.begin();
						}
						else
							boss_it++;
					}

					break;// 跳出case
				}

					  /* 道具4：分叉子弹（一段时间） */
				case 4: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs3_1.push_back(new Bullet3_1(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（中））
						bs3_2.push_back(new Bullet3_2(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（左））
						bs3_3.push_back(new Bullet3_3(bulletimg, hp.GetRect()));// 我方子弹（分叉子弹（右））

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit3_1 = bs3_1.begin();
					while (bsit3_1 != bs3_1.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_1)->Show())
							bsit3_1 = bs3_1.erase(bsit3_1);
						else
							bsit3_1++;
					}
					auto bsit3_2 = bs3_2.begin();
					while (bsit3_2 != bs3_2.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_2)->Show())
							bsit3_2 = bs3_2.erase(bsit3_2);
						else
							bsit3_2++;
					}
					auto bsit3_3 = bs3_3.begin();
					while (bsit3_3 != bs3_3.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit3_3)->Show())
							bsit3_3 = bs3_3.erase(bsit3_3);
						else
							bsit3_3++;
					}

					/* 加载敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}


							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								delete (*bit3_1);
								bs3_1.erase(bit3_1);

								break;
							}
							bit3_1++;
						}
						auto bit3_2 = bs3_2.begin();
						while (bit3_2 != bs3_2.end()) {
							if (RectDuangRect((*bit3_2)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								delete (*bit3_2);
								bs3_2.erase(bit3_2);

								break;
							}
							bit3_2++;
						}
						auto bit3_3 = bs3_3.begin();
						while (bit3_3 != bs3_3.end()) {
							if (RectDuangRect((*bit3_3)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								delete (*bit3_3);
								bs3_3.erase(bit3_3);

								break;
							}
							bit3_3++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit3_1);
								bs3_1.erase(bit3_1);

								break;
							}
							bit3_1++;
						}
						auto bit3_2 = bs3_2.begin();
						while (bit3_2 != bs3_2.end()) {
							if (RectDuangRect((*bit3_2)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit3_2);
								bs3_2.erase(bit3_2);

								break;
							}
							bit3_2++;
						}
						auto bit3_3 = bs3_3.begin();
						while (bit3_3 != bs3_3.end()) {
							if (RectDuangRect((*bit3_3)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								delete (*bit3_3);
								bs3_3.erase(bit3_3);

								break;
							}
							bit3_3++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
							}

							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*mini_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								delete (*bit3_1);
								bs3_1.erase(bit3_1);

								break;
							}
							bit3_1++;
						}
						auto bit3_2 = bs3_2.begin();
						while (bit3_2 != bs3_2.end()) {
							if (RectDuangRect((*bit3_2)->GetRect(), (*mini_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								delete (*bit3_2);
								bs3_2.erase(bit3_2);

								break;
							}
							bit3_2++;
						}
						auto bit3_3 = bs3_3.begin();
						while (bit3_3 != bs3_3.end()) {
							if (RectDuangRect((*bit3_3)->GetRect(), (*mini_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								delete (*bit3_3);
								bs3_3.erase(bit3_3);

								break;
							}
							bit3_3++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*giant_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*giant_it)->dying()) {
								(*giant_it)->Dies();
								kill[3]++;
							}

							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*giant_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*giant_it)->hurt()) {
									kill[3]++;
									kill_temp++;
								}

								delete (*bit3_1);
								bs3_1.erase(bit3_1);

								break;
							}
							bit3_1++;
						}
						auto bit3_2 = bs3_2.begin();
						while (bit3_2 != bs3_2.end()) {
							if (RectDuangRect((*bit3_2)->GetRect(), (*giant_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*giant_it)->hurt()) {
									kill[3]++;
									kill_temp++;
								}

								delete (*bit3_2);
								bs3_2.erase(bit3_2);

								break;
							}
							bit3_2++;
						}
						auto bit3_3 = bs3_3.begin();
						while (bit3_3 != bs3_3.end()) {
							if (RectDuangRect((*bit3_3)->GetRect(), (*giant_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*giant_it)->hurt()) {
									kill[3]++;
									kill_temp++;
								}

								delete (*bit3_3);
								bs3_3.erase(bit3_3);

								break;
							}
							bit3_3++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}
					auto boss_it = boss_ep.begin();
					while (boss_it != boss_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*boss_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt(HP);

							break;
						}

						/* 如果我方子弹击中敌机 */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*boss_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*boss_it)->hurt()) {
									kill[4]++;
									kill_temp++;
									flag = true;
								}

								delete (*bit3_1);
								bs3_1.erase(bit3_1);

								break;
							}
							bit3_1++;
						}
						auto bit3_2 = bs3_2.begin();
						while (bit3_2 != bs3_2.end()) {
							if (RectDuangRect((*bit3_2)->GetRect(), (*boss_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*boss_it)->hurt()) {
									kill[4]++;
									kill_temp++;
									flag = true;
								}

								delete (*bit3_2);
								bs3_2.erase(bit3_2);

								break;
							}
							bit3_2++;
						}
						auto bit3_3 = bs3_3.begin();
						while (bit3_3 != bs3_3.end()) {
							if (RectDuangRect((*bit3_3)->GetRect(), (*boss_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*boss_it)->hurt()) {
									kill[4]++;
									kill_temp++;
									flag = true;
								}

								delete (*bit3_3);
								bs3_3.erase(bit3_3);

								break;
							}
							bit3_3++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*boss_it)->Show()) {
							delete (*boss_it);// 删除类指针
							boss_ep.erase(boss_it);// 踢出容器
							boss_it = boss_ep.begin();
						}
						else
							boss_it++;
					}

					break;// 跳出case
				}

					  /* 道具5：穿甲子弹（一段时间） */
				case 5: {
					/* 添加我方子弹 */
					bsing++;
					if (bsing == 101 - bs_frequency) {// 每隔一段时间发射一颗子弹
						bsing = 0;
						bs4.push_back(new Bullet4(bullet4img, hp.GetRect()));// 我方子弹（穿甲弹）

						/* 发射一定数量子弹后恢复正常状态 */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* 加载我方子弹 */
					auto bsit4 = bs4.begin();
					while (bsit4 != bs4.end()) {
						// 如果子弹飞出屏幕则去除
						if (!(*bsit4)->Show())
							bsit4 = bs4.erase(bsit4);
						else
							bsit4++;
					}

					/* 加载敌方飞机 */
					auto it = ep.begin();
					while (it != ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}

							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								break;
							}
							bit4++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*it)->Show()) {
							delete (*it);// 删除类指针
							ep.erase(it);// 踢出容器
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*mid_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								// 如果大于1条命，则减去1条命
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// 如果恰好1条命，则判定死亡，击杀数+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// 如果小于1条命，确认死亡
								else
									(*mid_it)->Dies();

								break;
							}
							bit4++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// 删除类指针
							mid_ep.erase(mid_it);// 踢出容器
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
							}

							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*mini_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								break;
							}
							bit4++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// 删除类指针
							mini_ep.erase(mini_it);// 踢出容器
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*giant_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt();
							if (!(*giant_it)->dying()) {
								(*giant_it)->Dies();
								kill[3]++;
							}

							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}

						/* 如果我方子弹击中敌机 */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*giant_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*giant_it)->hurt()) {
									kill[3]++;
									kill_temp++;
								}

								break;
							}
							bit4++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// 删除类指针
							giant_ep.erase(giant_it);// 踢出容器
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}
					auto boss_it = boss_ep.begin();
					while (boss_it != boss_ep.end()) {
						// 敌方飞机与我方飞机相撞
						if (RectDuangRect((*boss_it)->GetRect(), hp.GetRect())) {
							/* 结果 */
							is_play = hp.hurt(HP);

							break;
						}

						/* 如果我方子弹击中敌机 */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*boss_it)->GetRect())) {// 如果子弹击中敌机
								/* 结果 */
								if ((*boss_it)->hurt()) {
									kill[4]++;
									kill_temp++;
									flag = true;
								}

								break;
							}
							bit4++;
						}

						// 如果敌机飞出屏幕则去除
						if (!(*boss_it)->Show()) {
							delete (*boss_it);// 删除类指针
							boss_ep.erase(boss_it);// 踢出容器
							boss_it = boss_ep.begin();
						}
						else
							boss_it++;
					}

					break;// 跳出case
				}
				}

				/* 每杀一定数量敌人送一个道具 */
				if ((condition == 0) && (kill_temp >= KILL_FOR_GIFT)) {
					/* 随机发放道具（未完成） */
					gift_index = rand() % 5;
					AddGift(gift, giftimg[gift_index]);

					kill_temp = 0;
					bullets_total = 0;
				}
				/* 加载道具 */
				auto gift_it = gift.begin();
				while (gift_it != gift.end()) {
					// 成功拾取道具
					if (RectDuangRect((*gift_it)->GetRect(), hp.GetRect())) {
						condition = gift_index + 1;

						delete (*gift_it);// 删除类指针
						gift.erase(gift_it);// 踢出容器
						gift_it = gift.begin();
						break;
					}
					// 未能拾取道具（已经飞出屏幕）
					if (!(*gift_it)->Show()) {
						delete (*gift_it);// 删除类指针
						gift.erase(gift_it);// 踢出容器
						gift_it = gift.begin();
					}
					else
						gift_it++;
				}

				/* 右上角实时显示击杀数和得分 */
				score = kill[0] * 3 + kill[1] * 5 + kill[2] * 1 + kill[3] * 7 + kill[4] * 1000;
				PrintScore(kill, score);

				/* 检测是否过关 */
				if (score >= SCORE_5) {
					flag = true;
					is_play = false;
				}

				EndBatchDraw();// BeginBatchDraw和EndBatchDraw用于消除频闪				
			}

			stopBgmMusic();
			Over(kill, score, flag);// 结算界面
			break;
		}
	}

	return true;
}
