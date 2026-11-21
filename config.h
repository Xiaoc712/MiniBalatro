#ifndef CONFIG_H
#define CONFIG_H


#include<raylib.h>

// ---------- 窗口信息 ----------
#define WIDTH  1280
#define HEIGHT 720
#define TITLE  "MiniBalatro"

// ---------- 背景信息 ----------
#define RADIUS 460

static const Vector2 CIRCLE_CENTER = { WIDTH / 2, (int)(HEIGHT*(0.44)) };

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


#endif