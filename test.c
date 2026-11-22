#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"cards.h"


int main(void)
{
    srand(((unsigned)time(NULL)));

    Card poker[52];
    Card Deck[52];

    //按点数从小到大为扑克牌初始化，顺序为红桃2，黑桃2，梅花2，方片2，红桃3···
    for(int i = 0; i < 13; i++){
        for(int j = 0; j < 4; j++){
            Deck[4 * i + j].suit = j;
            Deck[4 * i + j].rank = i;
        }
    }

    shuffle(Deck, 52);

    printf("花色    点数\n");
    for(int i = 0; i < 52; i++){
            printf("%-7d %d\n",Deck[i].suit,Deck[i].rank);
    }

    return 0;
}
void shuffle(Card * Deck, int n)
{
    for(int i = n - 1; i > 0; i--){
        int j = rand()%(i + 1);
        Card temp = Deck[i];
        Deck[i] = Deck[j];
        Deck[j] = temp;
    }
}