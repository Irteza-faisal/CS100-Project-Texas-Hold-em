#include <iostream>
#include <algorithm>
#include "Poker_main.h"
using namespace std;

void sort_number(POKER cards[5], const int numofcards)
{
    for (int i = 0; i<numofcards; i++)
    {
        for (int ii = i + 1; ii<numofcards; ii++)
        {
            if (cards->Nums[i] > cards->Nums[ii])
            {
                int temp = cards->Nums[i];
                cards->Nums[i] = cards->Nums[ii];
                cards->Nums[ii] = temp;
            }
        }
    }
}

int confidence(POKER cards[5],int numofcards) 
//cards 1 to 5, where card 0 and 1 are the cards dealt, cards 2, 3, 4 are the cards on the table. Num of cards ensures that confidence level is  only taken with the cards available on the table at that moment.   
{
    bool pair = false;
    bool two_pair = false;
    bool three_of_a_kind = false;
    bool straight = false;
    bool flush = false;
    bool full_house = false;
    bool four_of_a_kind = false;
    bool straight_flush = false;
    bool royal_flush = false;

    POKER sortedarray1[5];
    
    copy (cards, cards+numofcards,sortedarray1);

    sort_number(sortedarray1,numofcards);

    POKER sortedarray2[5];

    int samecards;
    //this number tells the number of cards that are the same, which dictates whether the ai has a pair, three of a kind, or four of a kind.
    
    int different_combos[3];
    //this tell the number of combos that exist (2 pairs, straight, 3 in a row, 4 in a row etc)
    
    int counter2 = 0;
    //this counter tells the actual number of times the loop below is used. its used in inserting values inside the different_combos arrray.
    
    for (int i = 0; i < numofcards; i++)
    {

        samecards = 0;

        for (int ii = i+1; ii<numofcards; ii++)
        {
        
            if (cards->Nums[i] == cards->Nums[ii] )
            {
                samecards++;
            }
            else
            {
                break;
            }
        }
        
        i=+samecards;
        different_combos[counter2] = samecards;
        counter2++;
    }

    for (int iii = 0; iii<sizeof(different_combos)/sizeof(int); iii++)
    {
        //time to be inefficient and make a tower of if statements les gooooooooo
        switch (different_combos[iii])
        {
        case 2:
            if (!pair)
            {
                pair = true;
            }
            else
            {
                two_pair = true;
            }
            break;
        case 3:
            three_of_a_kind = true;
            break;
        case 4:
            four_of_a_kind = true;
            break;
        }
    }
    if (three_of_a_kind && pair)
    {
        full_house = true;
    }
}
