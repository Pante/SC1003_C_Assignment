#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 5
#define STRING_LIMIT 20

typedef struct Card {
    int id;
    char name[STRING_LIMIT];
    char company[STRING_LIMIT];
} Card;

typedef struct Cards {
    Card values[MAX];
    size_t length;
} Cards;


int compare_card(const void *a, const void *b) {
    return ((Card*) a)->id - ((Card*) b)->id;
}

void sort(Cards *const cards) {
    qsort(cards->values, cards->length, sizeof(Card), compare_card);
}


void read(char *const in) {
    fgets(in, STRING_LIMIT, stdin);
    in[strcspn(in, "\r\n")] = 0;
}

void to_lower(const char in[STRING_LIMIT], char out[STRING_LIMIT]) {
    strcpy(out, in); // This is inefficient as heck, but I'm too lazy to deal with terminal \0s
    size_t i = 0;
    for(; out[i] != '\0'; i++) {
        out[i] = tolower(in[i]);
    }
}

void print_card(const Card *const card) {
    printf("nameCardID: %d\n", card->id);
    printf("personName: %s\n", card->name);
    printf("companyName: %s\n", card->company);
}


void listNameCards(const Cards *const cards) {
    printf("listNameCards():\n");

    if (cards->length == 0) {
        printf("The name card holder is empty\n");
        return;
    }

    size_t i = 0;
    for (; i < cards->length; i++) {
        print_card(&cards->values[i]);
    }
}

void addNameCard(Cards *const cards) {
    printf("addNameCard():\n");
    Card card = {};

    printf("Enter nameCardID: \n");
    char buffer[STRING_LIMIT];
    fgets(buffer, STRING_LIMIT, stdin);
    card.id = atoi(buffer);


    printf("Enter personName:\n");
    read(card.name);

    printf("Enter companyName:\n");
    read(card.company);
    
    if (cards->length == MAX) {
        printf("The name card holder is full\n");
        return;
    }

    size_t i = 0;
    for (; i < cards->length; i++) {
        if (card.id == cards->values[i].id) {
            printf("The nameCardID has already existed\n");
            return;
        }
    }

    cards->values[cards->length] = card;
    cards->length++;
    sort(cards);
    printf("The name card has been added successfully\n");
}

void removeNameCard(Cards *const cards) {
    printf("removeNameCard():\n");
    printf("Enter personName:\n");
    char target[STRING_LIMIT];
    read(target);
    to_lower(target, target);

    if (cards->length == 0) {
        printf("The name card holder is empty\n");
        return;
    }

    size_t i = 0;
    for (; i < cards->length; i++) {
        Card card = cards->values[i];
        char name[STRING_LIMIT];
        to_lower(card.name, name);
        if (strcmp(name, target) == 0) {
            size_t current = i;
            size_t next = i + 1;
            for (; next < cards->length; current++, next++) {
                cards->values[current] = cards->values[next];
            }
            cards->length--;

            printf("The name card is removed\n");
            print_card(&card);
            return;
        }
    }

    printf("The target person name is not in the name card holder\n");
}

void getNameCard(Cards *const cards) {
    printf("getNameCard():\n");
    printf("Enter personName:\n");
    char target[STRING_LIMIT];
    read(target);
    to_lower(target, target);

    size_t i = 0;
    for (; i < cards->length; i++) {
        Card card = cards->values[i];
        char name[STRING_LIMIT];
        to_lower(card.name, name);
        if (strcmp(target, name) == 0) {
            printf( "The target person name is found\n");
            print_card(&card);
            return;
        }
    }

    printf("The target person name is not found\n");
}


int main() {
    Cards cards = { .length = 0 };

    printf("NTU NAME CARD HOLDER MANAGEMENT PROGRAM: \n"
           "1: listNameCards() \n"
           "2: addNameCard() \n"
           "3: removeNameCard() \n"
           "4: getNameCard() \n"
           "5: quit\n"
    );

    while (true) {
        printf("Enter your choice: \n");

        char buffer[STRING_LIMIT];
        fgets(buffer, STRING_LIMIT, stdin);
        switch (atoi(buffer)) {
            case 1:
                listNameCards(&cards);
                break;
            case 2:
                addNameCard(&cards);
                break;
            case 3:
                removeNameCard(&cards);
                break;
            case 4:
                getNameCard(&cards);
                break;
            default:
                return 0;
        }
    }
}
