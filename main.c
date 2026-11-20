#include "config.h"
#include "Cards.h"

int main(void)
{
    //按点数从小到大为扑克牌初始化，顺序为红桃2，黑桃2，梅花2，方片2，红桃3···
    for(int i = 0; i < 13; i++){
        for(int j = 0; j < 4; j++){
            poker[13 * j + i].rank = i;
            poker[4 * i + j].suit = j;
        }
    }
    /*printf("花色    点数\n");
    for(int i = 0; i < 52; i++){
            printf("%-7d %d\n",poker[i].suit,poker[i].rank);
    }*/
    return 0;
}
