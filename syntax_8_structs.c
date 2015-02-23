#include <stdio.h>

typedef enum {
    hearts,
    clubs,
    spades,
    diamonds    
} Suit;


typedef struct Card Card;
struct Card {
    Suit    suit;
    int     value;
};

Card fakeMagicTrick_byValue(Card c);
void fakeMagicTrick_byReference(Card* c);



int main(){
    Card c = {spades, 5};
    Card d = fakeMagicTrick_byValue(c);
    
    printf("c = Card(%d, %d) (expected: Card(2, 5))\n", c.suit, c.value);
    printf("d = Card(%d, %d) (expected: Card(0, 5))\n", d.suit, d.value);
    
    fakeMagicTrick_byReference(&c);

    printf("c = Card(%d, %d) (expected: Card(0, 5))\n", c.suit, c.value);
}



Card fakeMagicTrick_byValue(Card c){
    Card result = {hearts, c.value};
    return result;
    
    /// Alternatives:
    
    // "Compound Literal"
    /*
    return (Card){hearts, c.value};
    */
    
    // "Designated initializer"
    /*
    return (Card){
        .value = c.value;
        .suit = hearts
    }
    */
}

void fakeMagicTrick_byReference(Card* c){
    c->suit = hearts;
    
    /// Alternative:
    // The above is "syntactic sugar" for this:
    /*
    (*c).suit = hearts;
    */
}



