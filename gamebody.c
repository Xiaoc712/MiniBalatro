#include<stdio.h>

#define FINAL_ROUND 10
#define SCORE_STEP 150
#define HAND_SIZE 8
#define CHOSEN_MAX 5

int money = 4;
int cards_left = 52;
int round = 1;
int score = 0;
int target = 300;/*初始化数据*/


char command;
int card_chosen[CHOSEN_MAX];/*选择的牌数组*/
int card_hand[HAND_SIZE];/*手牌数组*/
char *oringal_input;/*原始输入*/
int num;/*选择的待操作牌数*/
int scoring[CHOSEN_MAX];/*计分数组*/
int jokers[3] = {0};/*小丑牌数组，存放购买的joker牌值。*//*小丑(Normal)：+4倍率； 半张(Half)：出牌数≤3时+8倍率； 旗手(Banner)：每剩一次弃牌+30筹码*/
int card_suit[4] = {0};/*红桃，黑桃，梅花，方块*/
int card_point[13] = {0};/*2，3，4，5，6，7，8，9，10，J，Q，K, A*/
int card_value[CHOSEN_MAX];


int hand_type(int *card_value)/*判断手牌类型函数，输入的是经过排序的待操作牌值数组*/
{
    int i, j = 0, k = 1;
    int pairs, threes, fours, flush = 0;
    
    int chosen_point[5] = {0};/*选择的牌点数*/
    for(i = 0; i < num; i++){
        card_suit[(card_value[i]-1)/13]++;
        card_point[(card_value[i]-1)%13]++;
        chosen_point[i] = (card_value[i]-1)%13;
    }
    for(i = 0; i < num-1; i++)
    {
        for(j = 0; j < num-1-i; j++){
            if(chosen_point[j] > chosen_point[j+1]){
                int temp = chosen_point[j];
                chosen_point[j] = chosen_point[j+1];
                chosen_point[j+1] = temp;
            }
        }
    }
    for(i = 0; i < 13; i++){
        if(card_point[i] == 2) pairs++;
        else if(card_point[i] == 3) threes++;
        else if(card_point[i] == 4) fours++;
    }
    for(i = 0; i < 4; i++){
        if(card_suit[i] == 5) flush = 1;/*同花*/
    }
    if(pairs == 1 && threes == 1) return 3;/*葫芦*/
    else if(fours == 1) return 2;/*四条*/
    else if(threes == 1) return 6;/*三条*/
    else if(pairs == 2) return 7;/*两对*/
    else if(pairs == 1) return 8;/*一对*/
    else if(num == 5 && chosen_point[4] ==chosen_point[3]+1 && chosen_point[3] == chosen_point[2]+1 && chosen_point[2] == chosen_point[1]+1 && chosen_point[1] == chosen_point[0]+1){
        if(flush == 1) return 1;/*同花顺*/
        else return 5;/*顺子*/
    }
    else if(flush == 1) return 5;/*同花*/
    else return 9;/*高牌*/

}
int joker_scoring(int *chips, int *multiply, int card_type)/*调用已经购买的joker的计分函数*/
{
    int i;
    if(jokers[0] == 1) *multiply += 4;/*小丑(Normal)*/
    if(jokers[1] == 1 && num <= 3) *multiply += 8;/*半张(Half)*/
    if(jokers[2] == 1) *chips += 30;/*旗手(Banner)*/
    switch(card_type)
    {
        case 1:{
            *chips = 100; *multiply = 8;
            for(i = 0; i < 5; i++){
                *chips += (card_value[i]-1) % 13 + 2;
            }
            break;
        }
        case 2: {
            *chips = 60; *multiply = 7;
            for(i = 0; i < 13; i++){
                if(card_point[i] == 4){
                    *chips += (i+2) * 4;
                    break;
                }
            }
        }
        case 3: {
            *chips = 40; *multiply = 4;
            for(i = 0; i < 13; i++){
                if(card_point[i] == 3){
                    *chips += (i+2) * 3;  
                }
                if(card_point[i] == 2){
                    *chips += (i+2) * 2;
            }
            break;
            }
        }
        case 4: {
            *chips = 35; *multiply = 4;
            for(i = 0; i < 5; i++){
                *chips += (card_value[i]-1) % 13 + 2;
            }
            break;

        }
        case 5: {
            *chips = 30; *multiply = 4;
            for(i = 0; i < 5; i++){
                *chips += (card_value[i]-1) % 13 + 2;
            }
            break;
        }
        case 6: {
            *chips = 30; *multiply = 3;
            for(i = 0; i < 13; i++){
                if(card_point[i] == 3){
                    *chips += (i+2) * 3;  
                    break;
                }
            }
        }
        case 7: {
            *chips = 20; *multiply = 2;
            for(i = 0; i < 13; i++){
                if(card_point[i] == 2){
                    *chips += (i+2) * 2;  
                }
            }
            break;
        }
        case 8: {
            *chips = 10; *multiply = 2;
            for(i = 0; i < 13; i++){
                if(card_point[i] == 2){
                    *chips += (i+2) * 2;  
                    break;
                }
            }
        }
        default: {
            *chips = 5; *multiply = 1;
            *chips += card_value[num-1] % 13 + 2;
        }
    }


}


int score_calculate(int *card_chosen)/*计分函数*/
{
    int score = 0;
    int chips = 0;
    int multiply = 0;
    int card_type;
    int i, j;
    for(int i = 0; i < num; i++){
        card_value[i] = card_hand[card_chosen[i]-1];
    }/*将选择的序号转换为牌值*/
    for(i = 0; i < num-1; i++)/*整理手牌，按花色和点数升序*/
    {
        for(j = 0; j < num-1-i; j++){
            if(card_value[j] > card_value[j+1]){
                int temp = card_value[j];
                card_value[j] = card_value[j+1];
                card_value[j+1] = temp;
            }
        }
    }
    card_type = hand_type(card_value);
    joker_scoring(&chips, &multiply, card_type);/*调用joker计分函数*/
    
    score += chips * multiply;
    return score;
}


void card_deal();/*发牌函数*/


int main()
{
    
    
    
    printf("p:出牌； d:弃牌；\n\n");


    while(round <= FINAL_ROUND){/*本局游戏循环*/


        printf("round %d\n", round);
        printf("<金币：%d> <回合：%d> <目标：%d> <牌堆剩余牌数：%d> \n",
                    money,round,target,cards_left);
        int d_times = 4;
        int p_times = 4;/*初始化出牌次数与弃牌次数*/

        card_deal();/*发牌*/
        while(1)/*回合循环*/{

            
            scanf("输入待操作的卡牌序号：%s",oringal_input);
            num = sscanf(oringal_input,"%d%d%d%d%d",&card_chosen[0],&card_chosen[1],
                         &card_chosen[2],&card_chosen[3],&card_chosen[4]);
            scanf("操作指令：%c",&command);
            cards_left -= num;

            if(command == 'p'){
                p_times--;
                score += score_calculate(card_chosen);/*计分并删除已经出的牌*/ 

                if(p_times == 0 && score < target){
                    printf("回合失败\n");
                    round = FINAL_ROUND + 2;
                    break;
                }
                
                else if(score >= target){
                    printf("回合胜利\n");
                    money += d_times * 2 + p_times;
                    target += SCORE_STEP;
                    round++;
                    break;
                }

                card_deal();
            }
            else if(command == 'd'){
                if(d_times == 0){
                    printf("弃牌次数用尽\n");  
                }
                else{
                    d_times--;
                    printf("弃牌成功\n");
                    card_deal();
                }
                   
            }
        }
        if(round <= FINAL_ROUND){
            shop();
        }
    }
    if(round == FINAL_ROUND + 2){
        printf("游戏结束\n");
    }
    else{
        printf("恭喜通关\n");
    }


}