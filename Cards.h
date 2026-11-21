#ifndef CARDS_H
#define CARDS_H

typedef enum { HEART, SPADE, CLUB, DIAMOND }Suit;
typedef enum { Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace }Rank;
typedef struct {
    Rank rank;
    Suit suit;
}Card;
extern Card poker[52];

#endif