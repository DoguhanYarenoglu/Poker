//1600002789 Doðuhan Yarenoðlu
#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h> 

#define NUM_SUITS 4//Type of our card
#define NUM_RANKS 13//Cards rank 
#define NUM_CARDS 5 //Cards in our hand 

void read_cards(int numrank[], int numsuit[]);//fonction to read cards
void analyze_hand(int numrank[], int numsuit[], bool* straight,bool* flush, bool* four, bool* three, int* pairs);//function to analyze hand 
void print_result(const bool* straight, const bool* flush, const bool* four,const bool* three, const int* pairs);//function to print result



int main(void) {
    bool straight, flush, four, three;
    int pairs;

    int numrank[NUM_RANKS];
    int numsuit[NUM_SUITS];
    for (;;) {
        read_cards(numrank, numsuit);
        analyze_hand(numrank, numsuit,
            &straight, &flush, &four, &three, &pairs);
        print_result(&straight, &flush, &four, &three, &pairs);
    }
}
// in this function we read the cards user given in 4 type of cards and 13num.
void read_cards(int numrank[], int numsuit[]) {
    bool card_exists[NUM_RANKS][NUM_SUITS];
    char c, rank_ch, suit_ch;
    int rank, suit;
    bool bad_card;
    int cards_read = 0;

    for (rank = 0; rank < NUM_RANKS; rank++) {
        numrank[rank] = 0;
        for (suit = 0; suit < NUM_SUITS; suit++)
            card_exists[rank][suit] = false;
    }

    for (suit = 0; suit < NUM_SUITS; suit++)
        numsuit[suit] = 0;

    while (cards_read < NUM_CARDS) {
        bad_card = false;

        printf("Enter a card: ");
        rank_ch = getchar();
        switch (rank_ch) {
        case '0':           exit(EXIT_SUCCESS);
        case '2':           rank = 0; break;
        case '3':           rank = 1; break;
        case '4':           rank = 2; break;
        case '5':           rank = 3; break;
        case '6':           rank = 4; break;
        case '7':           rank = 5; break;
        case '8':           rank = 6; break;
        case '9':           rank = 7; break;
        case 't': case 'T': rank = 8; break;
        case 'j': case 'J': rank = 9; break;
        case 'q': case 'Q': rank = 10; break;
        case 'k': case 'K': rank = 11; break;
        case 'a': case 'A': rank = 12; break;
        default:            bad_card = true;
        }

        suit_ch = getchar();
        switch (suit_ch) {
        case 'c': case 'C': suit = 0; break;
        case 'd': case 'D': suit = 1; break;
        case 'h': case 'H': suit = 2; break;
        case 's': case 'S': suit = 3; break;
        default:            bad_card = true;
        }
        while ((c = getchar()) != '\n')
            if (c != ' ') bad_card = true;

        if (bad_card)
            printf("Bad card; ignored.\n");
        else if (card_exists[rank][suit])
            printf("Duplicate card; ignored.\n");
        else {
            numrank[rank]++;
            numsuit[suit]++;
            card_exists[rank][suit] = true;
            cards_read++;
        }
    }
}

//here we tryin' to analyze hand to cards given to 'straight,'flush, 'three,'four or pairs 
void analyze_hand(int numrank[], int numsuit[], bool* straight,
    bool* flush, bool* four, bool* three, int* pairs) {
    int num_consec = 0;
    int rank, suit;

    *straight = false;
    *flush = false;
    *four = false;
    *three = false;
    *pairs = 0;

    for (suit = 0; suit < NUM_SUITS; suit++)
        if (numsuit[suit] == NUM_CARDS)
            *flush = true;

    rank = 0;
    while (numrank[rank] == 0) rank++;
    for (; rank < NUM_RANKS && numrank[rank] > 0; rank++)
        num_consec++;
    if (num_consec == NUM_CARDS) {
        *straight = true;
        return;
    }

    for (rank = 0; rank < NUM_RANKS; rank++) {
        if (numrank[rank] == 4) *four = true;
        if (numrank[rank] == 3) *three = true;
        if (numrank[rank] == 2) (*pairs)++;
    }
}
//in this funciton we print to analyzed hand to output 
void print_result(const bool* straight, const bool* flush, const bool* four,
    const bool* three, const int* pairs) {
    if (*straight && *flush) printf("Straight flush");
    else if (*four)          printf("Four of a kind");
    else if (*three &&
        *pairs == 1)    printf("Full house");
    else if (*flush)         printf("Flush");
    else if (*straight)      printf("Straight");
    else if (*three)         printf("Three of a kind");
    else if (*pairs == 2)    printf("Two pairs");
    else if (*pairs == 1)    printf("Pair");
    else                     printf("High card");

    printf("\n\n");
}