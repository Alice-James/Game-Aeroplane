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
#include <conio.h>// ������ͣ��Ϸ
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

	loadimage(&heroimg, _T(".\\res\\mplane.png"));// loadimage�������ڴ��ļ��ж�ȡͼ�����飺https://docs.easyx.cn/zh-cn/loadimage
	loadimage(&heroimg2, _T(".\\res\\mplane1.png"));// loadimage�������ڴ��ļ��ж�ȡͼ�����飺https://docs.easyx.cn/zh-cn/loadimage
	loadimage(&bgimg, _T(".\\res\\bg.png"), swidth, sheight * 2);// ����ͼƬ�������Ⱥ͸߶�
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
		// ���ؿ�ʼ����
		case 0: break;

		// �޾�ģʽ������1�أ���ͨ�л�
		// �ܶȣ�density = 5
		case 101: {
			/* �������� */
			BG bg = BG(bgimg);// ����
			Hero hp = Hero(heroimg);// ��ҷɻ�
			vector<Enemy*> ep;// �л���������ͨ��
			vector<Bullet*> bs;// �ҷ��ӵ���������ͨ��
			vector<Bullet2_1*> bs2_1;// �ҷ��ӵ�������˫���ӵ����󣩣�
			vector<Bullet2_2*> bs2_2;// �ҷ��ӵ�������˫���ӵ����ң���
			vector<Bullet3_1*> bs3_1;// �ҷ��ӵ��������ֲ��ӵ����У���
			vector<Bullet3_2*> bs3_2;// �ҷ��ӵ��������ֲ��ӵ����󣩣�
			vector<Bullet3_3*> bs3_3;// �ҷ��ӵ��������ֲ��ӵ����ң���
			vector<Bullet4*> bs4;// �ҷ��ӵ����������׵���
			vector<EBullet*> ebs;// �з��ӵ���������ͨ��
			vector<Gift*> gift;// ��������

			/* ����������� */
			int bsing = 0;// �����ҷ��ӵ�����Ƶ�ʣ���ͨ��
			int ebsing = 0;// ���Ƶз��ӵ�����Ƶ�ʣ���ͨ��
			int density = DENSITY;// ���Ƶл��ܶȣ���ͨ��

			/* ��������� */
			int kill[5] = {0, 0, 0, 0, 0};// ��¼���ֻ�ɱ����:{��ͨ�����ͣ�С�ͣ����ͣ�BOSS}
			int score = 0;// ��¼�÷֣�{��ͨ��3�����ͣ�5��С�ͣ�1�����ͣ�7��BOSS��31}
			int kill_temp = 0;// ��¼��ǰɱ���������ﵽһ��ֵ����㣬����ȷ�����͵���ʱ����
			int bullets_total = 0;// ��¼�е����ڼ䷢���ӵ������������л�����״̬
			int condition = 0;// �����л�����״̬��Ĭ��Ϊ0
			int gift_index = 0;// ���ڼ�¼��������

			playBgmMusic();

			/* ��ӿ��ֵл� */
			for (int i = 0; i < density; i++) {
				AddEnemy(ep, enemyimg, eboom);
			}

			/* ������Ϸ�� */
			while (is_play) {
				/* ���ر�������ҷɻ� */
				BeginBatchDraw();// BeginBatchDraw��EndBatchDraw��������Ƶ�������飺https://docs.easyx.cn/zh-cn/other-func
				bg.Show();
				Sleep(4);
				flushmessage();
				Sleep(1);
				hp.Control();
				hp.Show();

				/* ���ո���ͣ */
				if (GetAsyncKeyState(VK_SPACE) & 0x0001)
					while (!(GetAsyncKeyState(VK_SPACE) & 0x0001));

				/* ��ӵз��ӵ� */
				ebsing++;
				if (ebsing == 101 - ebs_frequency) {
					ebsing = 0;
					for (auto& i : ep)
						ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// �з��ӵ�����ͨ��
				}

				/* ��ӵл� */
				for (int i = 0; i < density - ep.size(); i++) {
					AddEnemy(ep, enemyimg, eboom);
				}

				/* ���صз��ӵ� */
				auto ebsit = ebs.begin();
				while (ebsit != ebs.end()) {
					// �ҷ��ɻ�������
					if (RectDuangRect((*ebsit)->GetRect(), hp.GetRect())) {
						/* ��� */
						is_play = hp.hurt();

						ebsit = ebs.erase(ebsit);
					}
					// ����ӵ��ɳ���Ļ��ȥ��
					else if (!(*ebsit)->Show())
						ebsit = ebs.erase(ebsit);
					else
						ebsit++;
				}
				
				/* ʰȡ���߽����Ӧ״̬ */
				switch (condition) {
					/* ����״̬ */
					case 0: {
						/* ����ҷ��ӵ� */
						bsing++;
						if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
							bsing = 0;
							bs.push_back(new Bullet(bulletimg, hp.GetRect()));// �ҷ��ӵ�����ͨ��
						}

						/* �����ҷ��ӵ� */
						auto bsit = bs.begin();
						while (bsit != bs.end()) {
							// ����ӵ��ɳ���Ļ��ȥ��
							if (!(*bsit)->Show())
								bsit = bs.erase(bsit);
							else
								bsit++;
						}

						/* ���صз��ɻ� */
						auto it = ep.begin();
						while (it != ep.end()) {
							// �з��ɻ����ҷ��ɻ���ײ
							if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
								/* ��� */
								is_play = hp.hurt();
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
									kill_temp++;
								}

								delete (*it);// ɾ����ָ��
								ep.erase(it);// �߳�����
								it = ep.begin();
							}

							/* ����ҷ��ӵ����ел� */
							auto bit = bs.begin();
							while (bit != bs.end()) {
								if (RectDuangRect((*bit)->GetRect(), (*it)->GetRect())) {
									/* ��� */
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

							// ����л��ɳ���Ļ��ȥ��
							if (!(*it)->Show()) {
								delete (*it);// ɾ����ָ��
								ep.erase(it);// �߳�����
								it = ep.begin();
							}
							else
								it++;
						}
						break;// ����case
					}

					/* ����1��������ֵ��һ���Ե��ߣ� */
					case 1: {
						hp.heal();

						condition = 0;// �ָ�����״̬

						break;// ����case
					}

					/* ����2����յл��͵з��ӵ���һ���Ե��ߣ� */
					case 2: {
						/* ��յз��ӵ� */
						auto ebsit = ebs.begin();
						while (ebsit != ebs.end()) {
							ebsit = ebs.erase(ebsit);
						}

						/* ��յз��ɻ� */
						auto it = ep.begin();
						while (it != ep.end()) {
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}

							// ����л��ɳ���Ļ��ȥ��
							if (!(*it)->Show()) {
								delete (*it);// ɾ����ָ��
								ep.erase(it);// �߳�����
								it = ep.begin();
							}
							else
								it++;
						}

						condition = 0;// �ָ�����״̬

						break;// ����case
					}

					/* ����3��˫���ӵ���һ��ʱ�䣩 */
					case 3: {
						/* ����ҷ��ӵ� */
						bsing++;
						if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
							bsing = 0;
							bs2_1.push_back(new Bullet2_1(bulletimg, hp.GetRect()));// �ҷ��ӵ���˫���ӵ����󣩣�
							bs2_2.push_back(new Bullet2_2(bulletimg, hp.GetRect()));// �ҷ��ӵ���˫���ӵ����ң���

							/* ����һ�������ӵ���ָ�����״̬ */
							bullets_total++;
							if (bullets_total >= BULLETS_MAX) {
								condition = 0;
								bullets_total = 0;
							}
						}

						/* �����ҷ��ӵ� */
						auto bsit2_1 = bs2_1.begin();
						while (bsit2_1 != bs2_1.end()) {
							// ����ӵ��ɳ���Ļ��ȥ��
							if (!(*bsit2_1)->Show())
								bsit2_1 = bs2_1.erase(bsit2_1);
							else
								bsit2_1++;
						}
						auto bsit2_2 = bs2_2.begin();
						while (bsit2_2 != bs2_2.end()) {
							// ����ӵ��ɳ���Ļ��ȥ��
							if (!(*bsit2_2)->Show())
								bsit2_2 = bs2_2.erase(bsit2_2);
							else
								bsit2_2++;
						}

						/* ���صз��ɻ� */
						auto it = ep.begin();
						while (it != ep.end()) {
							// �з��ɻ����ҷ��ɻ���ײ
							if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
								/* ��� */
								is_play = hp.hurt();
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								delete (*it);// ɾ����ָ��
								ep.erase(it);// �߳�����
								it = ep.begin();
							}

							/* ����ҷ��ӵ����ел� */
							auto bit2_1 = bs2_1.begin();
							while (bit2_1 != bs2_1.end()) {
								if (RectDuangRect((*bit2_1)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
									/* ��� */
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
								if (RectDuangRect((*bit2_2)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
									/* ��� */
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

							// ����л��ɳ���Ļ��ȥ��
							if (!(*it)->Show()) {
								delete (*it);// ɾ����ָ��
								ep.erase(it);// �߳�����
								it = ep.begin();
							}
							else
								it++;
						}
						break;// ����case
					}

					/* ����4���ֲ��ӵ���һ��ʱ�䣩 */
					case 4: {
						/* ����ҷ��ӵ� */
						bsing++;
						if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
							bsing = 0;
							bs3_1.push_back(new Bullet3_1(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����У���
							bs3_2.push_back(new Bullet3_2(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����󣩣�
							bs3_3.push_back(new Bullet3_3(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����ң���

							/* ����һ�������ӵ���ָ�����״̬ */
							bullets_total++;
							if (bullets_total >= BULLETS_MAX) {
								condition = 0;
								bullets_total = 0;
							}
						}

						/* �����ҷ��ӵ� */
						auto bsit3_1 = bs3_1.begin();
						while (bsit3_1 != bs3_1.end()) {
							// ����ӵ��ɳ���Ļ��ȥ��
							if (!(*bsit3_1)->Show())
								bsit3_1 = bs3_1.erase(bsit3_1);
							else
								bsit3_1++;
						}
						auto bsit3_2 = bs3_2.begin();
						while (bsit3_2 != bs3_2.end()) {
							// ����ӵ��ɳ���Ļ��ȥ��
							if (!(*bsit3_2)->Show())
								bsit3_2 = bs3_2.erase(bsit3_2);
							else
								bsit3_2++;
						}
						auto bsit3_3 = bs3_3.begin();
						while (bsit3_3 != bs3_3.end()) {
							// ����ӵ��ɳ���Ļ��ȥ��
							if (!(*bsit3_3)->Show())
								bsit3_3 = bs3_3.erase(bsit3_3);
							else
								bsit3_3++;
						}

						/* ���صз��ɻ� */
						auto it = ep.begin();
						while (it != ep.end()) {
							// �з��ɻ����ҷ��ɻ���ײ
							if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
								/* ��� */
								is_play = hp.hurt();
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}


								delete (*it);// ɾ����ָ��
								ep.erase(it);// �߳�����
								it = ep.begin();
							}

							/* ����ҷ��ӵ����ел� */
							auto bit3_1 = bs3_1.begin();
							while (bit3_1 != bs3_1.end()) {
								if (RectDuangRect((*bit3_1)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
									/* ��� */
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
								if (RectDuangRect((*bit3_2)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
									/* ��� */
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
								if (RectDuangRect((*bit3_3)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
									/* ��� */
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

							// ����л��ɳ���Ļ��ȥ��
							if (!(*it)->Show()) {
								delete (*it);// ɾ����ָ��
								ep.erase(it);// �߳�����
								it = ep.begin();
							}
							else
								it++;
						}
						break;// ����case
					}

					/* ����5�������ӵ���һ��ʱ�䣩 */
					case 5: {
						/* ����ҷ��ӵ� */
						bsing++;
						if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
							bsing = 0;
							bs4.push_back(new Bullet4(bullet4img, hp.GetRect()));// �ҷ��ӵ������׵���

							/* ����һ�������ӵ���ָ�����״̬ */
							bullets_total++;
							if (bullets_total >= BULLETS_MAX) {
								condition = 0;
								bullets_total = 0;
							}
						}

						/* �����ҷ��ӵ� */
						auto bsit4 = bs4.begin();
						while (bsit4 != bs4.end()) {
							// ����ӵ��ɳ���Ļ��ȥ��
							if (!(*bsit4)->Show())
								bsit4 = bs4.erase(bsit4);
							else
								bsit4++;
						}

						/* ���صз��ɻ� */
						auto it = ep.begin();
						while (it != ep.end()) {
							// �з��ɻ����ҷ��ɻ���ײ
							if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
								/* ��� */
								is_play = hp.hurt();
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								delete (*it);// ɾ����ָ��
								ep.erase(it);// �߳�����
								it = ep.begin();
							}

							/* ����ҷ��ӵ����ел� */
							auto bit4 = bs4.begin();
							while (bit4 != bs4.end()) {
								if (RectDuangRect((*bit4)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
									/* ��� */
									if (!(*it)->dying()) {
										(*it)->Dies();
										kill[0]++;
									}

									break;
								}
								bit4++;
							}

							// ����л��ɳ���Ļ��ȥ��
							if (!(*it)->Show()) {
								delete (*it);// ɾ����ָ��
								ep.erase(it);// �߳�����
								it = ep.begin();
							}
							else
								it++;
						}
						break;// ����case
					}
				}
				
				/* ÿɱһ������������һ������ */
				if ((condition == 0) && (kill_temp >= KILL_FOR_GIFT)) {
					/* ������ŵ��ߣ�δ��ɣ� */
					gift_index = rand() % 5;
					AddGift(gift, giftimg[gift_index]);

					kill_temp = 0;
					bullets_total = 0;
				}
				/* ���ص��� */
				auto gift_it = gift.begin();
				while (gift_it != gift.end()) {
					// �ɹ�ʰȡ����
					if (RectDuangRect((*gift_it)->GetRect(), hp.GetRect())) {
						condition = gift_index + 1;

						delete (*gift_it);// ɾ����ָ��
						gift.erase(gift_it);// �߳�����
						gift_it = gift.begin();
						break;
					}
					// δ��ʰȡ���ߣ��Ѿ��ɳ���Ļ��
					if (!(*gift_it)->Show()) {
						delete (*gift_it);// ɾ����ָ��
						gift.erase(gift_it);// �߳�����
						gift_it = gift.begin();
					}
					else
						gift_it++;
				}

				/* ���Ͻ�ʵʱ��ʾ��ɱ���͵÷� */
				score = kill[0] * 3 + kill[1] * 5 + kill[2] * 1 + kill[3] * 7 + kill[4] * 31;
				PrintScore(kill, score);

				EndBatchDraw();// BeginBatchDraw��EndBatchDraw��������Ƶ��				
			}

			stopBgmMusic();
			Over(kill, score);// �������
			break;
		}
		
		// �޾�ģʽ������2�أ����͵л�
		// �ܶȣ�mid_density = 3
		case 102: {
			/* �������� */
			BG bg = BG(bgimg);// ����
			Hero hp = Hero(heroimg);// ��ҷɻ�
			vector<midEnemy*> mid_ep;// �л����������ͣ�
			vector<Bullet*> bs;// �ҷ��ӵ���������ͨ��
			vector<Bullet2_1*> bs2_1;// �ҷ��ӵ�������˫���ӵ����󣩣�
			vector<Bullet2_2*> bs2_2;// �ҷ��ӵ�������˫���ӵ����ң���
			vector<Bullet3_1*> bs3_1;// �ҷ��ӵ��������ֲ��ӵ����У���
			vector<Bullet3_2*> bs3_2;// �ҷ��ӵ��������ֲ��ӵ����󣩣�
			vector<Bullet3_3*> bs3_3;// �ҷ��ӵ��������ֲ��ӵ����ң���
			vector<Bullet4*> bs4;// �ҷ��ӵ����������׵���
			vector<EBullet*> mid_ebs;// �з��ӵ����������ͣ�
			vector<Gift*> gift;// ��������

			/* ����������� */
			int bsing = 0;// �����ҷ��ӵ�����Ƶ�ʣ���ͨ��
			int mid_ebsing = 0;// ���Ƶз��ӵ�����Ƶ�ʣ����ͣ�
			int mid_density = MID_DENSITY;// ���Ƶл��ܶȣ����ͣ�

			/* ��������� */
			int kill[5] = { 0, 0, 0, 0, 0 };// ��¼���ֻ�ɱ����:{��ͨ�����ͣ�С�ͣ����ͣ�BOSS}
			int score = 0;// ��¼�÷֣�{��ͨ��3�����ͣ�5��С�ͣ�1�����ͣ�7��BOSS��31}
			int kill_temp = 0;// ��¼��ǰɱ���������ﵽһ��ֵ����㣬����ȷ�����͵���ʱ����
			int bullets_total = 0;// ��¼�е����ڼ䷢���ӵ������������л�����״̬
			int condition = 0;// �����л�����״̬��Ĭ��Ϊ0
			int gift_index = 0;// ���ڼ�¼��������

			playBgmMusic();

			/* ��ӿ��ֵл� */
			for (int i = 0; i < mid_density; i++) {
				AddEnemy(mid_ep, midEnemyimg, eboom);
			}

			/* ������Ϸ�� */
			while (is_play) {
				/* ���ر�������ҷɻ� */
				BeginBatchDraw();// BeginBatchDraw��EndBatchDraw��������Ƶ�������飺https://docs.easyx.cn/zh-cn/other-func
				bg.Show();
				Sleep(4);
				flushmessage();
				Sleep(1);
				hp.Control();
				hp.Show();

				/* ���ո���ͣ */
				if (GetAsyncKeyState(VK_SPACE) & 0x0001)
					while (!(GetAsyncKeyState(VK_SPACE) & 0x0001));

				/* ��ӵз��ӵ� */
				mid_ebsing++;
				if (mid_ebsing == 101 - mid_ebs_frequency) {
					mid_ebsing = 0;
					for (auto& i : mid_ep)
						mid_ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// �з��ӵ������ͣ�
				}

				/* ��ӵл� */
				for (int i = 0; i < mid_density - mid_ep.size(); i++) {
					AddEnemy(mid_ep, midEnemyimg, eboom);
				}

				/* ���صз��ӵ� */
				auto mid_ebsit = mid_ebs.begin();
				while (mid_ebsit != mid_ebs.end()) {
					// �ҷ��ɻ�������
					if (RectDuangRect((*mid_ebsit)->GetRect(), hp.GetRect())) {
						/* ��� */
						is_play = hp.hurt();

						mid_ebsit = mid_ebs.erase(mid_ebsit);
					}
					// ����ӵ��ɳ���Ļ��ȥ��
					else if (!(*mid_ebsit)->Show())
						mid_ebsit = mid_ebs.erase(mid_ebsit);
					else
						mid_ebsit++;
				}

				/* ʰȡ���߽����Ӧ״̬ */
				switch (condition) {
					/* ����״̬ */
				case 0: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs.push_back(new Bullet(bulletimg, hp.GetRect()));// �ҷ��ӵ�����ͨ��
					}

					/* �����ҷ��ӵ� */
					auto bsit = bs.begin();
					while (bsit != bs.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit)->Show())
							bsit = bs.erase(bsit);
						else
							bsit++;
					}

					/* ���صз��ɻ� */
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
								kill_temp++;
							}

							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*mid_it)->GetRect())) {
								/* ��� */
								// �������1���������ȥ1����
								if((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if((*mid_it)->how_many_lives() == 1){
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
								else
									(*mid_it)->Dies();

								delete (*bit);
								bs.erase(bit);

								break;
							}
							bit++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					break;// ����case
				}

					  /* ����1��������ֵ��һ���Ե��ߣ� */
				case 1: {
					hp.heal();

					condition = 0;// �ָ�����״̬

					break;// ����case
				}

					  /* ����2����յл��͵з��ӵ���һ���Ե��ߣ� */
				case 2: {
					/* ��յз��ӵ� */
					auto mid_ebsit = mid_ebs.begin();
					while (mid_ebsit != mid_ebs.end()) {
						mid_ebsit = mid_ebs.erase(mid_ebsit);
					}

					/* ��յз��ɻ� */
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						if (!(*mid_it)->dying()) {
							(*mid_it)->Dies();
							kill[1]++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}

					condition = 0;// �ָ�����״̬

					break;// ����case
				}

					  /* ����3��˫���ӵ���һ��ʱ�䣩 */
				case 3: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs2_1.push_back(new Bullet2_1(bulletimg, hp.GetRect()));// �ҷ��ӵ���˫���ӵ����󣩣�
						bs2_2.push_back(new Bullet2_2(bulletimg, hp.GetRect()));// �ҷ��ӵ���˫���ӵ����ң���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit2_1 = bs2_1.begin();
					while (bsit2_1 != bs2_1.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit2_1)->Show())
							bsit2_1 = bs2_1.erase(bsit2_1);
						else
							bsit2_1++;
					}
					auto bsit2_2 = bs2_2.begin();
					while (bsit2_2 != bs2_2.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit2_2)->Show())
							bsit2_2 = bs2_2.erase(bsit2_2);
						else
							bsit2_2++;
					}

					/* ���صз��ɻ� */
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
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
							if (RectDuangRect((*bit2_2)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
								else
									(*mid_it)->Dies();

								delete (*bit2_2);
								bs2_2.erase(bit2_2);

								break;
							}
							bit2_2++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					break;// ����case
				}

					  /* ����4���ֲ��ӵ���һ��ʱ�䣩 */
				case 4: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs3_1.push_back(new Bullet3_1(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����У���
						bs3_2.push_back(new Bullet3_2(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����󣩣�
						bs3_3.push_back(new Bullet3_3(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����ң���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit3_1 = bs3_1.begin();
					while (bsit3_1 != bs3_1.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_1)->Show())
							bsit3_1 = bs3_1.erase(bsit3_1);
						else
							bsit3_1++;
					}
					auto bsit3_2 = bs3_2.begin();
					while (bsit3_2 != bs3_2.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_2)->Show())
							bsit3_2 = bs3_2.erase(bsit3_2);
						else
							bsit3_2++;
					}
					auto bsit3_3 = bs3_3.begin();
					while (bsit3_3 != bs3_3.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_3)->Show())
							bsit3_3 = bs3_3.erase(bsit3_3);
						else
							bsit3_3++;
					}

					/* ���صз��ɻ� */
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
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
							if (RectDuangRect((*bit3_2)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
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
							if (RectDuangRect((*bit3_3)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
								else
									(*mid_it)->Dies();

								delete (*bit3_3);
								bs3_3.erase(bit3_3);

								break;
							}
							bit3_3++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					break;// ����case
				}

					  /* ����5�������ӵ���һ��ʱ�䣩 */
				case 5: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs4.push_back(new Bullet4(bullet4img, hp.GetRect()));// �ҷ��ӵ������׵���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit4 = bs4.begin();
					while (bsit4 != bs4.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit4)->Show())
							bsit4 = bs4.erase(bsit4);
						else
							bsit4++;
					}

					/* ���صз��ɻ� */
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
								else
									(*mid_it)->Dies();

								break;
							}
							bit4++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					break;// ����case
				}
				}

				/* ÿɱһ������������һ������ */
				if ((condition == 0) && (kill_temp >= KILL_FOR_GIFT)) {
					/* ������ŵ��ߣ�δ��ɣ� */
					gift_index = rand() % 5;
					AddGift(gift, giftimg[gift_index]);

					kill_temp = 0;
					bullets_total = 0;
				}
				/* ���ص��� */
				auto gift_it = gift.begin();
				while (gift_it != gift.end()) {
					// �ɹ�ʰȡ����
					if (RectDuangRect((*gift_it)->GetRect(), hp.GetRect())) {
						condition = gift_index + 1;

						delete (*gift_it);// ɾ����ָ��
						gift.erase(gift_it);// �߳�����
						gift_it = gift.begin();
						break;
					}
					// δ��ʰȡ���ߣ��Ѿ��ɳ���Ļ��
					if (!(*gift_it)->Show()) {
						delete (*gift_it);// ɾ����ָ��
						gift.erase(gift_it);// �߳�����
						gift_it = gift.begin();
					}
					else
						gift_it++;
				}

				/* ���Ͻ�ʵʱ��ʾ��ɱ���͵÷� */
				score = kill[0] * 3 + kill[1] * 5 + kill[2] * 1 + kill[3] * 7 + kill[4] * 31;
				PrintScore(kill, score);

				EndBatchDraw();// BeginBatchDraw��EndBatchDraw��������Ƶ��				
			}

			stopBgmMusic();
			Over(kill, score);// �������
			break;
		}

		// �޾�ģʽ������3�أ�С�͵л�
		// �ܶȣ�mini_density = 8
		case 103: {
			/* �������� */
			BG bg = BG(bgimg);// ����
			Hero hp = Hero(heroimg);// ��ҷɻ�
			vector<miniEnemy*> mini_ep;// �л�������С�ͣ�
			vector<Bullet*> bs;// �ҷ��ӵ���������ͨ��
			vector<Bullet2_1*> bs2_1;// �ҷ��ӵ�������˫���ӵ����󣩣�
			vector<Bullet2_2*> bs2_2;// �ҷ��ӵ�������˫���ӵ����ң���
			vector<Bullet3_1*> bs3_1;// �ҷ��ӵ��������ֲ��ӵ����У���
			vector<Bullet3_2*> bs3_2;// �ҷ��ӵ��������ֲ��ӵ����󣩣�
			vector<Bullet3_3*> bs3_3;// �ҷ��ӵ��������ֲ��ӵ����ң���
			vector<Bullet4*> bs4;// �ҷ��ӵ����������׵���
			vector<Gift*> gift;// ��������

			/* ����������� */
			int bsing = 0;// �����ҷ��ӵ�����Ƶ�ʣ���ͨ��
			int mini_density = MINI_DENSITY;// ���Ƶл��ܶȣ�С�ͣ�

			/* ��������� */
			int kill[5] = { 0, 0, 0, 0, 0 };// ��¼���ֻ�ɱ����:{��ͨ�����ͣ�С�ͣ����ͣ�BOSS}
			int score = 0;// ��¼�÷֣�{��ͨ��3�����ͣ�5��С�ͣ�1�����ͣ�7��BOSS��31}
			int kill_temp = 0;// ��¼��ǰɱ���������ﵽһ��ֵ����㣬����ȷ�����͵���ʱ����
			int bullets_total = 0;// ��¼�е����ڼ䷢���ӵ������������л�����״̬
			int condition = 0;// �����л�����״̬��Ĭ��Ϊ0
			int gift_index = 0;// ���ڼ�¼��������

			/* ��¼ʱ�� */
			DWORD startTime = timeGetTime();// ��ȡ��ʼʱ��
			int mini_time = 4000;// С�͵л�ˢ��ʱ��

			playBgmMusic();

			/* ��ӿ��ֵл� */
			for (int i = 0; i < mini_density; i++) {
				AddEnemy(mini_ep, miniEnemyimg, eboom, 1);
			}

			/* ������Ϸ�� */
			while (is_play) {
				/* ���ر�������ҷɻ� */
				BeginBatchDraw();// BeginBatchDraw��EndBatchDraw��������Ƶ�������飺https://docs.easyx.cn/zh-cn/other-func
				bg.Show();
				Sleep(4);
				flushmessage();
				Sleep(1);
				hp.Control();
				hp.Show();

				/* ���ո���ͣ */
				if (GetAsyncKeyState(VK_SPACE) & 0x0001)
					while (!(GetAsyncKeyState(VK_SPACE) & 0x0001));

				/* ��ӵл� */
				DWORD currentTime = timeGetTime(); // ��ȡ��ǰʱ��
				DWORD elapsedTime = currentTime - startTime; // ���㾭����ʱ��
				if (static_cast<int>(elapsedTime) >= mini_time) {
					int x = rand() % 3;
					for (int i = 0; i < mini_density; i++) {// ����л�
						AddEnemy(mini_ep, miniEnemyimg, eboom, x);
					}
					startTime = currentTime;
				}

				/* ʰȡ���߽����Ӧ״̬ */
				switch (condition) {
					/* ����״̬ */
				case 0: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs.push_back(new Bullet(bulletimg, hp.GetRect()));// �ҷ��ӵ�����ͨ��
					}

					/* �����ҷ��ӵ� */
					auto bsit = bs.begin();
					while (bsit != bs.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit)->Show())
							bsit = bs.erase(bsit);
						else
							bsit++;
					}

					/* ���صз��ɻ� */
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
								kill_temp++;
							}

							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*mini_it)->GetRect())) {
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					break;// ����case
				}

					  /* ����1��������ֵ��һ���Ե��ߣ� */
				case 1: {
					hp.heal();

					condition = 0;// �ָ�����״̬

					break;// ����case
				}

					  /* ����2����յл��͵з��ӵ���һ���Ե��ߣ� */
				case 2: {
					/* ��յз��ɻ� */
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						if (!(*mini_it)->dying()) {
							(*mini_it)->Dies();
							kill[2]++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}

					condition = 0;// �ָ�����״̬

					break;// ����case
				}

					  /* ����3��˫���ӵ���һ��ʱ�䣩 */
				case 3: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs2_1.push_back(new Bullet2_1(bulletimg, hp.GetRect()));// �ҷ��ӵ���˫���ӵ����󣩣�
						bs2_2.push_back(new Bullet2_2(bulletimg, hp.GetRect()));// �ҷ��ӵ���˫���ӵ����ң���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit2_1 = bs2_1.begin();
					while (bsit2_1 != bs2_1.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit2_1)->Show())
							bsit2_1 = bs2_1.erase(bsit2_1);
						else
							bsit2_1++;
					}
					auto bsit2_2 = bs2_2.begin();
					while (bsit2_2 != bs2_2.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit2_2)->Show())
							bsit2_2 = bs2_2.erase(bsit2_2);
						else
							bsit2_2++;
					}

					/* ���صз��ɻ� */
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
							}

							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*mini_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit2_2)->GetRect(), (*mini_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					break;// ����case
				}

					  /* ����4���ֲ��ӵ���һ��ʱ�䣩 */
				case 4: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs3_1.push_back(new Bullet3_1(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����У���
						bs3_2.push_back(new Bullet3_2(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����󣩣�
						bs3_3.push_back(new Bullet3_3(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����ң���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit3_1 = bs3_1.begin();
					while (bsit3_1 != bs3_1.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_1)->Show())
							bsit3_1 = bs3_1.erase(bsit3_1);
						else
							bsit3_1++;
					}
					auto bsit3_2 = bs3_2.begin();
					while (bsit3_2 != bs3_2.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_2)->Show())
							bsit3_2 = bs3_2.erase(bsit3_2);
						else
							bsit3_2++;
					}
					auto bsit3_3 = bs3_3.begin();
					while (bsit3_3 != bs3_3.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_3)->Show())
							bsit3_3 = bs3_3.erase(bsit3_3);
						else
							bsit3_3++;
					}

					/* ���صз��ɻ� */
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
							}

							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*mini_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_2)->GetRect(), (*mini_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_3)->GetRect(), (*mini_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					break;// ����case
				}

					  /* ����5�������ӵ���һ��ʱ�䣩 */
				case 5: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs4.push_back(new Bullet4(bullet4img, hp.GetRect()));// �ҷ��ӵ������׵���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit4 = bs4.begin();
					while (bsit4 != bs4.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit4)->Show())
							bsit4 = bs4.erase(bsit4);
						else
							bsit4++;
					}

					/* ���صз��ɻ� */
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
							}

							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*mini_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								break;
							}
							bit4++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					break;// ����case
				}
				}

				/* ÿɱһ������������һ������ */
				if ((condition == 0) && (kill_temp >= KILL_FOR_GIFT)) {
					/* ������ŵ��ߣ�δ��ɣ� */
					gift_index = rand() % 5;
					AddGift(gift, giftimg[gift_index]);

					kill_temp = 0;
					bullets_total = 0;
				}
				/* ���ص��� */
				auto gift_it = gift.begin();
				while (gift_it != gift.end()) {
					// �ɹ�ʰȡ����
					if (RectDuangRect((*gift_it)->GetRect(), hp.GetRect())) {
						condition = gift_index + 1;

						delete (*gift_it);// ɾ����ָ��
						gift.erase(gift_it);// �߳�����
						gift_it = gift.begin();
						break;
					}
					// δ��ʰȡ���ߣ��Ѿ��ɳ���Ļ��
					if (!(*gift_it)->Show()) {
						delete (*gift_it);// ɾ����ָ��
						gift.erase(gift_it);// �߳�����
						gift_it = gift.begin();
					}
					else
						gift_it++;
				}

				/* ���Ͻ�ʵʱ��ʾ��ɱ���͵÷� */
				score = kill[0] * 3 + kill[1] * 5 + kill[2] * 1 + kill[3] * 7 + kill[4] * 31;
				PrintScore(kill, score);

				EndBatchDraw();// BeginBatchDraw��EndBatchDraw��������Ƶ��				
			}

			stopBgmMusic();
			Over(kill, score);// �������
			break;
		}

		// �޾�ģʽ������4�أ����͵л�
		// �ܶȣ�giant_density = 2
		case 104: {
			/* �������� */
			BG bg = BG(bgimg);// ����
			Hero hp = Hero(heroimg);// ��ҷɻ�
			vector<giantEnemy*> giant_ep;// �л����������ͣ�
			vector<Bullet*> bs;// �ҷ��ӵ���������ͨ��
			vector<Bullet2_1*> bs2_1;// �ҷ��ӵ�������˫���ӵ����󣩣�
			vector<Bullet2_2*> bs2_2;// �ҷ��ӵ�������˫���ӵ����ң���
			vector<Bullet3_1*> bs3_1;// �ҷ��ӵ��������ֲ��ӵ����У���
			vector<Bullet3_2*> bs3_2;// �ҷ��ӵ��������ֲ��ӵ����󣩣�
			vector<Bullet3_3*> bs3_3;// �ҷ��ӵ��������ֲ��ӵ����ң���
			vector<Bullet4*> bs4;// �ҷ��ӵ����������׵���
			vector<EBullet*> giant_ebs;// �з��ӵ����������ͣ�
			vector<Gift*> gift;// ��������

			/* ����������� */
			int bsing = 0;// �����ҷ��ӵ�����Ƶ�ʣ���ͨ��
			int giant_ebsing = 0;// ���Ƶз��ӵ�����Ƶ�ʣ����ͣ�
			int giant_density = GIANT_DENSITY;// ���Ƶл��ܶȣ����ͣ�

			/* ��������� */
			int kill[5] = { 0, 0, 0, 0, 0 };// ��¼���ֻ�ɱ����:{��ͨ�����ͣ�С�ͣ����ͣ�BOSS}
			int score = 0;// ��¼�÷֣�{��ͨ��3�����ͣ�5��С�ͣ�1�����ͣ�7��BOSS��31}
			int kill_temp = 0;// ��¼��ǰɱ���������ﵽһ��ֵ����㣬����ȷ�����͵���ʱ����
			int bullets_total = 0;// ��¼�е����ڼ䷢���ӵ������������л�����״̬
			int condition = 0;// �����л�����״̬��Ĭ��Ϊ0
			int gift_index = 0;// ���ڼ�¼��������

			playBgmMusic();

			/* ��ӿ��ֵл� */
			for (int i = 0; i < giant_density; i++) {
				AddEnemy(giant_ep, giantEnemyimg, eboom);
			}

			/* ������Ϸ�� */
			while (is_play) {
				/* ���ر�������ҷɻ� */
				BeginBatchDraw();// BeginBatchDraw��EndBatchDraw��������Ƶ�������飺https://docs.easyx.cn/zh-cn/other-func
				bg.Show();
				Sleep(4);
				flushmessage();
				Sleep(1);
				hp.Control();
				hp.Show();

				/* ���ո���ͣ */
				if (GetAsyncKeyState(VK_SPACE) & 0x0001)
					while (!(GetAsyncKeyState(VK_SPACE) & 0x0001));

				/* ��ӵз��ӵ� */
				giant_ebsing++;
				if (giant_ebsing == 101 - giant_ebs_frequency) {
					giant_ebsing = 0;
					for (auto& i : giant_ep)
						giant_ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// �з��ӵ������ͣ�
				}

				/* ��ӵл� */
				for (int i = 0; i < giant_density - giant_ep.size(); i++) {
					AddEnemy(giant_ep, giantEnemyimg, eboom);
				}

				/* ���صз��ӵ� */
				auto giant_ebsit = giant_ebs.begin();
				while (giant_ebsit != giant_ebs.end()) {
					// �ҷ��ɻ�������
					if (RectDuangRect((*giant_ebsit)->GetRect(), hp.GetRect())) {
						/* ��� */
						is_play = hp.hurt();

						giant_ebsit = giant_ebs.erase(giant_ebsit);
					}
					// ����ӵ��ɳ���Ļ��ȥ��
					else if (!(*giant_ebsit)->Show())
						giant_ebsit = giant_ebs.erase(giant_ebsit);
					else
						giant_ebsit++;
				}

				/* ʰȡ���߽����Ӧ״̬ */
				switch (condition) {
					/* ����״̬ */
				case 0: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs.push_back(new Bullet(bulletimg, hp.GetRect()));// �ҷ��ӵ�����ͨ��
					}

					/* �����ҷ��ӵ� */
					auto bsit = bs.begin();
					while (bsit != bs.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit)->Show())
							bsit = bs.erase(bsit);
						else
							bsit++;
					}

					/* ���صз��ɻ� */
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*giant_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*giant_it)->dying()) {
								(*giant_it)->Dies();
								kill[3]++;
								kill_temp++;
							}

							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*giant_it)->GetRect())) {
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}
					break;// ����case
				}

					  /* ����1��������ֵ��һ���Ե��ߣ� */
				case 1: {
					hp.heal();

					condition = 0;// �ָ�����״̬

					break;// ����case
				}

					  /* ����2����յл��͵з��ӵ���һ���Ե��ߣ� */
				case 2: {
					/* ��յз��ӵ� */
					auto giant_ebsit = giant_ebs.begin();
					while (giant_ebsit != giant_ebs.end()) {
						giant_ebsit = giant_ebs.erase(giant_ebsit);
					}

					/* ��յз��ɻ� */
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						if (!(*giant_it)->dying()) {
							(*giant_it)->Dies();
							kill[3]++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}

					condition = 0;// �ָ�����״̬

					break;// ����case
				}

					  /* ����3��˫���ӵ���һ��ʱ�䣩 */
				case 3: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs2_1.push_back(new Bullet2_1(bulletimg, hp.GetRect()));// �ҷ��ӵ���˫���ӵ����󣩣�
						bs2_2.push_back(new Bullet2_2(bulletimg, hp.GetRect()));// �ҷ��ӵ���˫���ӵ����ң���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit2_1 = bs2_1.begin();
					while (bsit2_1 != bs2_1.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit2_1)->Show())
							bsit2_1 = bs2_1.erase(bsit2_1);
						else
							bsit2_1++;
					}
					auto bsit2_2 = bs2_2.begin();
					while (bsit2_2 != bs2_2.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit2_2)->Show())
							bsit2_2 = bs2_2.erase(bsit2_2);
						else
							bsit2_2++;
					}

					/* ���صз��ɻ� */
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*giant_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*giant_it)->dying()) {
								(*giant_it)->Dies();
								kill[3]++;
							}

							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*giant_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit2_2)->GetRect(), (*giant_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}
					break;// ����case
				}

					  /* ����4���ֲ��ӵ���һ��ʱ�䣩 */
				case 4: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs3_1.push_back(new Bullet3_1(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����У���
						bs3_2.push_back(new Bullet3_2(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����󣩣�
						bs3_3.push_back(new Bullet3_3(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����ң���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit3_1 = bs3_1.begin();
					while (bsit3_1 != bs3_1.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_1)->Show())
							bsit3_1 = bs3_1.erase(bsit3_1);
						else
							bsit3_1++;
					}
					auto bsit3_2 = bs3_2.begin();
					while (bsit3_2 != bs3_2.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_2)->Show())
							bsit3_2 = bs3_2.erase(bsit3_2);
						else
							bsit3_2++;
					}
					auto bsit3_3 = bs3_3.begin();
					while (bsit3_3 != bs3_3.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_3)->Show())
							bsit3_3 = bs3_3.erase(bsit3_3);
						else
							bsit3_3++;
					}

					/* ���صз��ɻ� */
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*giant_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*giant_it)->dying()) {
								(*giant_it)->Dies();
								kill[3]++;
							}

							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*giant_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_2)->GetRect(), (*giant_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_3)->GetRect(), (*giant_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}
					break;// ����case
				}

					  /* ����5�������ӵ���һ��ʱ�䣩 */
				case 5: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs4.push_back(new Bullet4(bullet4img, hp.GetRect()));// �ҷ��ӵ������׵���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit4 = bs4.begin();
					while (bsit4 != bs4.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit4)->Show())
							bsit4 = bs4.erase(bsit4);
						else
							bsit4++;
					}

					/* ���صз��ɻ� */
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*giant_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*giant_it)->dying()) {
								(*giant_it)->Dies();
								kill[3]++;
							}

							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*giant_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								if ((*giant_it)->hurt()) {
									kill[3]++;
									kill_temp++;
								}

								break;
							}
							bit4++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}
					break;// ����case
				}
				}

				/* ÿɱһ������������һ������ */
				if ((condition == 0) && (kill_temp >= KILL_FOR_GIFT)) {
					/* ������ŵ��ߣ�δ��ɣ� */
					gift_index = rand() % 5;
					AddGift(gift, giftimg[gift_index]);

					kill_temp = 0;
					bullets_total = 0;
				}
				/* ���ص��� */
				auto gift_it = gift.begin();
				while (gift_it != gift.end()) {
					// �ɹ�ʰȡ����
					if (RectDuangRect((*gift_it)->GetRect(), hp.GetRect())) {
						condition = gift_index + 1;

						delete (*gift_it);// ɾ����ָ��
						gift.erase(gift_it);// �߳�����
						gift_it = gift.begin();
						break;
					}
					// δ��ʰȡ���ߣ��Ѿ��ɳ���Ļ��
					if (!(*gift_it)->Show()) {
						delete (*gift_it);// ɾ����ָ��
						gift.erase(gift_it);// �߳�����
						gift_it = gift.begin();
					}
					else
						gift_it++;
				}

				/* ���Ͻ�ʵʱ��ʾ��ɱ���͵÷� */
				score = kill[0] * 3 + kill[1] * 5 + kill[2] * 1 + kill[3] * 7 + kill[4] * 31;
				PrintScore(kill, score);

				EndBatchDraw();// BeginBatchDraw��EndBatchDraw��������Ƶ��				
			}

			stopBgmMusic();
			Over(kill, score);// �������
			break;
		}

		// �޾�ģʽ������5�أ�BOSS
		// �ܶȣ�boss_density = 31
		case 105: {
			/* �������� */
			BG bg = BG(bgimg);// ����
			Hero hp = Hero(heroimg);// ��ҷɻ�
			vector<bossEnemy*> boss_ep;// �л�������BOSS��
			vector<Bullet*> bs;// �ҷ��ӵ���������ͨ��
			vector<Bullet2_1*> bs2_1;// �ҷ��ӵ�������˫���ӵ����󣩣�
			vector<Bullet2_2*> bs2_2;// �ҷ��ӵ�������˫���ӵ����ң���
			vector<Bullet3_1*> bs3_1;// �ҷ��ӵ��������ֲ��ӵ����У���
			vector<Bullet3_2*> bs3_2;// �ҷ��ӵ��������ֲ��ӵ����󣩣�
			vector<Bullet3_3*> bs3_3;// �ҷ��ӵ��������ֲ��ӵ����ң���
			vector<Bullet4*> bs4;// �ҷ��ӵ����������׵���
			vector<BossSkill_1*> boss_skill_1;// BOSS�ӵ�������skill_1��
			vector<BossSkill_2*> boss_skill_2;// BOSS�ӵ�������skill_2��
			vector<BossSkill_3*> boss_skill_3;// BOSS�ӵ�������skill_3��
			vector<Gift*> gift;// ��������

			/* ����������� */
			int bsing = 0;// �����ҷ��ӵ�����Ƶ�ʣ���ͨ��
			int boss_ebsing = 0;// ���Ƶз��ӵ�����Ƶ�ʣ�BOSS��
			int boss_density = BOSS_DENSITY;// ���Ƶл��ܶȣ�BOSS��

			/* ��������� */
			int kill[5] = { 0, 0, 0, 0, 0 };// ��¼���ֻ�ɱ����:{��ͨ�����ͣ�С�ͣ����ͣ�BOSS}
			int score = 0;// ��¼�÷֣�{��ͨ��3�����ͣ�5��С�ͣ�1�����ͣ�7��BOSS��31}
			int kill_temp = 0;// ��¼��ǰɱ���������ﵽһ��ֵ����㣬����ȷ�����͵���ʱ����
			int bullets_total = 0;// ��¼�е����ڼ䷢���ӵ������������л�����״̬
			int condition = 0;// �����л�����״̬��Ĭ��Ϊ0
			int gift_index = 0;// ���ڼ�¼��������

			playBgmMusic();

			/* ��ӿ��ֵл� */
			for (int i = 0; i < boss_density; i++) {
				AddEnemy(boss_ep, bossEnemyimg, eboom);
			}

			/* ������Ϸ�� */
			while (is_play) {
				/* ���ر�������ҷɻ� */
				BeginBatchDraw();// BeginBatchDraw��EndBatchDraw��������Ƶ�������飺https://docs.easyx.cn/zh-cn/other-func
				bg.Show();
				Sleep(4);
				flushmessage();
				Sleep(1);
				hp.Control();
				hp.Show();

				/* ���ո���ͣ */
				if (GetAsyncKeyState(VK_SPACE) & 0x0001)
					while (!(GetAsyncKeyState(VK_SPACE) & 0x0001));

				/* ��ӵз��ӵ� */
				boss_ebsing++;
				if (boss_ebsing == 101 - boss_ebs_frequency) {
					boss_ebsing = 0;
					for (auto& i : boss_ep) {
						// boss_skill_1������ʣ�50%
						if (rand() % 2 != 0)
							boss_skill_1.push_back(new BossSkill_1(bossSkill_1img, i->GetRect()));
						// boss_skill_2������ʣ�100%
						boss_skill_2.push_back(new BossSkill_2(bossSkill_2img, i->GetRect()));
						// boss_skill_3������ʣ�25%
						if (rand() % 4 == 0)
							boss_skill_3.push_back(new BossSkill_3(bossSkill_3img, i->GetRect()));
					}
				}

				/* ��ӵл� */
				for (int i = 0; i < boss_density - boss_ep.size(); i++) {
					AddEnemy(boss_ep, bossEnemyimg, eboom);
				}

				/* ���صз��ӵ� */
				auto boss_skill_1it = boss_skill_1.begin();
				while (boss_skill_1it != boss_skill_1.end()) {
					// �ҷ��ɻ�������
					if (RectDuangRect((*boss_skill_1it)->GetRect(), hp.GetRect())) {
						/* ��� */
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
					// �ҷ��ɻ�������
					if (RectDuangRect((*boss_skill_2it)->GetRect(), hp.GetRect())) {
						/* ��� */
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
					// �ҷ��ɻ�������
					if (RectDuangRect((*boss_skill_3it)->GetRect(), hp.GetRect())) {
						/* ��� */
						is_play = hp.hurt(HP);

						boss_skill_3it = boss_skill_3.erase(boss_skill_3it);
					}
					else if (!(*boss_skill_3it)->Show())
						boss_skill_3it = boss_skill_3.erase(boss_skill_3it);
					else
						boss_skill_3it++;
				}
				
				/* ʰȡ���߽����Ӧ״̬ */
				switch (condition) {
					/* ����״̬ */
				case 0: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs.push_back(new Bullet(bulletimg, hp.GetRect()));// �ҷ��ӵ�����ͨ��
					}

					/* �����ҷ��ӵ� */
					auto bsit = bs.begin();
					while (bsit != bs.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit)->Show())
							bsit = bs.erase(bsit);
						else
							bsit++;
					}

					/* ���صз��ɻ� */
					auto boss_it = boss_ep.begin();
					while (boss_it != boss_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*boss_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt(HP);

							break;
						}

						/* ����ҷ��ӵ����ел� */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*boss_it)->GetRect())) {
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*boss_it)->Show()) {
							delete (*boss_it);// ɾ����ָ��
							boss_ep.erase(boss_it);// �߳�����
							boss_it = boss_ep.begin();
						}
						else
							boss_it++;
					}
					break;// ����case
				}

					  /* ����1��������ֵ��һ���Ե��ߣ� */
				case 1: {
					hp.heal();

					condition = 0;// �ָ�����״̬

					break;// ����case
				}

					  /* ����2����յл��͵з��ӵ���һ���Ե��ߣ� */
				case 2: {
					/* ��յз��ӵ� */
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

					/* ��յз��ɻ� */
					auto boss_it = boss_ep.begin();
					while (boss_it != boss_ep.end()) {
						if (!(*boss_it)->dying()) {
							(*boss_it)->Dies();
							kill[4]++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*boss_it)->Show()) {
							delete (*boss_it);// ɾ����ָ��
							boss_ep.erase(boss_it);// �߳�����
							boss_it = boss_ep.begin();
						}
						else
							boss_it++;
					}

					condition = 0;// �ָ�����״̬

					break;// ����case
				}

					  /* ����3��˫���ӵ���һ��ʱ�䣩 */
				case 3: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs2_1.push_back(new Bullet2_1(bulletimg, hp.GetRect()));// �ҷ��ӵ���˫���ӵ����󣩣�
						bs2_2.push_back(new Bullet2_2(bulletimg, hp.GetRect()));// �ҷ��ӵ���˫���ӵ����ң���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit2_1 = bs2_1.begin();
					while (bsit2_1 != bs2_1.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit2_1)->Show())
							bsit2_1 = bs2_1.erase(bsit2_1);
						else
							bsit2_1++;
					}
					auto bsit2_2 = bs2_2.begin();
					while (bsit2_2 != bs2_2.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit2_2)->Show())
							bsit2_2 = bs2_2.erase(bsit2_2);
						else
							bsit2_2++;
					}

					/* ���صз��ɻ� */
					auto boss_it = boss_ep.begin();
					while (boss_it != boss_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*boss_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt(HP);

							break;
						}

						/* ����ҷ��ӵ����ел� */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*boss_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit2_2)->GetRect(), (*boss_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*boss_it)->Show()) {
							delete (*boss_it);// ɾ����ָ��
							boss_ep.erase(boss_it);// �߳�����
							boss_it = boss_ep.begin();
						}
						else
							boss_it++;
					}
					break;// ����case
				}

					  /* ����4���ֲ��ӵ���һ��ʱ�䣩 */
				case 4: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs3_1.push_back(new Bullet3_1(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����У���
						bs3_2.push_back(new Bullet3_2(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����󣩣�
						bs3_3.push_back(new Bullet3_3(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����ң���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit3_1 = bs3_1.begin();
					while (bsit3_1 != bs3_1.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_1)->Show())
							bsit3_1 = bs3_1.erase(bsit3_1);
						else
							bsit3_1++;
					}
					auto bsit3_2 = bs3_2.begin();
					while (bsit3_2 != bs3_2.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_2)->Show())
							bsit3_2 = bs3_2.erase(bsit3_2);
						else
							bsit3_2++;
					}
					auto bsit3_3 = bs3_3.begin();
					while (bsit3_3 != bs3_3.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_3)->Show())
							bsit3_3 = bs3_3.erase(bsit3_3);
						else
							bsit3_3++;
					}

					/* ���صз��ɻ� */
					auto boss_it = boss_ep.begin();
					while (boss_it != boss_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*boss_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt(HP);

							break;
						}

						/* ����ҷ��ӵ����ел� */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*boss_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_2)->GetRect(), (*boss_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_3)->GetRect(), (*boss_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*boss_it)->Show()) {
							delete (*boss_it);// ɾ����ָ��
							boss_ep.erase(boss_it);// �߳�����
							boss_it = boss_ep.begin();
						}
						else
							boss_it++;
					}
					break;// ����case
				}

					  /* ����5�������ӵ���һ��ʱ�䣩 */
				case 5: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs4.push_back(new Bullet4(bullet4img, hp.GetRect()));// �ҷ��ӵ������׵���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit4 = bs4.begin();
					while (bsit4 != bs4.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit4)->Show())
							bsit4 = bs4.erase(bsit4);
						else
							bsit4++;
					}

					/* ���صз��ɻ� */
					auto boss_it = boss_ep.begin();
					while (boss_it != boss_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*boss_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt(HP);

							break;
						}

						/* ����ҷ��ӵ����ел� */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*boss_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								if ((*boss_it)->hurt()) {
									kill[4]++;
									kill_temp++;
								}

								break;
							}
							bit4++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*boss_it)->Show()) {
							delete (*boss_it);// ɾ����ָ��
							boss_ep.erase(boss_it);// �߳�����
							boss_it = boss_ep.begin();
						}
						else
							boss_it++;
					}
					break;// ����case
				}
				}

				/* ÿɱһ������������һ������ */
				if ((condition == 0) && (kill_temp >= KILL_FOR_GIFT)) {
					/* ������ŵ��ߣ�δ��ɣ� */
					gift_index = rand() % 5;
					AddGift(gift, giftimg[gift_index]);

					kill_temp = 0;
					bullets_total = 0;
				}
				/* ���ص��� */
				auto gift_it = gift.begin();
				while (gift_it != gift.end()) {
					// �ɹ�ʰȡ����
					if (RectDuangRect((*gift_it)->GetRect(), hp.GetRect())) {
						condition = gift_index + 1;

						delete (*gift_it);// ɾ����ָ��
						gift.erase(gift_it);// �߳�����
						gift_it = gift.begin();
						break;
					}
					// δ��ʰȡ���ߣ��Ѿ��ɳ���Ļ��
					if (!(*gift_it)->Show()) {
						delete (*gift_it);// ɾ����ָ��
						gift.erase(gift_it);// �߳�����
						gift_it = gift.begin();
					}
					else
						gift_it++;
				}

				/* ���Ͻ�ʵʱ��ʾ��ɱ���͵÷� */
				score = kill[0] * 3 + kill[1] * 5 + kill[2] * 1 + kill[3] * 7 + kill[4] * 31;
				PrintScore(kill, score);

				EndBatchDraw();// BeginBatchDraw��EndBatchDraw��������Ƶ��				
			}

			stopBgmMusic();
			Over(kill, score);// �������
			break;
		}

		// ����ģʽ������1��
		// ��ͨ�л�
		// score 300
		case 201: {
			/* �������� */
			BG bg = BG(bgimg);// ����
			Hero hp = Hero(heroimg);// ��ҷɻ�
			vector<Enemy*> ep;// �л���������ͨ��
			vector<Bullet*> bs;// �ҷ��ӵ���������ͨ��
			vector<Bullet2_1*> bs2_1;// �ҷ��ӵ�������˫���ӵ����󣩣�
			vector<Bullet2_2*> bs2_2;// �ҷ��ӵ�������˫���ӵ����ң���
			vector<Bullet3_1*> bs3_1;// �ҷ��ӵ��������ֲ��ӵ����У���
			vector<Bullet3_2*> bs3_2;// �ҷ��ӵ��������ֲ��ӵ����󣩣�
			vector<Bullet3_3*> bs3_3;// �ҷ��ӵ��������ֲ��ӵ����ң���
			vector<Bullet4*> bs4;// �ҷ��ӵ����������׵���
			vector<EBullet*> ebs;// �з��ӵ���������ͨ��
			vector<Gift*> gift;// ��������

			/* ����������� */
			int bsing = 0;// �����ҷ��ӵ�����Ƶ�ʣ���ͨ��
			int ebsing = 0;// ���Ƶз��ӵ�����Ƶ�ʣ���ͨ��
			int density = DENSITY;// ���Ƶл��ܶȣ���ͨ��

			/* ��������� */
			int kill[5] = { 0, 0, 0, 0, 0 };// ��¼���ֻ�ɱ����:{��ͨ�����ͣ�С�ͣ����ͣ�BOSS}
			int score = 0;// ��¼�÷֣�{��ͨ��3�����ͣ�5��С�ͣ�1�����ͣ�7��BOSS��31}
			int kill_temp = 0;// ��¼��ǰɱ���������ﵽһ��ֵ����㣬����ȷ�����͵���ʱ����
			int bullets_total = 0;// ��¼�е����ڼ䷢���ӵ������������л�����״̬
			int condition = 0;// �����л�����״̬��Ĭ��Ϊ0
			int gift_index = 0;// ���ڼ�¼��������
			bool flag = false;// �ж��Ƿ����

			playBgmMusic();

			/* ��ӿ��ֵл� */
			for (int i = 0; i < density; i++) {
				AddEnemy(ep, enemyimg, eboom);
			}

			/* ������Ϸ�� */
			while (is_play) {
				/* ���ر�������ҷɻ� */
				BeginBatchDraw();// BeginBatchDraw��EndBatchDraw��������Ƶ�������飺https://docs.easyx.cn/zh-cn/other-func
				bg.Show();
				Sleep(4);
				flushmessage();
				Sleep(1);
				hp.Control();
				hp.Show();

				/* ���ո���ͣ */
				if (GetAsyncKeyState(VK_SPACE) & 0x0001)
					while (!(GetAsyncKeyState(VK_SPACE) & 0x0001));

				/* ��ӵз��ӵ� */
				ebsing++;
				if (ebsing == 101 - ebs_frequency) {
					ebsing = 0;
					for (auto& i : ep)
						ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// �з��ӵ�����ͨ��
				}

				/* ��ӵл� */
				for (int i = 0; i < density - ep.size(); i++) {
					AddEnemy(ep, enemyimg, eboom);
				}

				/* ���صз��ӵ� */
				auto ebsit = ebs.begin();
				while (ebsit != ebs.end()) {
					// �ҷ��ɻ�������
					if (RectDuangRect((*ebsit)->GetRect(), hp.GetRect())) {
						/* ��� */
						is_play = hp.hurt();

						ebsit = ebs.erase(ebsit);
					}
					// ����ӵ��ɳ���Ļ��ȥ��
					else if (!(*ebsit)->Show())
						ebsit = ebs.erase(ebsit);
					else
						ebsit++;
				}

				/* ʰȡ���߽����Ӧ״̬ */
				switch (condition) {
					/* ����״̬ */
				case 0: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs.push_back(new Bullet(bulletimg, hp.GetRect()));// �ҷ��ӵ�����ͨ��
					}

					/* �����ҷ��ӵ� */
					auto bsit = bs.begin();
					while (bsit != bs.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit)->Show())
							bsit = bs.erase(bsit);
						else
							bsit++;
					}

					/* ���صз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
								kill_temp++;
							}

							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*it)->GetRect())) {
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}
						else
							it++;
					}
					break;// ����case
				}

					  /* ����1��������ֵ��һ���Ե��ߣ� */
				case 1: {
					hp.heal();

					condition = 0;// �ָ�����״̬

					break;// ����case
				}

					  /* ����2����յл��͵з��ӵ���һ���Ե��ߣ� */
				case 2: {
					/* ��յз��ӵ� */
					auto ebsit = ebs.begin();
					while (ebsit != ebs.end()) {
						ebsit = ebs.erase(ebsit);
					}

					/* ��յз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						if (!(*it)->dying()) {
							(*it)->Dies();
							kill[0]++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}
						else
							it++;
					}

					condition = 0;// �ָ�����״̬

					break;// ����case
				}

					  /* ����3��˫���ӵ���һ��ʱ�䣩 */
				case 3: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs2_1.push_back(new Bullet2_1(bulletimg, hp.GetRect()));// �ҷ��ӵ���˫���ӵ����󣩣�
						bs2_2.push_back(new Bullet2_2(bulletimg, hp.GetRect()));// �ҷ��ӵ���˫���ӵ����ң���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit2_1 = bs2_1.begin();
					while (bsit2_1 != bs2_1.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit2_1)->Show())
							bsit2_1 = bs2_1.erase(bsit2_1);
						else
							bsit2_1++;
					}
					auto bsit2_2 = bs2_2.begin();
					while (bsit2_2 != bs2_2.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit2_2)->Show())
							bsit2_2 = bs2_2.erase(bsit2_2);
						else
							bsit2_2++;
					}

					/* ���صз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}

							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit2_2)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}
						else
							it++;
					}
					break;// ����case
				}

					  /* ����4���ֲ��ӵ���һ��ʱ�䣩 */
				case 4: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs3_1.push_back(new Bullet3_1(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����У���
						bs3_2.push_back(new Bullet3_2(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����󣩣�
						bs3_3.push_back(new Bullet3_3(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����ң���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit3_1 = bs3_1.begin();
					while (bsit3_1 != bs3_1.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_1)->Show())
							bsit3_1 = bs3_1.erase(bsit3_1);
						else
							bsit3_1++;
					}
					auto bsit3_2 = bs3_2.begin();
					while (bsit3_2 != bs3_2.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_2)->Show())
							bsit3_2 = bs3_2.erase(bsit3_2);
						else
							bsit3_2++;
					}
					auto bsit3_3 = bs3_3.begin();
					while (bsit3_3 != bs3_3.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_3)->Show())
							bsit3_3 = bs3_3.erase(bsit3_3);
						else
							bsit3_3++;
					}

					/* ���صз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}


							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_2)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_3)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}
						else
							it++;
					}
					break;// ����case
				}

					  /* ����5�������ӵ���һ��ʱ�䣩 */
				case 5: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs4.push_back(new Bullet4(bullet4img, hp.GetRect()));// �ҷ��ӵ������׵���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit4 = bs4.begin();
					while (bsit4 != bs4.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit4)->Show())
							bsit4 = bs4.erase(bsit4);
						else
							bsit4++;
					}

					/* ���صз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}

							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								break;
							}
							bit4++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}
						else
							it++;
					}
					break;// ����case
				}
				}

				/* ÿɱһ������������һ������ */
				if ((condition == 0) && (kill_temp >= KILL_FOR_GIFT)) {
					/* ������ŵ��ߣ�δ��ɣ� */
					gift_index = rand() % 5;
					AddGift(gift, giftimg[gift_index]);

					kill_temp = 0;
					bullets_total = 0;
				}
				/* ���ص��� */
				auto gift_it = gift.begin();
				while (gift_it != gift.end()) {
					// �ɹ�ʰȡ����
					if (RectDuangRect((*gift_it)->GetRect(), hp.GetRect())) {
						condition = gift_index + 1;

						delete (*gift_it);// ɾ����ָ��
						gift.erase(gift_it);// �߳�����
						gift_it = gift.begin();
						break;
					}
					// δ��ʰȡ���ߣ��Ѿ��ɳ���Ļ��
					if (!(*gift_it)->Show()) {
						delete (*gift_it);// ɾ����ָ��
						gift.erase(gift_it);// �߳�����
						gift_it = gift.begin();
					}
					else
						gift_it++;
				}

				/* ���Ͻ�ʵʱ��ʾ��ɱ���͵÷� */
				score = kill[0] * 3 + kill[1] * 5 + kill[2] * 1 + kill[3] * 7 + kill[4] * 31;
				PrintScore(kill, score);

				/* ����Ƿ���� */
				if (score >= SCORE_1) {
					flag = true;
					is_play = false;
				}

				EndBatchDraw();// BeginBatchDraw��EndBatchDraw��������Ƶ��				
			}

			stopBgmMusic();
			Over(kill, score, flag);// �������
			break;
		}

		// ����ģʽ������2��
		// ��ͨ�л������͵л�
		// score 500
		case 202: {
			/* �������� */
			BG bg = BG(bgimg2);// ����
			Hero hp = Hero(heroimg);// ��ҷɻ�
			vector<Enemy*> ep;// �л���������ͨ��
			vector<midEnemy*> mid_ep;// �л����������ͣ�
			vector<Bullet*> bs;// �ҷ��ӵ���������ͨ��
			vector<Bullet2_1*> bs2_1;// �ҷ��ӵ�������˫���ӵ����󣩣�
			vector<Bullet2_2*> bs2_2;// �ҷ��ӵ�������˫���ӵ����ң���
			vector<Bullet3_1*> bs3_1;// �ҷ��ӵ��������ֲ��ӵ����У���
			vector<Bullet3_2*> bs3_2;// �ҷ��ӵ��������ֲ��ӵ����󣩣�
			vector<Bullet3_3*> bs3_3;// �ҷ��ӵ��������ֲ��ӵ����ң���
			vector<Bullet4*> bs4;// �ҷ��ӵ����������׵���
			vector<EBullet*> ebs;// �з��ӵ���������ͨ��
			vector<EBullet*> mid_ebs;// �з��ӵ����������ͣ�
			vector<Gift*> gift;// ��������

			/* ����������� */
			int bsing = 0;// �����ҷ��ӵ�����Ƶ�ʣ���ͨ��
			int ebsing = 0;// ���Ƶз��ӵ�����Ƶ�ʣ���ͨ��
			int mid_ebsing = 0;// ���Ƶз��ӵ�����Ƶ�ʣ����ͣ�
			int density = DENSITY;// ���Ƶл��ܶȣ���ͨ��
			int mid_density = MID_DENSITY;// ���Ƶл��ܶȣ����ͣ�

			/* ��������� */
			int kill[5] = { 0, 0, 0, 0, 0 };// ��¼���ֻ�ɱ����:{��ͨ�����ͣ�С�ͣ����ͣ�BOSS}
			int score = 0;// ��¼�÷֣�{��ͨ��3�����ͣ�5��С�ͣ�1�����ͣ�7��BOSS��31}
			int kill_temp = 0;// ��¼��ǰɱ���������ﵽһ��ֵ����㣬����ȷ�����͵���ʱ����
			int bullets_total = 0;// ��¼�е����ڼ䷢���ӵ������������л�����״̬
			int condition = 0;// �����л�����״̬��Ĭ��Ϊ0
			int gift_index = 0;// ���ڼ�¼��������
			bool flag = false;// �ж��Ƿ����

			playBgmMusic();

			/* ��ӿ��ֵл� */
			for (int i = 0; i < density; i++) {
				AddEnemy(ep, enemyimg, eboom);
			}

			/* ������Ϸ�� */
			while (is_play) {
				/* ���ر�������ҷɻ� */
				BeginBatchDraw();// BeginBatchDraw��EndBatchDraw��������Ƶ�������飺https://docs.easyx.cn/zh-cn/other-func
				bg.Show();
				Sleep(4);
				flushmessage();
				Sleep(1);
				hp.Control();
				hp.Show();

				/* ���ո���ͣ */
				if (GetAsyncKeyState(VK_SPACE) & 0x0001)
					while (!(GetAsyncKeyState(VK_SPACE) & 0x0001));

				/* ��ӵз��ӵ� */
				ebsing++;
				if (ebsing == 101 - ebs_frequency) {
					ebsing = 0;
					for (auto& i : ep)
						ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// �з��ӵ�����ͨ��
				}
				mid_ebsing++;
				if (mid_ebsing == 101 - mid_ebs_frequency) {
					mid_ebsing = 0;
					for (auto& i : mid_ep)
						mid_ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// �з��ӵ������ͣ�
				}

				/* ��ӵл� */
				for (int i = 0; i < density - ep.size(); i++) {
					AddEnemy(ep, enemyimg, eboom);
				}
				for (int i = 0; i < mid_density - mid_ep.size(); i++) {
					AddEnemy(mid_ep, midEnemyimg, eboom);
				}

				/* ���صз��ӵ� */
				auto ebsit = ebs.begin();
				while (ebsit != ebs.end()) {
					// �ҷ��ɻ�������
					if (RectDuangRect((*ebsit)->GetRect(), hp.GetRect())) {
						/* ��� */
						is_play = hp.hurt();

						ebsit = ebs.erase(ebsit);
					}
					// ����ӵ��ɳ���Ļ��ȥ��
					else if (!(*ebsit)->Show())
						ebsit = ebs.erase(ebsit);
					else
						ebsit++;
				}
				auto mid_ebsit = mid_ebs.begin();
				while (mid_ebsit != mid_ebs.end()) {
					// �ҷ��ɻ�������
					if (RectDuangRect((*mid_ebsit)->GetRect(), hp.GetRect())) {
						/* ��� */
						is_play = hp.hurt();

						mid_ebsit = mid_ebs.erase(mid_ebsit);
					}
					// ����ӵ��ɳ���Ļ��ȥ��
					else if (!(*mid_ebsit)->Show())
						mid_ebsit = mid_ebs.erase(mid_ebsit);
					else
						mid_ebsit++;
				}

				/* ʰȡ���߽����Ӧ״̬ */
				switch (condition) {
					/* ����״̬ */
				case 0: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs.push_back(new Bullet(bulletimg, hp.GetRect()));// �ҷ��ӵ�����ͨ��
					}

					/* �����ҷ��ӵ� */
					auto bsit = bs.begin();
					while (bsit != bs.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit)->Show())
							bsit = bs.erase(bsit);
						else
							bsit++;
					}

					/* ���صз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
								kill_temp++;
							}

							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*it)->GetRect())) {
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
								kill_temp++;
							}

							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*mid_it)->GetRect())) {
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
								else
									(*mid_it)->Dies();

								delete (*bit);
								bs.erase(bit);

								break;
							}
							bit++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}

					break;// ����case
				}

					  /* ����1��������ֵ��һ���Ե��ߣ� */
				case 1: {
					hp.heal();

					condition = 0;// �ָ�����״̬

					break;// ����case
				}

					  /* ����2����յл��͵з��ӵ���һ���Ե��ߣ� */
				case 2: {
					/* ��յз��ӵ� */
					auto ebsit = ebs.begin();
					while (ebsit != ebs.end()) {
						ebsit = ebs.erase(ebsit);
					}
					auto mid_ebsit = mid_ebs.begin();
					while (mid_ebsit != mid_ebs.end()) {
						mid_ebsit = mid_ebs.erase(mid_ebsit);
					}

					/* ��յз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						if (!(*it)->dying()) {
							(*it)->Dies();
							kill[0]++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}

					condition = 0;// �ָ�����״̬

					break;// ����case
				}

					  /* ����3��˫���ӵ���һ��ʱ�䣩 */
				case 3: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs2_1.push_back(new Bullet2_1(bulletimg, hp.GetRect()));// �ҷ��ӵ���˫���ӵ����󣩣�
						bs2_2.push_back(new Bullet2_2(bulletimg, hp.GetRect()));// �ҷ��ӵ���˫���ӵ����ң���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit2_1 = bs2_1.begin();
					while (bsit2_1 != bs2_1.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit2_1)->Show())
							bsit2_1 = bs2_1.erase(bsit2_1);
						else
							bsit2_1++;
					}
					auto bsit2_2 = bs2_2.begin();
					while (bsit2_2 != bs2_2.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit2_2)->Show())
							bsit2_2 = bs2_2.erase(bsit2_2);
						else
							bsit2_2++;
					}

					/* ���صз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}

							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit2_2)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
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
							if (RectDuangRect((*bit2_2)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
								else
									(*mid_it)->Dies();

								delete (*bit2_2);
								bs2_2.erase(bit2_2);

								break;
							}
							bit2_2++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}

					break;// ����case
				}

					  /* ����4���ֲ��ӵ���һ��ʱ�䣩 */
				case 4: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs3_1.push_back(new Bullet3_1(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����У���
						bs3_2.push_back(new Bullet3_2(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����󣩣�
						bs3_3.push_back(new Bullet3_3(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����ң���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit3_1 = bs3_1.begin();
					while (bsit3_1 != bs3_1.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_1)->Show())
							bsit3_1 = bs3_1.erase(bsit3_1);
						else
							bsit3_1++;
					}
					auto bsit3_2 = bs3_2.begin();
					while (bsit3_2 != bs3_2.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_2)->Show())
							bsit3_2 = bs3_2.erase(bsit3_2);
						else
							bsit3_2++;
					}
					auto bsit3_3 = bs3_3.begin();
					while (bsit3_3 != bs3_3.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_3)->Show())
							bsit3_3 = bs3_3.erase(bsit3_3);
						else
							bsit3_3++;
					}

					/* ���صз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}


							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_2)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_3)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
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
							if (RectDuangRect((*bit3_2)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
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
							if (RectDuangRect((*bit3_3)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
								else
									(*mid_it)->Dies();

								delete (*bit3_3);
								bs3_3.erase(bit3_3);

								break;
							}
							bit3_3++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}

					break;// ����case
				}

					  /* ����5�������ӵ���һ��ʱ�䣩 */
				case 5: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs4.push_back(new Bullet4(bullet4img, hp.GetRect()));// �ҷ��ӵ������׵���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit4 = bs4.begin();
					while (bsit4 != bs4.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit4)->Show())
							bsit4 = bs4.erase(bsit4);
						else
							bsit4++;
					}

					/* ���صз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}

							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								break;
							}
							bit4++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
								else
									(*mid_it)->Dies();

								break;
							}
							bit4++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}

					break;// ����case
				}
				}

				/* ÿɱһ������������һ������ */
				if ((condition == 0) && (kill_temp >= KILL_FOR_GIFT)) {
					/* ������ŵ��ߣ�δ��ɣ� */
					gift_index = rand() % 5;
					AddGift(gift, giftimg[gift_index]);

					kill_temp = 0;
					bullets_total = 0;
				}
				/* ���ص��� */
				auto gift_it = gift.begin();
				while (gift_it != gift.end()) {
					// �ɹ�ʰȡ����
					if (RectDuangRect((*gift_it)->GetRect(), hp.GetRect())) {
						condition = gift_index + 1;

						delete (*gift_it);// ɾ����ָ��
						gift.erase(gift_it);// �߳�����
						gift_it = gift.begin();
						break;
					}
					// δ��ʰȡ���ߣ��Ѿ��ɳ���Ļ��
					if (!(*gift_it)->Show()) {
						delete (*gift_it);// ɾ����ָ��
						gift.erase(gift_it);// �߳�����
						gift_it = gift.begin();
					}
					else
						gift_it++;
				}

				/* ���Ͻ�ʵʱ��ʾ��ɱ���͵÷� */
				score = kill[0] * 3 + kill[1] * 5 + kill[2] * 1 + kill[3] * 7 + kill[4] * 31;
				PrintScore(kill, score);

				/* ����Ƿ���� */
				if (score >= SCORE_2) {
					flag = true;
					is_play = false;
				}

				EndBatchDraw();// BeginBatchDraw��EndBatchDraw��������Ƶ��				
			}

			stopBgmMusic();
			Over(kill, score, flag);// �������
			break;
		}

		// ����ģʽ������3��
		// ��ͨ�л������͵л���С�͵л�
		// score 700
		case 203: {
			/* �������� */
			BG bg = BG(bgimg3);// ����
			Hero hp = Hero(heroimg2);// ��ҷɻ�
			vector<Enemy*> ep;// �л���������ͨ��
			vector<midEnemy*> mid_ep;// �л����������ͣ�
			vector<miniEnemy*> mini_ep;// �л�������С�ͣ�
			vector<Bullet*> bs;// �ҷ��ӵ���������ͨ��
			vector<Bullet2_1*> bs2_1;// �ҷ��ӵ�������˫���ӵ����󣩣�
			vector<Bullet2_2*> bs2_2;// �ҷ��ӵ�������˫���ӵ����ң���
			vector<Bullet3_1*> bs3_1;// �ҷ��ӵ��������ֲ��ӵ����У���
			vector<Bullet3_2*> bs3_2;// �ҷ��ӵ��������ֲ��ӵ����󣩣�
			vector<Bullet3_3*> bs3_3;// �ҷ��ӵ��������ֲ��ӵ����ң���
			vector<Bullet4*> bs4;// �ҷ��ӵ����������׵���
			vector<EBullet*> ebs;// �з��ӵ���������ͨ��
			vector<EBullet*> mid_ebs;// �з��ӵ����������ͣ�
			vector<Gift*> gift;// ��������

			/* ����������� */
			int bsing = 0;// �����ҷ��ӵ�����Ƶ�ʣ���ͨ��
			int ebsing = 0;// ���Ƶз��ӵ�����Ƶ�ʣ���ͨ��
			int mid_ebsing = 0;// ���Ƶз��ӵ�����Ƶ�ʣ����ͣ�
			int density = DENSITY;// ���Ƶл��ܶȣ���ͨ��
			int mid_density = MID_DENSITY;// ���Ƶл��ܶȣ����ͣ�
			int mini_density = MINI_DENSITY;// ���Ƶл��ܶȣ�С�ͣ�

			/* ��������� */
			int kill[5] = { 0, 0, 0, 0, 0 };// ��¼���ֻ�ɱ����:{��ͨ�����ͣ�С�ͣ����ͣ�BOSS}
			int score = 0;// ��¼�÷֣�{��ͨ��3�����ͣ�5��С�ͣ�1�����ͣ�7��BOSS��31}
			int kill_temp = 0;// ��¼��ǰɱ���������ﵽһ��ֵ����㣬����ȷ�����͵���ʱ����
			int bullets_total = 0;// ��¼�е����ڼ䷢���ӵ������������л�����״̬
			int condition = 0;// �����л�����״̬��Ĭ��Ϊ0
			int gift_index = 0;// ���ڼ�¼��������
			bool flag = false;// �ж��Ƿ����

			/* ��¼ʱ�� */
			DWORD startTime = timeGetTime();// ��ȡ��ʼʱ��
			int mini_time = 4000;// С�͵л�ˢ��ʱ��

			playBgmMusic();

			/* ��ӿ��ֵл� */
			for (int i = 0; i < density; i++) {
				AddEnemy(ep, enemyimg, eboom);
			}

			/* ������Ϸ�� */
			while (is_play) {
				/* ���ر�������ҷɻ� */
				BeginBatchDraw();// BeginBatchDraw��EndBatchDraw��������Ƶ�������飺https://docs.easyx.cn/zh-cn/other-func
				bg.Show();
				Sleep(4);
				flushmessage();
				Sleep(1);
				hp.Control();
				hp.Show();

				/* ���ո���ͣ */
				if (GetAsyncKeyState(VK_SPACE) & 0x0001)
					while (!(GetAsyncKeyState(VK_SPACE) & 0x0001));

				/* ��ӵз��ӵ� */
				ebsing++;
				if (ebsing == 101 - ebs_frequency) {
					ebsing = 0;
					for (auto& i : ep)
						ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// �з��ӵ�����ͨ��
				}
				mid_ebsing++;
				if (mid_ebsing == 101 - mid_ebs_frequency) {
					mid_ebsing = 0;
					for (auto& i : mid_ep)
						mid_ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// �з��ӵ������ͣ�
				}

				/* ��ӵл� */
				for (int i = 0; i < density - ep.size(); i++) {
					AddEnemy(ep, enemyimg, eboom);
				}
				for (int i = 0; i < mid_density - mid_ep.size(); i++) {
					AddEnemy(mid_ep, midEnemyimg, eboom);
				}
				DWORD currentTime = timeGetTime(); // ��ȡ��ǰʱ��
				DWORD elapsedTime = currentTime - startTime; // ���㾭����ʱ��
				if (static_cast<int>(elapsedTime) >= mini_time) {
					int x = rand() % 3;
					for (int i = 0; i < mini_density; i++) {// ����л�
						AddEnemy(mini_ep, miniEnemyimg, eboom, x);
					}
					startTime = currentTime;
				}

				/* ���صз��ӵ� */
				auto ebsit = ebs.begin();
				while (ebsit != ebs.end()) {
					// �ҷ��ɻ�������
					if (RectDuangRect((*ebsit)->GetRect(), hp.GetRect())) {
						/* ��� */
						is_play = hp.hurt();

						ebsit = ebs.erase(ebsit);
					}
					// ����ӵ��ɳ���Ļ��ȥ��
					else if (!(*ebsit)->Show())
						ebsit = ebs.erase(ebsit);
					else
						ebsit++;
				}
				auto mid_ebsit = mid_ebs.begin();
				while (mid_ebsit != mid_ebs.end()) {
					// �ҷ��ɻ�������
					if (RectDuangRect((*mid_ebsit)->GetRect(), hp.GetRect())) {
						/* ��� */
						is_play = hp.hurt();

						mid_ebsit = mid_ebs.erase(mid_ebsit);
					}
					// ����ӵ��ɳ���Ļ��ȥ��
					else if (!(*mid_ebsit)->Show())
						mid_ebsit = mid_ebs.erase(mid_ebsit);
					else
						mid_ebsit++;
				}

				/* ʰȡ���߽����Ӧ״̬ */
				switch (condition) {
					/* ����״̬ */
				case 0: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs.push_back(new Bullet(bulletimg, hp.GetRect()));// �ҷ��ӵ�����ͨ��
					}

					/* �����ҷ��ӵ� */
					auto bsit = bs.begin();
					while (bsit != bs.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit)->Show())
							bsit = bs.erase(bsit);
						else
							bsit++;
					}

					/* ���صз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
								kill_temp++;
							}

							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*it)->GetRect())) {
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
								kill_temp++;
							}

							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*mid_it)->GetRect())) {
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
								else
									(*mid_it)->Dies();

								delete (*bit);
								bs.erase(bit);

								break;
							}
							bit++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
								kill_temp++;
							}

							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*mini_it)->GetRect())) {
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}

					break;// ����case
				}

					  /* ����1��������ֵ��һ���Ե��ߣ� */
				case 1: {
					hp.heal();

					condition = 0;// �ָ�����״̬

					break;// ����case
				}

					  /* ����2����յл��͵з��ӵ���һ���Ե��ߣ� */
				case 2: {
					/* ��յз��ӵ� */
					auto ebsit = ebs.begin();
					while (ebsit != ebs.end()) {
						ebsit = ebs.erase(ebsit);
					}
					auto mid_ebsit = mid_ebs.begin();
					while (mid_ebsit != mid_ebs.end()) {
						mid_ebsit = mid_ebs.erase(mid_ebsit);
					}

					/* ��յз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						if (!(*it)->dying()) {
							(*it)->Dies();
							kill[0]++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}

					condition = 0;// �ָ�����״̬

					break;// ����case
				}

					  /* ����3��˫���ӵ���һ��ʱ�䣩 */
				case 3: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs2_1.push_back(new Bullet2_1(bulletimg, hp.GetRect()));// �ҷ��ӵ���˫���ӵ����󣩣�
						bs2_2.push_back(new Bullet2_2(bulletimg, hp.GetRect()));// �ҷ��ӵ���˫���ӵ����ң���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit2_1 = bs2_1.begin();
					while (bsit2_1 != bs2_1.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit2_1)->Show())
							bsit2_1 = bs2_1.erase(bsit2_1);
						else
							bsit2_1++;
					}
					auto bsit2_2 = bs2_2.begin();
					while (bsit2_2 != bs2_2.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit2_2)->Show())
							bsit2_2 = bs2_2.erase(bsit2_2);
						else
							bsit2_2++;
					}

					/* ���صз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}

							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit2_2)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
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
							if (RectDuangRect((*bit2_2)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
								else
									(*mid_it)->Dies();

								delete (*bit2_2);
								bs2_2.erase(bit2_2);

								break;
							}
							bit2_2++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
							}

							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*mini_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit2_2)->GetRect(), (*mini_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}

					break;// ����case
				}

					  /* ����4���ֲ��ӵ���һ��ʱ�䣩 */
				case 4: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs3_1.push_back(new Bullet3_1(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����У���
						bs3_2.push_back(new Bullet3_2(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����󣩣�
						bs3_3.push_back(new Bullet3_3(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����ң���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit3_1 = bs3_1.begin();
					while (bsit3_1 != bs3_1.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_1)->Show())
							bsit3_1 = bs3_1.erase(bsit3_1);
						else
							bsit3_1++;
					}
					auto bsit3_2 = bs3_2.begin();
					while (bsit3_2 != bs3_2.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_2)->Show())
							bsit3_2 = bs3_2.erase(bsit3_2);
						else
							bsit3_2++;
					}
					auto bsit3_3 = bs3_3.begin();
					while (bsit3_3 != bs3_3.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_3)->Show())
							bsit3_3 = bs3_3.erase(bsit3_3);
						else
							bsit3_3++;
					}

					/* ���صз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}


							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_2)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_3)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
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
							if (RectDuangRect((*bit3_2)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
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
							if (RectDuangRect((*bit3_3)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
								else
									(*mid_it)->Dies();

								delete (*bit3_3);
								bs3_3.erase(bit3_3);

								break;
							}
							bit3_3++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
							}

							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*mini_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_2)->GetRect(), (*mini_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_3)->GetRect(), (*mini_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}

					break;// ����case
				}

					  /* ����5�������ӵ���һ��ʱ�䣩 */
				case 5: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs4.push_back(new Bullet4(bullet4img, hp.GetRect()));// �ҷ��ӵ������׵���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit4 = bs4.begin();
					while (bsit4 != bs4.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit4)->Show())
							bsit4 = bs4.erase(bsit4);
						else
							bsit4++;
					}

					/* ���صз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}

							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								break;
							}
							bit4++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
								else
									(*mid_it)->Dies();

								break;
							}
							bit4++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
							}

							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*mini_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								break;
							}
							bit4++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}

					break;// ����case
				}
				}

				/* ÿɱһ������������һ������ */
				if ((condition == 0) && (kill_temp >= KILL_FOR_GIFT)) {
					/* ������ŵ��ߣ�δ��ɣ� */
					gift_index = rand() % 5;
					AddGift(gift, giftimg[gift_index]);

					kill_temp = 0;
					bullets_total = 0;
				}
				/* ���ص��� */
				auto gift_it = gift.begin();
				while (gift_it != gift.end()) {
					// �ɹ�ʰȡ����
					if (RectDuangRect((*gift_it)->GetRect(), hp.GetRect())) {
						condition = gift_index + 1;

						delete (*gift_it);// ɾ����ָ��
						gift.erase(gift_it);// �߳�����
						gift_it = gift.begin();
						break;
					}
					// δ��ʰȡ���ߣ��Ѿ��ɳ���Ļ��
					if (!(*gift_it)->Show()) {
						delete (*gift_it);// ɾ����ָ��
						gift.erase(gift_it);// �߳�����
						gift_it = gift.begin();
					}
					else
						gift_it++;
				}

				/* ���Ͻ�ʵʱ��ʾ��ɱ���͵÷� */
				score = kill[0] * 3 + kill[1] * 5 + kill[2] * 1 + kill[3] * 7 + kill[4] * 31;
				PrintScore(kill, score);

				/* ����Ƿ���� */
				if (score >= SCORE_3) {
					flag = true;
					is_play = false;
				}

				EndBatchDraw();// BeginBatchDraw��EndBatchDraw��������Ƶ��				
			}

			stopBgmMusic();
			Over(kill, score, flag);// �������
			break;
		}

		// ����ģʽ������4��
		// ��ͨ�л������͵л���С�͵л������͵л�
		// score 1300
		case 204: {
			/* �������� */
			BG bg = BG(bgimg4);// ����
			Hero hp = Hero(heroimg2);// ��ҷɻ�
			vector<Enemy*> ep;// �л���������ͨ��
			vector<midEnemy*> mid_ep;// �л����������ͣ�
			vector<miniEnemy*> mini_ep;// �л�������С�ͣ�
			vector<giantEnemy*> giant_ep;// �л����������ͣ�
			vector<Bullet*> bs;// �ҷ��ӵ���������ͨ��
			vector<Bullet2_1*> bs2_1;// �ҷ��ӵ�������˫���ӵ����󣩣�
			vector<Bullet2_2*> bs2_2;// �ҷ��ӵ�������˫���ӵ����ң���
			vector<Bullet3_1*> bs3_1;// �ҷ��ӵ��������ֲ��ӵ����У���
			vector<Bullet3_2*> bs3_2;// �ҷ��ӵ��������ֲ��ӵ����󣩣�
			vector<Bullet3_3*> bs3_3;// �ҷ��ӵ��������ֲ��ӵ����ң���
			vector<Bullet4*> bs4;// �ҷ��ӵ����������׵���
			vector<EBullet*> ebs;// �з��ӵ���������ͨ��
			vector<EBullet*> mid_ebs;// �з��ӵ����������ͣ�
			vector<EBullet*> giant_ebs;// �з��ӵ����������ͣ�
			vector<Gift*> gift;// ��������

			/* ����������� */
			int bsing = 0;// �����ҷ��ӵ�����Ƶ�ʣ���ͨ��
			int ebsing = 0;// ���Ƶз��ӵ�����Ƶ�ʣ���ͨ��
			int mid_ebsing = 0;// ���Ƶз��ӵ�����Ƶ�ʣ����ͣ�
			int giant_ebsing = 0;// ���Ƶз��ӵ�����Ƶ�ʣ����ͣ�
			int density = DENSITY;// ���Ƶл��ܶȣ���ͨ��
			int mid_density = MID_DENSITY;// ���Ƶл��ܶȣ����ͣ�
			int mini_density = MINI_DENSITY;// ���Ƶл��ܶȣ�С�ͣ�
			int giant_density = GIANT_DENSITY;// ���Ƶл��ܶȣ����ͣ�

			/* ��������� */
			int kill[5] = { 0, 0, 0, 0, 0 };// ��¼���ֻ�ɱ����:{��ͨ�����ͣ�С�ͣ����ͣ�BOSS}
			int score = 0;// ��¼�÷֣�{��ͨ��3�����ͣ�5��С�ͣ�1�����ͣ�7��BOSS��31}
			int kill_temp = 0;// ��¼��ǰɱ���������ﵽһ��ֵ����㣬����ȷ�����͵���ʱ����
			int bullets_total = 0;// ��¼�е����ڼ䷢���ӵ������������л�����״̬
			int condition = 0;// �����л�����״̬��Ĭ��Ϊ0
			int gift_index = 0;// ���ڼ�¼��������
			bool flag = false;// �ж��Ƿ����

			/* ��¼ʱ�� */
			DWORD startTime = timeGetTime();// ��ȡ��ʼʱ��
			int mini_time = 4000;// С�͵л�ˢ��ʱ��

			playBgmMusic();

			/* ��ӿ��ֵл� */
			for (int i = 0; i < density; i++) {
				AddEnemy(ep, enemyimg, eboom);
			}

			/* ������Ϸ�� */
			while (is_play) {
				/* ���ر�������ҷɻ� */
				BeginBatchDraw();// BeginBatchDraw��EndBatchDraw��������Ƶ�������飺https://docs.easyx.cn/zh-cn/other-func
				bg.Show();
				Sleep(4);
				flushmessage();
				Sleep(1);
				hp.Control();
				hp.Show();

				/* ���ո���ͣ */
				if (GetAsyncKeyState(VK_SPACE) & 0x0001)
					while (!(GetAsyncKeyState(VK_SPACE) & 0x0001));

				/* ��ӵз��ӵ� */
				ebsing++;
				if (ebsing == 101 - ebs_frequency) {
					ebsing = 0;
					for (auto& i : ep)
						ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// �з��ӵ�����ͨ��
				}
				mid_ebsing++;
				if (mid_ebsing == 101 - mid_ebs_frequency) {
					mid_ebsing = 0;
					for (auto& i : mid_ep)
						mid_ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// �з��ӵ������ͣ�
				}
				giant_ebsing++;
				if (giant_ebsing == 101 - giant_ebs_frequency) {
					giant_ebsing = 0;
					for (auto& i : giant_ep)
						giant_ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// �з��ӵ������ͣ�
				}

				/* ��ӵл� */
				for (int i = 0; i < density - ep.size(); i++) {
					AddEnemy(ep, enemyimg, eboom);
				}
				for (int i = 0; i < mid_density - mid_ep.size(); i++) {
					AddEnemy(mid_ep, midEnemyimg, eboom);
				}
				DWORD currentTime = timeGetTime(); // ��ȡ��ǰʱ��
				DWORD elapsedTime = currentTime - startTime; // ���㾭����ʱ��
				if (static_cast<int>(elapsedTime) >= mini_time) {
					int x = rand() % 3;
					for (int i = 0; i < mini_density; i++) {// ����л�
						AddEnemy(mini_ep, miniEnemyimg, eboom, x);
					}
					startTime = currentTime;
				}
				for (int i = 0; i < giant_density - giant_ep.size(); i++) {
					AddEnemy(giant_ep, giantEnemyimg, eboom);
				}

				/* ���صз��ӵ� */
				auto ebsit = ebs.begin();
				while (ebsit != ebs.end()) {
					// �ҷ��ɻ�������
					if (RectDuangRect((*ebsit)->GetRect(), hp.GetRect())) {
						/* ��� */
						is_play = hp.hurt();

						ebsit = ebs.erase(ebsit);
					}
					// ����ӵ��ɳ���Ļ��ȥ��
					else if (!(*ebsit)->Show())
						ebsit = ebs.erase(ebsit);
					else
						ebsit++;
				}
				auto mid_ebsit = mid_ebs.begin();
				while (mid_ebsit != mid_ebs.end()) {
					// �ҷ��ɻ�������
					if (RectDuangRect((*mid_ebsit)->GetRect(), hp.GetRect())) {
						/* ��� */
						is_play = hp.hurt();

						mid_ebsit = mid_ebs.erase(mid_ebsit);
					}
					// ����ӵ��ɳ���Ļ��ȥ��
					else if (!(*mid_ebsit)->Show())
						mid_ebsit = mid_ebs.erase(mid_ebsit);
					else
						mid_ebsit++;
				}
				auto giant_ebsit = giant_ebs.begin();
				while (giant_ebsit != giant_ebs.end()) {
					// �ҷ��ɻ�������
					if (RectDuangRect((*giant_ebsit)->GetRect(), hp.GetRect())) {
						/* ��� */
						is_play = hp.hurt();

						giant_ebsit = giant_ebs.erase(giant_ebsit);
					}
					// ����ӵ��ɳ���Ļ��ȥ��
					else if (!(*giant_ebsit)->Show())
						giant_ebsit = giant_ebs.erase(giant_ebsit);
					else
						giant_ebsit++;
				}

				/* ʰȡ���߽����Ӧ״̬ */
				switch (condition) {
					/* ����״̬ */
				case 0: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs.push_back(new Bullet(bulletimg, hp.GetRect()));// �ҷ��ӵ�����ͨ��
					}

					/* �����ҷ��ӵ� */
					auto bsit = bs.begin();
					while (bsit != bs.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit)->Show())
							bsit = bs.erase(bsit);
						else
							bsit++;
					}

					/* ���صз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
								kill_temp++;
							}

							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*it)->GetRect())) {
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
								kill_temp++;
							}

							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*mid_it)->GetRect())) {
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
								else
									(*mid_it)->Dies();

								delete (*bit);
								bs.erase(bit);

								break;
							}
							bit++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
								kill_temp++;
							}

							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*mini_it)->GetRect())) {
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*giant_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*giant_it)->dying()) {
								(*giant_it)->Dies();
								kill[3]++;
								kill_temp++;
							}

							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*giant_it)->GetRect())) {
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}

					break;// ����case
				}

					  /* ����1��������ֵ��һ���Ե��ߣ� */
				case 1: {
					hp.heal();

					condition = 0;// �ָ�����״̬

					break;// ����case
				}

					  /* ����2����յл��͵з��ӵ���һ���Ե��ߣ� */
				case 2: {
					/* ��յз��ӵ� */
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

					/* ��յз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						if (!(*it)->dying()) {
							(*it)->Dies();
							kill[0]++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}

					condition = 0;// �ָ�����״̬

					break;// ����case
				}

					  /* ����3��˫���ӵ���һ��ʱ�䣩 */
				case 3: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs2_1.push_back(new Bullet2_1(bulletimg, hp.GetRect()));// �ҷ��ӵ���˫���ӵ����󣩣�
						bs2_2.push_back(new Bullet2_2(bulletimg, hp.GetRect()));// �ҷ��ӵ���˫���ӵ����ң���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit2_1 = bs2_1.begin();
					while (bsit2_1 != bs2_1.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit2_1)->Show())
							bsit2_1 = bs2_1.erase(bsit2_1);
						else
							bsit2_1++;
					}
					auto bsit2_2 = bs2_2.begin();
					while (bsit2_2 != bs2_2.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit2_2)->Show())
							bsit2_2 = bs2_2.erase(bsit2_2);
						else
							bsit2_2++;
					}

					/* ���صз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}

							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit2_2)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
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
							if (RectDuangRect((*bit2_2)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
								else
									(*mid_it)->Dies();

								delete (*bit2_2);
								bs2_2.erase(bit2_2);

								break;
							}
							bit2_2++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
							}

							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*mini_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit2_2)->GetRect(), (*mini_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*giant_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*giant_it)->dying()) {
								(*giant_it)->Dies();
								kill[3]++;
							}

							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*giant_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit2_2)->GetRect(), (*giant_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}

					break;// ����case
				}

					  /* ����4���ֲ��ӵ���һ��ʱ�䣩 */
				case 4: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs3_1.push_back(new Bullet3_1(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����У���
						bs3_2.push_back(new Bullet3_2(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����󣩣�
						bs3_3.push_back(new Bullet3_3(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����ң���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit3_1 = bs3_1.begin();
					while (bsit3_1 != bs3_1.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_1)->Show())
							bsit3_1 = bs3_1.erase(bsit3_1);
						else
							bsit3_1++;
					}
					auto bsit3_2 = bs3_2.begin();
					while (bsit3_2 != bs3_2.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_2)->Show())
							bsit3_2 = bs3_2.erase(bsit3_2);
						else
							bsit3_2++;
					}
					auto bsit3_3 = bs3_3.begin();
					while (bsit3_3 != bs3_3.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_3)->Show())
							bsit3_3 = bs3_3.erase(bsit3_3);
						else
							bsit3_3++;
					}

					/* ���صз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}


							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_2)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_3)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
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
							if (RectDuangRect((*bit3_2)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
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
							if (RectDuangRect((*bit3_3)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
								else
									(*mid_it)->Dies();

								delete (*bit3_3);
								bs3_3.erase(bit3_3);

								break;
							}
							bit3_3++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
							}

							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*mini_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_2)->GetRect(), (*mini_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_3)->GetRect(), (*mini_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*giant_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*giant_it)->dying()) {
								(*giant_it)->Dies();
								kill[3]++;
							}

							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*giant_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_2)->GetRect(), (*giant_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_3)->GetRect(), (*giant_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}

					break;// ����case
				}

					  /* ����5�������ӵ���һ��ʱ�䣩 */
				case 5: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs4.push_back(new Bullet4(bullet4img, hp.GetRect()));// �ҷ��ӵ������׵���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit4 = bs4.begin();
					while (bsit4 != bs4.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit4)->Show())
							bsit4 = bs4.erase(bsit4);
						else
							bsit4++;
					}

					/* ���صз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}

							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								break;
							}
							bit4++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
								else
									(*mid_it)->Dies();

								break;
							}
							bit4++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
							}

							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*mini_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								break;
							}
							bit4++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*giant_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*giant_it)->dying()) {
								(*giant_it)->Dies();
								kill[3]++;
							}

							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*giant_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								if ((*giant_it)->hurt()) {
									kill[3]++;
									kill_temp++;
								}

								break;
							}
							bit4++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}

					break;// ����case
				}
				}

				/* ÿɱһ������������һ������ */
				if ((condition == 0) && (kill_temp >= KILL_FOR_GIFT)) {
					/* ������ŵ��ߣ�δ��ɣ� */
					gift_index = rand() % 5;
					AddGift(gift, giftimg[gift_index]);

					kill_temp = 0;
					bullets_total = 0;
				}
				/* ���ص��� */
				auto gift_it = gift.begin();
				while (gift_it != gift.end()) {
					// �ɹ�ʰȡ����
					if (RectDuangRect((*gift_it)->GetRect(), hp.GetRect())) {
						condition = gift_index + 1;

						delete (*gift_it);// ɾ����ָ��
						gift.erase(gift_it);// �߳�����
						gift_it = gift.begin();
						break;
					}
					// δ��ʰȡ���ߣ��Ѿ��ɳ���Ļ��
					if (!(*gift_it)->Show()) {
						delete (*gift_it);// ɾ����ָ��
						gift.erase(gift_it);// �߳�����
						gift_it = gift.begin();
					}
					else
						gift_it++;
				}

				/* ���Ͻ�ʵʱ��ʾ��ɱ���͵÷� */
				score = kill[0] * 3 + kill[1] * 5 + kill[2] * 1 + kill[3] * 7 + kill[4] * 31;
				PrintScore(kill, score);

				/* ����Ƿ���� */
				if (score >= SCORE_4) {
					flag = true;
					is_play = false;
				}

				EndBatchDraw();// BeginBatchDraw��EndBatchDraw��������Ƶ��				
			}

			stopBgmMusic();
			Over(kill, score, flag);// �������
			break;
		}

		// ����ģʽ������5��
		// ��ͨ�л������͵л���С�͵л������͵л���BOSS
		// score 1300
		case 205: {
			/* �������� */
			BG bg = BG(bgimg5);// ����
			Hero hp = Hero(heroimg2);// ��ҷɻ�
			vector<Enemy*> ep;// �л���������ͨ��
			vector<midEnemy*> mid_ep;// �л����������ͣ�
			vector<miniEnemy*> mini_ep;// �л�������С�ͣ�
			vector<giantEnemy*> giant_ep;// �л����������ͣ�
			vector<bossEnemy*> boss_ep;// �л�������BOSS��
			vector<Bullet*> bs;// �ҷ��ӵ���������ͨ��
			vector<Bullet2_1*> bs2_1;// �ҷ��ӵ�������˫���ӵ����󣩣�
			vector<Bullet2_2*> bs2_2;// �ҷ��ӵ�������˫���ӵ����ң���
			vector<Bullet3_1*> bs3_1;// �ҷ��ӵ��������ֲ��ӵ����У���
			vector<Bullet3_2*> bs3_2;// �ҷ��ӵ��������ֲ��ӵ����󣩣�
			vector<Bullet3_3*> bs3_3;// �ҷ��ӵ��������ֲ��ӵ����ң���
			vector<Bullet4*> bs4;// �ҷ��ӵ����������׵���
			vector<EBullet*> ebs;// �з��ӵ���������ͨ��
			vector<EBullet*> mid_ebs;// �з��ӵ����������ͣ�
			vector<EBullet*> giant_ebs;// �з��ӵ����������ͣ�
			vector<BossSkill_1*> boss_skill_1;// BOSS�ӵ�������skill_1��
			vector<BossSkill_2*> boss_skill_2;// BOSS�ӵ�������skill_2��
			vector<BossSkill_3*> boss_skill_3;// BOSS�ӵ�������skill_3��
			vector<Gift*> gift;// ��������

			/* ����������� */
			int bsing = 0;// �����ҷ��ӵ�����Ƶ�ʣ���ͨ��
			int ebsing = 0;// ���Ƶз��ӵ�����Ƶ�ʣ���ͨ��
			int mid_ebsing = 0;// ���Ƶз��ӵ�����Ƶ�ʣ����ͣ�
			int giant_ebsing = 0;// ���Ƶз��ӵ�����Ƶ�ʣ����ͣ�
			int boss_ebsing = 0;// ���Ƶз��ӵ�����Ƶ�ʣ�BOSS��
			int density = DENSITY;// ���Ƶл��ܶȣ���ͨ��
			int mid_density = MID_DENSITY;// ���Ƶл��ܶȣ����ͣ�
			int mini_density = MINI_DENSITY;// ���Ƶл��ܶȣ�С�ͣ�
			int giant_density = GIANT_DENSITY;// ���Ƶл��ܶȣ����ͣ�
			int boss_density = BOSS_DENSITY;// ���Ƶл��ܶȣ�BOSS��

			/* ��������� */
			int kill[5] = { 0, 0, 0, 0, 0 };// ��¼���ֻ�ɱ����:{��ͨ�����ͣ�С�ͣ����ͣ�BOSS}
			int score = 0;// ��¼�÷֣�{��ͨ��3�����ͣ�5��С�ͣ�1�����ͣ�7��BOSS��31}
			int kill_temp = 0;// ��¼��ǰɱ���������ﵽһ��ֵ����㣬����ȷ�����͵���ʱ����
			int bullets_total = 0;// ��¼�е����ڼ䷢���ӵ������������л�����״̬
			int condition = 0;// �����л�����״̬��Ĭ��Ϊ0
			int gift_index = 0;// ���ڼ�¼��������
			bool flag = false;// �ж��Ƿ����

			/* ��¼ʱ�� */
			DWORD startTime = timeGetTime();// ��ȡ��ʼʱ��
			int mini_time = 4000;// С�͵л�ˢ��ʱ��

			playBgmMusic();

			/* ��ӿ��ֵл� */
			for (int i = 0; i < density; i++) {
				AddEnemy(ep, enemyimg, eboom);
			}

			/* ������Ϸ�� */
			while (is_play) {
				/* ���ر�������ҷɻ� */
				BeginBatchDraw();// BeginBatchDraw��EndBatchDraw��������Ƶ�������飺https://docs.easyx.cn/zh-cn/other-func
				bg.Show();
				Sleep(4);
				flushmessage();
				Sleep(1);
				hp.Control();
				hp.Show();

				/* ���ո���ͣ */
				if (GetAsyncKeyState(VK_SPACE) & 0x0001)
					while (!(GetAsyncKeyState(VK_SPACE) & 0x0001));

				/* ��ӵз��ӵ� */
				ebsing++;
				if (ebsing == 101 - ebs_frequency) {
					ebsing = 0;
					for (auto& i : ep)
						ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// �з��ӵ�����ͨ��
				}
				mid_ebsing++;
				if (mid_ebsing == 101 - mid_ebs_frequency) {
					mid_ebsing = 0;
					for (auto& i : mid_ep)
						mid_ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// �з��ӵ������ͣ�
				}
				giant_ebsing++;
				if (giant_ebsing == 101 - giant_ebs_frequency) {
					giant_ebsing = 0;
					for (auto& i : giant_ep)
						giant_ebs.push_back(new EBullet(ebulletimg, i->GetRect()));// �з��ӵ������ͣ�
				}
				boss_ebsing++;
				if (boss_ebsing == 101 - boss_ebs_frequency) {
					boss_ebsing = 0;
					for (auto& i : boss_ep) {
						// boss_skill_1������ʣ�50%
						if (rand() % 2 != 0)
							boss_skill_1.push_back(new BossSkill_1(bossSkill_1img, i->GetRect()));
						// boss_skill_2������ʣ�100%
						boss_skill_2.push_back(new BossSkill_2(bossSkill_2img, i->GetRect()));
						// boss_skill_3������ʣ�25%
						if (rand() % 4 == 0)
							boss_skill_3.push_back(new BossSkill_3(bossSkill_3img, i->GetRect()));
					}
				}

				/* ��ӵл� */
				if (score < SCORE_4) {
					for (int i = 0; i < density - ep.size(); i++) {
						AddEnemy(ep, enemyimg, eboom);
					}
					for (int i = 0; i < mid_density - mid_ep.size(); i++) {
						AddEnemy(mid_ep, midEnemyimg, eboom);
					}
					DWORD currentTime = timeGetTime(); // ��ȡ��ǰʱ��
					DWORD elapsedTime = currentTime - startTime; // ���㾭����ʱ��
					if (static_cast<int>(elapsedTime) >= mini_time) {
						int x = rand() % 3;
						for (int i = 0; i < mini_density; i++) {// ����л�
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

				/* ���صз��ӵ� */
				auto ebsit = ebs.begin();
				while (ebsit != ebs.end()) {
					// �ҷ��ɻ�������
					if (RectDuangRect((*ebsit)->GetRect(), hp.GetRect())) {
						/* ��� */
						is_play = hp.hurt();

						ebsit = ebs.erase(ebsit);
					}
					// ����ӵ��ɳ���Ļ��ȥ��
					else if (!(*ebsit)->Show())
						ebsit = ebs.erase(ebsit);
					else
						ebsit++;
				}
				auto mid_ebsit = mid_ebs.begin();
				while (mid_ebsit != mid_ebs.end()) {
					// �ҷ��ɻ�������
					if (RectDuangRect((*mid_ebsit)->GetRect(), hp.GetRect())) {
						/* ��� */
						is_play = hp.hurt();

						mid_ebsit = mid_ebs.erase(mid_ebsit);
					}
					// ����ӵ��ɳ���Ļ��ȥ��
					else if (!(*mid_ebsit)->Show())
						mid_ebsit = mid_ebs.erase(mid_ebsit);
					else
						mid_ebsit++;
				}
				auto giant_ebsit = giant_ebs.begin();
				while (giant_ebsit != giant_ebs.end()) {
					// �ҷ��ɻ�������
					if (RectDuangRect((*giant_ebsit)->GetRect(), hp.GetRect())) {
						/* ��� */
						is_play = hp.hurt();

						giant_ebsit = giant_ebs.erase(giant_ebsit);
					}
					// ����ӵ��ɳ���Ļ��ȥ��
					else if (!(*giant_ebsit)->Show())
						giant_ebsit = giant_ebs.erase(giant_ebsit);
					else
						giant_ebsit++;
				}
				auto boss_skill_1it = boss_skill_1.begin();
				while (boss_skill_1it != boss_skill_1.end()) {
					// �ҷ��ɻ�������
					if (RectDuangRect((*boss_skill_1it)->GetRect(), hp.GetRect())) {
						/* ��� */
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
					// �ҷ��ɻ�������
					if (RectDuangRect((*boss_skill_2it)->GetRect(), hp.GetRect())) {
						/* ��� */
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
					// �ҷ��ɻ�������
					if (RectDuangRect((*boss_skill_3it)->GetRect(), hp.GetRect())) {
						/* ��� */
						is_play = hp.hurt(HP);

						boss_skill_3it = boss_skill_3.erase(boss_skill_3it);
					}
					else if (!(*boss_skill_3it)->Show())
						boss_skill_3it = boss_skill_3.erase(boss_skill_3it);
					else
						boss_skill_3it++;
				}

				/* ʰȡ���߽����Ӧ״̬ */
				switch (condition) {
					/* ����״̬ */
				case 0: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs.push_back(new Bullet(bulletimg, hp.GetRect()));// �ҷ��ӵ�����ͨ��
					}

					/* �����ҷ��ӵ� */
					auto bsit = bs.begin();
					while (bsit != bs.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit)->Show())
							bsit = bs.erase(bsit);
						else
							bsit++;
					}

					/* ���صз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
								kill_temp++;
							}

							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*it)->GetRect())) {
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
								kill_temp++;
							}

							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*mid_it)->GetRect())) {
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
								else
									(*mid_it)->Dies();

								delete (*bit);
								bs.erase(bit);

								break;
							}
							bit++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
								kill_temp++;
							}

							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*mini_it)->GetRect())) {
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*giant_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*giant_it)->dying()) {
								(*giant_it)->Dies();
								kill[3]++;
								kill_temp++;
							}

							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*giant_it)->GetRect())) {
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}
					auto boss_it = boss_ep.begin();
					while (boss_it != boss_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*boss_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt(HP);

							break;
						}

						/* ����ҷ��ӵ����ел� */
						auto bit = bs.begin();
						while (bit != bs.end()) {
							if (RectDuangRect((*bit)->GetRect(), (*boss_it)->GetRect())) {
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*boss_it)->Show()) {
							delete (*boss_it);// ɾ����ָ��
							boss_ep.erase(boss_it);// �߳�����
							boss_it = boss_ep.begin();
						}
						else
							boss_it++;
					}

					break;// ����case
				}

					  /* ����1��������ֵ��һ���Ե��ߣ� */
				case 1: {
					hp.heal();

					condition = 0;// �ָ�����״̬

					break;// ����case
				}

					  /* ����2����յл��͵з��ӵ���һ���Ե��ߣ� */
				case 2: {
					/* ��յз��ӵ� */
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

					/* ��յз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						if (!(*it)->dying()) {
							(*it)->Dies();
							kill[0]++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*boss_it)->Show()) {
							delete (*boss_it);// ɾ����ָ��
							boss_ep.erase(boss_it);// �߳�����
							boss_it = boss_ep.begin();
						}
						else
							boss_it++;
					}

					condition = 0;// �ָ�����״̬

					break;// ����case
				}

					  /* ����3��˫���ӵ���һ��ʱ�䣩 */
				case 3: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs2_1.push_back(new Bullet2_1(bulletimg, hp.GetRect()));// �ҷ��ӵ���˫���ӵ����󣩣�
						bs2_2.push_back(new Bullet2_2(bulletimg, hp.GetRect()));// �ҷ��ӵ���˫���ӵ����ң���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit2_1 = bs2_1.begin();
					while (bsit2_1 != bs2_1.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit2_1)->Show())
							bsit2_1 = bs2_1.erase(bsit2_1);
						else
							bsit2_1++;
					}
					auto bsit2_2 = bs2_2.begin();
					while (bsit2_2 != bs2_2.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit2_2)->Show())
							bsit2_2 = bs2_2.erase(bsit2_2);
						else
							bsit2_2++;
					}

					/* ���صз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}

							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit2_2)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
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
							if (RectDuangRect((*bit2_2)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
								else
									(*mid_it)->Dies();

								delete (*bit2_2);
								bs2_2.erase(bit2_2);

								break;
							}
							bit2_2++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
							}

							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*mini_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit2_2)->GetRect(), (*mini_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*giant_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*giant_it)->dying()) {
								(*giant_it)->Dies();
								kill[3]++;
							}

							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*giant_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit2_2)->GetRect(), (*giant_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}
					auto boss_it = boss_ep.begin();
					while (boss_it != boss_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*boss_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt(HP);

							break;
						}

						/* ����ҷ��ӵ����ел� */
						auto bit2_1 = bs2_1.begin();
						while (bit2_1 != bs2_1.end()) {
							if (RectDuangRect((*bit2_1)->GetRect(), (*boss_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit2_2)->GetRect(), (*boss_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*boss_it)->Show()) {
							delete (*boss_it);// ɾ����ָ��
							boss_ep.erase(boss_it);// �߳�����
							boss_it = boss_ep.begin();
						}
						else
							boss_it++;
					}

					break;// ����case
				}

					  /* ����4���ֲ��ӵ���һ��ʱ�䣩 */
				case 4: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs3_1.push_back(new Bullet3_1(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����У���
						bs3_2.push_back(new Bullet3_2(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����󣩣�
						bs3_3.push_back(new Bullet3_3(bulletimg, hp.GetRect()));// �ҷ��ӵ����ֲ��ӵ����ң���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit3_1 = bs3_1.begin();
					while (bsit3_1 != bs3_1.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_1)->Show())
							bsit3_1 = bs3_1.erase(bsit3_1);
						else
							bsit3_1++;
					}
					auto bsit3_2 = bs3_2.begin();
					while (bsit3_2 != bs3_2.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_2)->Show())
							bsit3_2 = bs3_2.erase(bsit3_2);
						else
							bsit3_2++;
					}
					auto bsit3_3 = bs3_3.begin();
					while (bsit3_3 != bs3_3.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit3_3)->Show())
							bsit3_3 = bs3_3.erase(bsit3_3);
						else
							bsit3_3++;
					}

					/* ���صз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}


							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_2)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_3)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
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
							if (RectDuangRect((*bit3_2)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
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
							if (RectDuangRect((*bit3_3)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
								else
									(*mid_it)->Dies();

								delete (*bit3_3);
								bs3_3.erase(bit3_3);

								break;
							}
							bit3_3++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
							}

							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*mini_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_2)->GetRect(), (*mini_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_3)->GetRect(), (*mini_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*giant_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*giant_it)->dying()) {
								(*giant_it)->Dies();
								kill[3]++;
							}

							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*giant_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_2)->GetRect(), (*giant_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_3)->GetRect(), (*giant_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}
					auto boss_it = boss_ep.begin();
					while (boss_it != boss_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*boss_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt(HP);

							break;
						}

						/* ����ҷ��ӵ����ел� */
						auto bit3_1 = bs3_1.begin();
						while (bit3_1 != bs3_1.end()) {
							if (RectDuangRect((*bit3_1)->GetRect(), (*boss_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_2)->GetRect(), (*boss_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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
							if (RectDuangRect((*bit3_3)->GetRect(), (*boss_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
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

						// ����л��ɳ���Ļ��ȥ��
						if (!(*boss_it)->Show()) {
							delete (*boss_it);// ɾ����ָ��
							boss_ep.erase(boss_it);// �߳�����
							boss_it = boss_ep.begin();
						}
						else
							boss_it++;
					}

					break;// ����case
				}

					  /* ����5�������ӵ���һ��ʱ�䣩 */
				case 5: {
					/* ����ҷ��ӵ� */
					bsing++;
					if (bsing == 101 - bs_frequency) {// ÿ��һ��ʱ�䷢��һ���ӵ�
						bsing = 0;
						bs4.push_back(new Bullet4(bullet4img, hp.GetRect()));// �ҷ��ӵ������׵���

						/* ����һ�������ӵ���ָ�����״̬ */
						bullets_total++;
						if (bullets_total >= BULLETS_MAX) {
							condition = 0;
							bullets_total = 0;
						}
					}

					/* �����ҷ��ӵ� */
					auto bsit4 = bs4.begin();
					while (bsit4 != bs4.end()) {
						// ����ӵ��ɳ���Ļ��ȥ��
						if (!(*bsit4)->Show())
							bsit4 = bs4.erase(bsit4);
						else
							bsit4++;
					}

					/* ���صз��ɻ� */
					auto it = ep.begin();
					while (it != ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*it)->dying()) {
								(*it)->Dies();
								kill[0]++;
							}

							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								if (!(*it)->dying()) {
									(*it)->Dies();
									kill[0]++;
								}

								break;
							}
							bit4++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*it)->Show()) {
							delete (*it);// ɾ����ָ��
							ep.erase(it);// �߳�����
							it = ep.begin();
						}
						else
							it++;
					}
					auto mid_it = mid_ep.begin();
					while (mid_it != mid_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mid_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mid_it)->dying()) {
								(*mid_it)->Dies();
								kill[1]++;
							}

							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*mid_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								// �������1���������ȥ1����
								if ((*mid_it)->how_many_lives() > 1)
									(*mid_it)->hurt();
								// ���ǡ��1���������ж���������ɱ��+1
								else if ((*mid_it)->how_many_lives() == 1) {
									(*mid_it)->Dies();
									kill[1]++;
									kill_temp++;
								}
								// ���С��1������ȷ������
								else
									(*mid_it)->Dies();

								break;
							}
							bit4++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mid_it)->Show()) {
							delete (*mid_it);// ɾ����ָ��
							mid_ep.erase(mid_it);// �߳�����
							mid_it = mid_ep.begin();
						}
						else
							mid_it++;
					}
					auto mini_it = mini_ep.begin();
					while (mini_it != mini_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*mini_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*mini_it)->dying()) {
								(*mini_it)->Dies();
								kill[2]++;
							}

							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*mini_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								if (!(*mini_it)->dying()) {
									(*mini_it)->Dies();
									kill[2]++;
								}

								break;
							}
							bit4++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*mini_it)->Show()) {
							delete (*mini_it);// ɾ����ָ��
							mini_ep.erase(mini_it);// �߳�����
							mini_it = mini_ep.begin();
						}
						else
							mini_it++;
					}
					auto giant_it = giant_ep.begin();
					while (giant_it != giant_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*giant_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt();
							if (!(*giant_it)->dying()) {
								(*giant_it)->Dies();
								kill[3]++;
							}

							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}

						/* ����ҷ��ӵ����ел� */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*giant_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								if ((*giant_it)->hurt()) {
									kill[3]++;
									kill_temp++;
								}

								break;
							}
							bit4++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*giant_it)->Show()) {
							delete (*giant_it);// ɾ����ָ��
							giant_ep.erase(giant_it);// �߳�����
							giant_it = giant_ep.begin();
						}
						else
							giant_it++;
					}
					auto boss_it = boss_ep.begin();
					while (boss_it != boss_ep.end()) {
						// �з��ɻ����ҷ��ɻ���ײ
						if (RectDuangRect((*boss_it)->GetRect(), hp.GetRect())) {
							/* ��� */
							is_play = hp.hurt(HP);

							break;
						}

						/* ����ҷ��ӵ����ел� */
						auto bit4 = bs4.begin();
						while (bit4 != bs4.end()) {
							if (RectDuangRect((*bit4)->GetRect(), (*boss_it)->GetRect())) {// ����ӵ����ел�
								/* ��� */
								if ((*boss_it)->hurt()) {
									kill[4]++;
									kill_temp++;
									flag = true;
								}

								break;
							}
							bit4++;
						}

						// ����л��ɳ���Ļ��ȥ��
						if (!(*boss_it)->Show()) {
							delete (*boss_it);// ɾ����ָ��
							boss_ep.erase(boss_it);// �߳�����
							boss_it = boss_ep.begin();
						}
						else
							boss_it++;
					}

					break;// ����case
				}
				}

				/* ÿɱһ������������һ������ */
				if ((condition == 0) && (kill_temp >= KILL_FOR_GIFT)) {
					/* ������ŵ��ߣ�δ��ɣ� */
					gift_index = rand() % 5;
					AddGift(gift, giftimg[gift_index]);

					kill_temp = 0;
					bullets_total = 0;
				}
				/* ���ص��� */
				auto gift_it = gift.begin();
				while (gift_it != gift.end()) {
					// �ɹ�ʰȡ����
					if (RectDuangRect((*gift_it)->GetRect(), hp.GetRect())) {
						condition = gift_index + 1;

						delete (*gift_it);// ɾ����ָ��
						gift.erase(gift_it);// �߳�����
						gift_it = gift.begin();
						break;
					}
					// δ��ʰȡ���ߣ��Ѿ��ɳ���Ļ��
					if (!(*gift_it)->Show()) {
						delete (*gift_it);// ɾ����ָ��
						gift.erase(gift_it);// �߳�����
						gift_it = gift.begin();
					}
					else
						gift_it++;
				}

				/* ���Ͻ�ʵʱ��ʾ��ɱ���͵÷� */
				score = kill[0] * 3 + kill[1] * 5 + kill[2] * 1 + kill[3] * 7 + kill[4] * 1000;
				PrintScore(kill, score);

				/* ����Ƿ���� */
				if (score >= SCORE_5) {
					flag = true;
					is_play = false;
				}

				EndBatchDraw();// BeginBatchDraw��EndBatchDraw��������Ƶ��				
			}

			stopBgmMusic();
			Over(kill, score, flag);// �������
			break;
		}
	}

	return true;
}
