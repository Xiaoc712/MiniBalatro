#ifndef CONFIG_H
#define CONFIG_H


#include<raylib.h>

// ---------- 窗口信息 ----------
#define BG_WIDTH  1280
#define BG_HEIGHT 720
#define TITLE  "MiniBalatro"

// ---------- 背景信息 ----------
#define RADIUS 460

static const Vector2 CIRCLE_CENTER = { BG_WIDTH / 2, (int)(BG_HEIGHT*(0.44)) };

// ---------- 配色主题 ----------
typedef struct {
    Color bgTop;        // 背景上
    Color bgBottom;     // 背景下
    Color glowInner;    // 光晕中心
    Color glowOuter;    // 光晕边缘
} Theme;
 
static const Theme THEMES[] = {
    // 紫色
    { { 58, 38, 96, 255 }, { 16, 11, 30, 255 }, { 150, 100, 230, 55 }, { 150, 100, 230, 0 } },
    // 绿色
    { { 58, 116, 92, 255 }, { 18, 46, 37, 255}, { 120, 200, 165, 70 }, { 90, 170, 135, 0 } }
};
#define THEME_COUNT 2

// ---------- 卡面路径信息 ----------
static const char *SUIT_NAME[4] = { "Hearts", "Spades", "Clubs", "Diamonds" };
static const char *RANK_NAME[13] = { "2","3","4","5","6","7","8","9","10","J","Q","K","A" };

#define CARD_DIR "./resource/poker_card1/PNG/Cards/"

// ---------- 卡牌纹理信息 ----------
#define CARD_TEX_WIDTH 112
#define CARD_TEX_HEIGHT 152
//手牌间距
#define HAND_STEP (int)(CARD_TEX_WIDTH*1.2)
//手牌侧边距
#define HAND_LEFT_GAP (int)((BG_WIDTH - CARD_TEX_WIDTH - HAND_STEP*(HAND_SIZE - 1))/2)
#define HAND_UP_GAP 450

#endif