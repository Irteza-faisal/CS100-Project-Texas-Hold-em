using namespace std;
#include<iostream>
#include<iomanip>
#include<random>
#pragma once

typedef struct {
        int Number;
        char suit;
        bool exists = true;
}card;


class POKER {
    public:
    int Nums[13] = {1,2,3,4,5,6,7,8,9,10,11,12,13}; /*Nums and Suits define the Number of cards per suit (13) A,1,2,3,4,5,6,7,8,9,10,J,Q,K*/
    char suits[4] = {'D','H','C','S'};
    int game_state = 0;
    bool player_playing = false;
    /*int Initial_game_states[3] = {1,2,-1}; Defines initial game states of Start game, Rules, Exit game, 1 starts game, 2 is rules, -1 Exit game*/

    /*int Start_sub_states[3] = {1,2,3}; Substates when in Start game to choose between number of players 1->3 2->4 3->5*/

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

    void is_playing_Perhamps(bool &playing){
        if(playing){
           return; 
        }
        cout<<"";
    }

    void main_game_3bots(){
        BOTAI AI1;
        BOTAI AI2;
        BOTAI AI3;
        bool isgame = true;
        player_playing = true;
        while (isgame && player_playing)
        {
            int player_bank= 500;
            bool isround = true;
            bool isfold = false;
            int pot = 0;
            card dealer[5];
            init_deck();
            while (isround)
            {
                card player_hand[2] = {draw_card(),draw_card()};

                AI1.assign_hand(draw_card(),draw_card());AI2.assign_hand(draw_card(),draw_card());AI3.assign_hand(draw_card(),draw_card());
                
                cout<<"o\t\t"<<pot<<endl;
                cout<<player_hand[0].Number<<" "<<player_hand[0].suit<<endl;
                cout<<player_hand[1].Number<<" "<<player_hand[1].suit<<endl;

                player_choice(isfold,pot,player_bank);
                //Ai choices go here <-- I have no idea what is supposed to go here

                dealer[0]=draw_card();dealer[1]=draw_card();dealer[2]=draw_card(); // this looks disgusting
                cout<<dealer[0].Number<<dealer[0].suit<<" "<<dealer[1].Number<<dealer[1].suit<<" "<<dealer[2].Number<<dealer[2].suit;

                if (!isfold){
                    player_choice(isfold,pot,player_bank); //isfold?isfold? ISFOLD??????? AAAAAAAAAAAAAAAAAAAAA
                }
                //Ai choices go here

                dealer[3]=draw_card();
                cout<<dealer[0].Number<<dealer[0].suit<<" "<<dealer[1].Number<<dealer[1].suit<<" "<<dealer[2].Number<<dealer[2].suit<<" "<<dealer[3].Number<<dealer[3].suit;

                if (!isfold){
                    player_choice(isfold,pot,player_bank);
                }
                //Ai choices go here.    
                

                dealer[4]=draw_card();
                cout<<dealer[0].Number<<dealer[0].suit<<" "<<dealer[1].Number<<dealer[1].suit<<" "<<dealer[2].Number<<dealer[2].suit<<" "<<dealer[3].Number<<dealer[3].suit<<" "<<dealer[4].Number<<dealer[4].suit;

                if (!isfold){
                    player_choice(isfold,pot,player_bank);
                }
                //Ai choices go here.



                 
            }
            is_playing_Perhamps(player_playing);
        }
        
    }

    void player_choice(bool &fold, int &pot, int &player_bank){
        int choice = 0;
        cout<<"What do you wish to do sir?"<<endl;
        cout<<"1-Bet."<<"2-Fold"<<endl;
        do{ 
            cin.clear();
            cout<<"-->";
            cin>>choice;
        }while(choice<=0 || choice >2|| cin.fail());
        
        if (choice == 1){
            pot =+ 10;
            player_bank =- 10;
        } 
        else{
            fold = true;
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

class BOTAI{
        public:
            card hand[2];
            int bank = 5000;
            //amount of money bot/player starts with
            
            int confidence;
            //confidence level
            
            bool fold = false;
            //tells the bot to fold or not

            bool inthegame = true;
            //this bool defines whether a bot is still in the game, or has lost.

            bool intheround = true;
            //uses same function as inthegame [the playing function] to tell whether a bot is playing the round or not (if it has folded yet, or is continuing)

            int numofcards;

            string biggest_threat;

            void assign_hand(card x,card y){
                hand[1]=x;
                hand[0]=y;
            }

            void sort_number(card cards[5], const int numofcards)
            { 
                for (int i = 0; i<numofcards; i++)                        
                {
                    for (int ii = i + 1; ii<numofcards; ii++)
                    {
                        if (cards[i].Number > cards[ii].Number)
                        {
                            card temp = cards[i];
                            cards[i] = cards[ii];
                            cards[ii]  = temp;
                        }
                    }
                }
            }

            void sort_suit(card cards[5], const int numofcards)
            {   
                int x[7] = {99};
                for (int k = 0; k<numofcards; k++)                        
                {
                    switch (cards[k].suit)
                    {
                    case 'D':
                        x[k] = 1;
                        break;
                    case 'H':
                        x[k] = 2;
                        break;
                    case 'S':
                        x[k] = 3;
                        break;
                    case 'C':
                        x[k] = 4;
                        break;
                    default:
                        break;
                    }
                }
                for (int i = 0; i<numofcards; i++)                        
                {
                    for (int ii = i + 1; ii<numofcards; ii++)
                    {
                        if (x[i] >= x[ii])
                        {
                            card temp = cards[i];
                            cards[i]  = cards[ii];
                            cards[ii] = temp;

                            int temp2 = x[i];
                            x[i] = x[ii];
                            x[ii] = temp2;
                        }
                    }
                }  
            }

void confidencerating(card cards_on_table[5]) 
    //cards 1 to 7, where card 0 and 1 are the cards dealt, cards 2, 3, 4, 5, 6, 7 are the cards on the table. Num of cards ensures that confidence level is  only taken with the cards available on the table at that moment.   
    {
        //opted to use booleans instead of one massive string. why? because i forgot i could use a string system. but eh. Im a fool if I dont use the bools
        bool pair = false;
        bool two_pair = false;
        bool three_of_a_kind = false;
        bool straight = false;
        bool flush = false;
        bool full_house = false;
        bool four_of_a_kind = false;
        bool straight_flush = false;
        bool royal_flush = false;

        card cards[7];

        int temparraycounter = 0;
        for (int ivegivenup = 0; ivegivenup<numofcards; ivegivenup++)
        {
            if (ivegivenup<=1)
            {
            cards[ivegivenup] = hand[ivegivenup];
            }
            else
            {
                cards[ivegivenup] = cards_on_table[temparraycounter];
                temparraycounter++;
            }
        }
        
        card sortedarray1[7];
        //only exists to make my poor life easier
        
        card sortedarray2[7];
        //only exists to make my poor life easier(2)
        
        int confidenceperc = 100;

    for (int iiiii = 0; iiiii<numofcards; iiiii++ )
            {
             confidenceperc= (+confidenceperc -7);
            }
        
        copy (cards, cards + numofcards,sortedarray1);
        copy (cards, cards + numofcards,sortedarray2);

        sort_number(sortedarray1,numofcards);
        sort_suit(sortedarray2,numofcards);

        //flush finder 9000
        int flush_val;
        //only exists to check 5 cards, or below 5 cards coz 5 cards needed for flush, 6 and 7 ew.
        
        if (numofcards<=5)
        {
            flush_val = numofcards;
        }
        else
        {
            flush_val = 5;
        }

        for (int counter3 ; counter3<numofcards ; counter3++)
        {
            int samesuit = 0;

            for (int counter3i = counter3+1; counter3i<numofcards; counter3i++)
            {
                if (sortedarray1[counter3].Number == sortedarray1[counter3i].Number )
                {
                    samesuit++;
                }
                else
                {
                    break;
                }
            }
            
            counter3+=samesuit;
            //move away from the same suite cards;
            if (samesuit == flush_val)
            {
                flush = true;
            }
        }
        int samecards = 0;
        //this number tells the number of cards that are the same, which dictates whether the ai has a pair, three of a kind, or four of a kind.
        
        int different_combos[5] = {0};
        //this tell the number of combos that exist (2 pairs, straight, 3 in a row, 4 in a row etc)
        
        int counter2 = 0;
        //this counter tells the actual number of times the loop below is used. its used in inserting values inside the different_combos arrray.
        
        for (int i = 0; i < numofcards; i++)
        //i in this case dictates which card is being used to find a pair of. so cards[0] means finding pairs for card number 1;
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
            //move away from the same pair cards;
            if (samecards!= 0)
            {
                different_combos[counter2] = samecards+1;
                counter2++;
                //increments to the next point in array for same cards.
            }
        }
        if (counter2>0)
        //most programmers (including myself) will hate me for the monstrosity that follows, but believe me I just didnt feel like rewriting the entire code again. debugging moment indeed.
        {
            counter2--;
            //so array counter val actually points at the correct limit.
            for (int iii = 0; iii<=counter2; iii++)
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
                default:
                    break;
                }
            }
            for (int counter4 = 0 ; counter4<numofcards; counter4++)
            {
                int numbersinrow;
                for (int counter4i = counter4+1; counter4i<flush_val; counter4i++)
                {
                    if (cards[counter4].Number == ((cards[counter4i].Number)+1))
                    {
                        numbersinrow++;
                    }
                    else;
                    {
                        break;
                    }
                }
                if (numbersinrow = flush_val)
                {
                    straight = true;
                }
            }

            if (three_of_a_kind && pair)
            {
                full_house = true;
                ;
            }
            if (straight && flush)
            {
                if ((sortedarray1[1].Number == 10) && (sortedarray1[0].Number == 1))
                {
                    royal_flush = true;
            
                }
                else
                {
                    straight_flush = true;
                }
            }  
            if (pair)
            {
                confidenceperc+=10;
            }
            if (three_of_a_kind)
            {
                confidenceperc+=12;
            }
            if (four_of_a_kind)
            {
                confidenceperc+=25;
            }
            if (full_house)
            {
                confidenceperc+=30;
            }
            if (two_pair)
            {
                confidenceperc+=20;
            }
            if (flush)
            {
                for (int j = 0; j<numofcards; j++)
                {
                    confidenceperc+=2;
                }
            }
            if (royal_flush)
            {
                confidenceperc+=50;
            }
        }

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distr1(0,99);
        //adding a bit of randomness yes.
        uniform_int_distribution<> distr2((confidenceperc - (confidenceperc/4)),confidenceperc);
        //MORE SPICE BUT LESS INTESE TO ENSURE BOT DOSENT ALWAYS FOLD.
        
        int number1 = distr1(gen);
        int number2 = distr2(gen);

        confidence = ((number1 + confidenceperc + number2)/3);
    }


    void folding()
    {
        if (confidence > 50)
        {
            fold = false;
        }
        else
        {
            fold = true;
        }
    }

    bool playing(const int bank, bool fold)
    {
        if ((bank< 10))
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

