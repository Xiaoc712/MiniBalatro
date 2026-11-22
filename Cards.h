#ifndef CARDS_H
#define CARDS_H

//---------- 卡牌信息 ----------
typedef enum { HEART, SPADE, CLUB, DIAMOND }Suit;
typedef enum { Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace }Rank;
typedef struct {
    Rank rank;
    Suit suit;
    
}Card;

#define HAND_SIZE 8 //手牌上限
#define CHOSEN_MAX 5 //出牌上限

//---------- 牌型信息 ----------
typedef enum { Royal_Flush, Straight_Flush, Four_of_a_Kind, Full_House, Flush, Straight, Three_of_a_Kind, Two_Pair, One_Pair, High_card } PokerHandType;

//---------- 游戏流程 ----------
#define FINAL_ROUND 10
#define SCORE_STEP 150

extern Card poker[52];
extern int hand[HAND_SIZE];

//---------- 函数声明 ----------
int hand_type(int *cards);/*判断手牌类型函数，输入的是经过排序的待操作牌值数组*/
void joker_scoring(int *chips, int *multiply, int card_type);/*调用已经购买的joker的计分函数*/
int score_calculate(int *chosen);/*计分函数*/

#endif