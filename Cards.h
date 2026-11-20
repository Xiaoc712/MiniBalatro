typedef enum { HEART, SPADE, CLUB, DIAMOND }Suit;
typedef enum { Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King }Rank;
typedef struct {
    Rank rank;
    Suit suit;
}Card;
Card poker[52];