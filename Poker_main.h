using namespace std;
#include<iostream>
#include<iomanip>
#include<random>
#pragma once

class POKER {
    public:
    int Nums[13] = {1,2,3,4,5,6,7,8,9,10,11,12,13}; /*Nums and Suits define the Number of cards per suit (13) A,1,2,3,4,5,6,7,8,9,10,J,Q,K*/
    char suits[4] = {'D','H','C','S'};
    int game_state = 0;
    bool player_playing = false;
    /*int Initial_game_states[3] = {1,2,-1}; Defines initial game states of Start game, Rules, Exit game, 1 starts game, 2 is rules, -1 Exit game*/

    /*int Start_sub_states[3] = {1,2,3}; Substates when in Start game to choose between number of players 1->3 2->4 3->5*/

    typedef struct {
        int Number;
        char suit;
        bool exists = true;
    }card;

    card cards[52];

    card draw_card(){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distr(0,51);
        int card_index = distr(gen);
        while (!(cards[card_index].exists)){
            int card_index = distr(gen);
        }
        cards[card_index].exists=false;
        return cards[card_index]; 
    }

    void init_deck(){ /*Initialises deck*/
        int n = 0;
        while (n != 52){
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 13; j++){
                cards[n].Number = Nums[j];
                cards[n].suit = suits[i];
                n++;
            }
        }
        }
    }

    void is_playing_if_yes_ask_if_play_again(bool playing){
        if(!playing){
            
        }
    }

    void main_game_3bots(){
        BOTAI AI1;
        BOTAI AI2;
        BOTAI AI3;
        bool isgame = true;
        player_playing = true;
        while (isgame)
        {
            bool isround = true;
            init_deck();
            while (isround)
            {
                card player_hand[2] = {draw_card(),draw_card()};

                AI1.assign_hand();AI2.assign_hand();AI3.assign_hand();


                
            }
            
        }
        
    }

    void choose_number_of_players(){
        /*Deliverable 3 for it just executes the setup for 1 vs 1 vs 1 vs 1*/
        main_game_3bots();
    }

    void rules(){

        game_state = 0;
        
        cout<<"So, what is texas holdem?\n"
            <<"simple, all you have to do is make a combo of 5 cards that is better than everyone else\n"
            <<"see that is not so complex is it?\n\n"
            <<"so lets get into the nitty gritty.\n"
            <<"first round, everyone get dealt with 2 cards\n"
            <<"a first round of \"betting\" happens, where you put in your money in the pot\n"
            <<"after this community cards (cards anyone can use) are dealt\n\t"
            <<"one card is dealt, the betting restarts\n\t"
            <<"another card is dealt,betting restarts\n\t"
            <<"another card is dealt,betting restarts\n\t"
            <<"another card is dealt,betting restarts\n\t"
            <<"last card is dealt, final betting happens\n\t"
            <<"in this, if you stopped betting at any round, you can longer bet in the other rounds, as you have\'folded\'\n\t"
            <<"in the end, if you have the best hand, congrats, you win the pot, if you don't have the best hand, well, you lose your bets\n\t"
            <<"first to go broke loses, which automatically means im losing"
            <<"\n\n"
            <<"hope this helps. if it didnt, check this site \"https://www.pokernews.com/poker-rules/texas-holdem.htm\""
            <<"\n\n";
        do{
            cin.clear();
            cout<<"-->";
            cin>>game_state;
        }while(game_state != 1 && game_state != 0);
        change_gamestate_rules();
    }

    void rules_suites(){
        cout<<"\tRoyal Flush - five cards of the same suit, ranked ace through ten\n\t"
            <<"Straight Flush - five cards of the same suit and consecutively ranked\n\t"
            <<"Four of a Kind - four cards of the same rank\n\t"
            <<"Full House - three cards of the same rank and two more cards of the same rank\n\t"
            <<"Flush - any five cards of the same suit\n\t"
            <<"Straight - any five cards consecutively ranked\n\t"
            <<"Three of a Kind - three cards of the same rank\n\t"
            <<"Two Pair - two cards of the same rank and two more cards of the same rank\n\t"
            <<"One Pair - two cards of the same rank\n\t"
            <<"High Card - five unmatched cards, so you only consider the card with the highest rank.\n";
        do{
            cout<<"-->";
            cin>>game_state;
        }while(game_state != 0);

        change_gamestate_rules();
    }

    void change_gamestate_mainmenu(){
        if (game_state == 1){
            choose_number_of_players();
        }
        else if (game_state == 2){
            rules();
        }
    }

    void change_gamestate_rules(){
        if (game_state == 1){
            rules_suites();
        }
        else if (game_state == 0){
            INIT();
        }
    }

    void change_gamestate_start_substate(){  /*Is this efficient? probably not? Do I care? Definetly not.*/
        if (game_state == 1) {

        }
    }

    void INIT(){
        cout<<setw(125)<<"<----WELCOME TO POKER TEXAS HOLD'EM---->\n";
        cout<<"1:Start Game.\n2:Rules.\n-1:Exit.\n";
        do{
            cout<<"-->";
            cin>>game_state;
        }while(game_state < -1 || cin.fail() || game_state > 2);
        change_gamestate_mainmenu();

    }

};

class BOTAI: public POKER {
        public:
            card hand[2];
            int bank;
            //amount of money bot/player starts with
            
            int confidence;
            //confidence level
            
            bool fold = false;
            //tells the bot to fold or not

            bool inthegame = true;
            //this bool defines whether a bot is still in the game, or has lost.

            bool intheround = true;
            //uses same function as inthegame [the playing function] to tell whether a bot is playing the round or not (if it has folded yet, or is continuing)

            void assign_hand(){
                hand[1]=draw_card();
                hand[0]=draw_card();
            }

            void sort_number(card cards[5], const int numofcards)
            {   //subhani, this is inly swapping numbers, not suits, fix !URGENT.
                for (int i = 0; i<numofcards; i++)                        
                {
                    for (int ii = i + 1; ii<numofcards; ii++)
                    {
                        if (cards[i].Number > cards[ii].Number)
                        {
                            int temp = cards[i].Number;
                            cards[i].Number = cards[ii].Number;
                            cards[ii].Number = temp;
                        }
                    }
                }
            }

            int confidencerating(card cards[5],int numofcards) //card cards[5] requires manual entry of each value, also it intrudes on the parent classs' cards array namespace !FIX   
            {
                //opted to use booleans instead of one massive string. why? because i forgot i could use a string system. but eh. <<---!change to string system and move to parent class.
                bool pair = false;
                bool two_pair = false;
                bool three_of_a_kind = false;
                bool straight = false;
                bool flush = false;
                bool full_house = false;
                bool four_of_a_kind = false;
                bool straight_flush = false;
                bool royal_flush = false;

                card sortedarray1[5];
                
                int confidenceperc = 55;

                for (int k; k<numofcards; k++)
                {
                    confidenceperc-=2;
                }
                
                copy (cards, cards+numofcards,sortedarray1);

                sort_number(sortedarray1,numofcards);

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
                    
                        if (sortedarray1[i].Number == sortedarray1[ii].Number )
                        {
                            samecards++;
                        }
                        else
                        {
                            break;
                        }
                    }
                    
                    i+=samecards;
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
                for (int iiiiii ; iiiiii<numofcards ; iiiiii++)
                {
                    if (cards[iiiiii].suit == cards[iiiiii+1].suit)
                    {
                        flush = true;
                    }
                    else
                    {
                        flush = false;
                        break;
                    }
                }
                for (int iiiiiii ; iiiiiii<numofcards; iiiiiii++)
                {
                    if (cards[iiiiiii].Number == cards[iiiiiii+1].Number)
                    {
                        straight = true;
                    }
                    else;
                    {
                        straight = false;
                        break;
                    }

                }
                if (three_of_a_kind && pair)
                {
                    full_house = true;
                }
                if (straight && flush)
                {
                    if ((sortedarray1[1].Number == 10) && (sortedarray1[0].Number == 1))
                    {
                        royal_flush = true;
                    }
                }

                for (int iiiii = 0; iiiii<numofcards; iiiii++ )
                {
                    confidenceperc=-5;
                }
                if (three_of_a_kind)
                {
                    confidenceperc=+15;
                }
                if (four_of_a_kind)
                {
                    confidenceperc=+15;
                }
                if (full_house)
                {
                    confidenceperc=+15;
                }
                if (two_pair)
                {
                    confidenceperc=+15;
                }
                if (flush)
                {
                    for (int j = 0; j<numofcards; j++)
                    {
                        confidenceperc=+2;
                    }
                }
                if (royal_flush)
                {
                    confidenceperc+=50;
                }
                return confidenceperc;
            }

            bool folding(int confidence_level)
            {
                if (confidence_level > 50)
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
            
            bool playing(const int bank, bool fold)
            {
                if ((bank< 5))
                //is this function nearly pointless? yes it is, but id rather not write these 4 lines again and again.
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
    };

