#pragma once

constexpr auto swidth = 800;// 画布宽度
constexpr auto sheight = 1100;// 画布长度

constexpr auto EP_SPEED = 4;// 普通敌机速度
constexpr auto MID_EP_SPEED = 4;// 中型敌机速度
constexpr auto MINI_EP_SPEED = 8;// 小型敌机速度
constexpr auto GIANT_EP_SPEED = 2;// 大型敌机速度
constexpr auto GIFT_SPEED = 2;// 道具速度
constexpr auto BS_SPEED = 10;// 子弹速度
constexpr auto BS_SPEED_3_2 = 4;// 子弹Bullet3_2速度
constexpr auto BS_SPEED_3_3 = 4;// 子弹Bullet3_3速度
constexpr auto EBS_SPEED = 6;// 敌方子弹速度
constexpr auto EBS_SPEED_BOSS1 = 4;// boss_skill_1速度
constexpr auto EBS_SPEED_BOSS2 = 6;// boss_skill_2速度
constexpr auto EBS_SPEED_BOSS3 = 20;// boss_skill_3速度
constexpr auto bs_frequency = 90;// 子弹发射频率(不大于100)
constexpr auto ebs_frequency = 30;// 普通敌机子弹发射频率(不大于100)
constexpr auto mid_ebs_frequency = 40;// 中型敌机子弹发射频率(不大于100)
constexpr auto giant_ebs_frequency = 60;// 大型敌机子弹发射频率(不大于100)
constexpr auto boss_ebs_frequency = 80;// BOSS子弹发射频率(不大于100)


constexpr int HP = 4;// 玩家飞机初始生命值
constexpr int midEnemyHP = 2;// 中型敌机初始生命值
constexpr int giantEnemyHP = 5;// 大型敌机初始生命值
constexpr int bossEnemyHP = 20;// BOSS敌机初始生命值

constexpr int DENSITY = 5;// 普通敌机密度
constexpr int MID_DENSITY = 3;// 中型敌机密度
constexpr int MINI_DENSITY = 8;// 小型敌机密度
constexpr int GIANT_DENSITY = 2;// 大型敌机密度
constexpr int BOSS_DENSITY = 1;// BOSS敌机密度

constexpr int KILL_FOR_GIFT = 20;// 每杀KILL_FOR_GIFT人给一次道具
constexpr int BULLETS_MAX = 20;// 每种道具最多发射子弹次数

constexpr int SCORE_1 = 300;// 闯关模式第1关挑战
constexpr int SCORE_2 = 500;// 闯关模式第2关挑战
constexpr int SCORE_3 = 700;// 闯关模式第3关挑战
constexpr int SCORE_4 = 1300;// 闯关模式第4关挑战
constexpr int SCORE_5 = 3100;// 闯关模式第4关挑战
