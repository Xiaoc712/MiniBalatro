#include<raylib.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "Cards.h"
#include "config.h"


Card poker[52];//定义扑克牌
int hand[NUM_HAND];//定义手牌

int main(void)
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
    //---------- 生成随机数种子 ----------



    /*************************************/
    //UI设计

    //---------- 随机配色主题 ----------
        Theme theme = THEMES[rand() % THEME_COUNT];

    //---------- 窗口创建 ----------
    InitWindow(BG_WIDTH, BG_HEIGHT, TITLE);
    SetTargetFPS(60);

    //---------- 卡牌加载 ----------
    Texture2D card_tex[52];
    for(int i = 0; i < 52; i++){
            char path[256];
            snprintf(path, sizeof(path), "%scard%s%s.png", CARD_DIR, SUIT_NAME[poker[i].suit], RANK_NAME[poker[i].rank]);
            //printf("%s\n", path);
            card_tex[i] = LoadTexture(path);
    }
    //---------- 卡牌加载检查 ----------
    for(int i = 0; i < 52; i++){
        if (card_tex[i].id == 0) {
            printf("纹理加载失败！\n");
            CloseWindow();
            return 1;
        }
    }

    while(!WindowShouldClose()){
        //绘图
        BeginDrawing();
        ClearBackground(WHITE);
        
        //---------- 背景绘制 ----------
        DrawRectangleGradientV(0, 0, BG_WIDTH, BG_HEIGHT, theme.bgTop, theme.bgBottom);
        DrawCircleGradient(CIRCLE_CENTER, RADIUS, theme.glowInner, theme.glowOuter);

        //---------- 卡牌绘制 ----------
        for(int i = 0; i < NUM_HAND; i++){
            DrawTexturePro(
                card_tex[hand[i]],
                //纹理裁剪大小
                (Rectangle){ 0, 0, (float)card_tex[hand[i]].width, (float)card_tex[hand[i]].height },
                //绘制位置（左上坐标x， y， 宽， 高）
                (Rectangle){ HAND_LEFT_GAP + i*HAND_STEP, HAND_UP_GAP, CARD_TEX_WIDTH, CARD_TEX_HEIGHT },
                //旋转中心
                (Vector2){ 0, 0 },
                //旋转角度
                0,
                //染色
                WHITE
            );
        }
        EndDrawing();
        //事件处理
    }

    //---------- 卡牌显存释放 ----------
    for(int i = 0; i < 52; i++){
        UnloadTexture(card_tex[i]);
    }
    CloseWindow();
    return 0;
}
