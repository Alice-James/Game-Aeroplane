#include "music.h"
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <io.h>

#pragma comment(lib, "Winmm.lib")


/* ≤•∑≈±≥æ∞“Ù¿÷ */
void playBgmMusic()
{
    mciSendString(_T("open \".\\res\\bg.wav\" alias bgm"), NULL, 0, NULL);
    mciSendString(_T("play bgm"), NULL, 0, NULL);
}

/* ‘›Õ£±≥æ∞“Ù¿÷ */
void stopBgmMusic() {
    mciSendString(_T("stop bgm"), NULL, 0, NULL);
}
