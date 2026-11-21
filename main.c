#include<raylib.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "Cards.h"
#include "config.h"


Card poker[52];//定义扑克牌

int main(int argc, char * argv)
{
    //---------- 生成随机数种子 ----------
    srand((unsigned)time(NULL));


    //按点数从小到大为扑克牌初始化，顺序为红桃2，黑桃2，梅花2，方片2，红桃3···
    for(int i = 0; i < 13; i++){
        for(int j = 0; j < 4; j++){
            poker[4 * i + j].suit = j;
            poker[4 * i + j].rank = i;
        }
    }
    /*printf("花色    点数\n");
    for(int i = 0; i < 52; i++){
            printf("%-7d %d\n",poker[i].suit,poker[i].rank);
    }*/





    /*************************************/
    //UI设计

    //---------- 随机配色主题 ----------
        Theme theme = THEMES[rand() % THEME_COUNT];

    //---------- 窗口创建 ----------
    InitWindow(WIDTH, HEIGHT, TITLE);
    SetTargetFPS(60);

    //---------- 卡牌绘制 ----------
    for(int i = 0; i < 13; i++){
        for(int j = 0; j < 4; j++){
            char path[256];
            Texture2D card_face[52];
            card_face[4 * i + j] = LoadTexture(path);
        }
    }
    while(!WindowShouldClose()){
        //绘图
        BeginDrawing();
        ClearBackground(WHITE);
        
        //---------- 背景绘制 ----------
        DrawRectangleGradientV(0, 0, WIDTH, HEIGHT, theme.bgTop, theme.bgBottom);
        DrawCircleGradient(CIRCLE_CENTER, RADIUS, theme.glowInner, theme.glowOuter);

        //

        EndDrawing();
        //事件处理
    }
    CloseWindow();
    return 0;
}
