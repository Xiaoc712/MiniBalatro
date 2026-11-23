#include<raylib.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "cards.h"
#include "config.h"


int target = 300;
int money = 4;
int round_no;

int score;
int plays;
int discards;

Card poker[52]; //定义扑克牌身份

Card Deck[52]; //随机顺序牌库
Card * deck_top = Deck;//洗牌时指向牌堆顶

int hand[HAND_SIZE];//定义手牌，代表手牌序号
int hand_cnt = HAND_SIZE;

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
    for(int i = 0; i < 52; i++){
        Deck[i] = poker[i];
    }

    //---------- 洗牌 ----------
    shuffle(Deck, 52);

    //---------- 发牌 ----------
    for(int i = 0; i < HAND_SIZE; i++){
        hand[i] = -1;//-1代表当前位置没有手牌
    }
    fill_hand(hand);


    /*************************************/
    //UI设计

    //---------- 随机配色主题 ----------
    Theme theme = THEMES[rand() % THEME_COUNT];
    //---------- 随机卡背样式 ----------
    int back_type = rand()%9;
    //---------- 窗口创建 ----------
    InitWindow(BG_WIDTH, BG_HEIGHT, TITLE);
    SetTargetFPS(60);

    //---------- 卡牌加载 ----------
    Texture2D card_tex[52];
    for(int i = 0; i < 52; i++){
            char card_path[256];
            snprintf(card_path, sizeof(card_path), "%scard%s%s.png", CARD_DIR, SUIT_NAME[poker[i].suit], RANK_NAME[poker[i].rank]);
            //printf("%s\n", path);
            card_tex[i] = LoadTexture(card_path);
    }
    //卡牌加载检查
    for(int i = 0; i < 52; i++){
        if (card_tex[i].id == 0) {
            printf("纹理加载失败！\n");
            CloseWindow();
            return 1;
        }
    }
    //---------- 卡背加载 ----------
    Texture2D back_tex[9];
    for(int i = 0; i < 9; i++){
        char back_path[256];
        char * back_color[3] = {"blue", "green", "red"};
        int back_number[3] = {2, 4, 5};
        snprintf(back_path, sizeof(back_path), "%scardBack_%s%d.png", CARD_DIR, back_color[i/3], back_number[i%3]);
        //printf("%s\n", back_path);
        back_tex[i] = LoadTexture(back_path);
    }
    //卡背加载检查
    for(int i = 0; i < 9; i++){       
        if (back_tex[i].id == 0) {
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

        //---------- 计分板绘制 ----------
        draw_panel(target, score, money, round_no, plays, discards);

        //---------- 卡牌绘制 ----------
        for(int i = 0; i < hand_cnt; i++){
            if(hand[i] < 0 || hand[i] >= 52) continue; //越界保护
            DrawTexturePro(
                card_tex[hand[i]],
                //纹理裁剪大小
                (Rectangle){ 0, 0, (float)card_tex[hand[i]].width, (float)card_tex[hand[i]].height },
                //绘制位置（左上坐标x， y， 宽， 高）
                (Rectangle){ HAND_LEFT_GAP + i*HAND_STEP, HAND_UP_GAP + ARC*(i - (hand_cnt - 1)/2)*(i - (hand_cnt - 1)/2), CARD_TEX_WIDTH, CARD_TEX_HEIGHT },
                //旋转中心
                (Vector2){ 56, 76 },
                //旋转角度
                TILT*(i - (hand_cnt - 1)/2),
                //染色
                WHITE
            );
        }        

        //---------- 卡背绘制 ----------
        DrawTexturePro(
                back_tex[back_type],
                //纹理裁剪大小
                (Rectangle){ 0, 0, (float)back_tex[back_type].width, (float)back_tex[back_type].height },
                //绘制位置（左上坐标x， y， 宽， 高）
                (Rectangle){ BACK_X, BACK_Y, CARD_TEX_WIDTH, CARD_TEX_HEIGHT },
                //旋转中心
                (Vector2){ 56, 76 },
                //旋转角度
                0,
                //染色
                WHITE
            );

        //---------- 按钮绘制 ----------
            
        EndDrawing();
        //事件处理
    }

    //---------- 卡牌显存释放 ----------
    for(int i = 0; i < 52; i++){
        UnloadTexture(card_tex[i]);
    }

    //---------- 卡背显存释放 ----------
    for(int i = 0; i < 9; i++){
        UnloadTexture(back_tex[i]);
    }

    CloseWindow();
    return 0;
}

void shuffle(Card * Deck, int n)//洗牌函数
{
    for(int i = n - 1; i > 0; i--){
        int j = rand()%(i + 1);
        Card temp = Deck[i];
        Deck[i] = Deck[j];
        Deck[j] = temp;
    }
}

void fill_hand(int * hand)//抽牌至手牌上限
{   
    for(int i = 0; i < HAND_SIZE; i++){
        if (deck_top >= Deck + 52) break;
        if(hand[i] == -1 && deck_top < Deck + 52){
            hand[i] = 4*deck_top->rank + deck_top->suit;
            deck_top++;
        }
    }
}

void draw_panel(int target, int score, int money, int round_no, int plays, int discards)
{
    DrawRectangle(PANEL_X, PANEL_Y, PANEL_WIDTH, PANEL_HEIGHT, PANEL_BG_COLOR);
}