using namespace std;
#include<iostream>
#include<iomanip>
#include<random>

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> distr(0,51);

typedef struct {
        int Number;
        char suit;
        bool exists = true;
}card;

class BOTAI{
        public:
            card hand[2];
            int bank = 500;
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

            int biggest_threat = 0;

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
                        if (sortedarray1[counter3].suit == sortedarray1[counter3i].suit )
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
                    
                    i= i + samecards;
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
                        if (numbersinrow == flush_val)
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
                uniform_int_distribution<> distr1(30,70);
                //adding a bit of randomness yes.
                uniform_int_distribution<> distr2((confidenceperc - (confidenceperc/4)),confidenceperc);
                //MORE SPICE BUT LESS INTESE TO ENSURE BOT DOSENT ALWAYS FOLD.
                
                int number1 = distr1(gen);
                int number2 = distr2(gen);

                confidence = ((number1 + confidenceperc + number2)/3);

                if (royal_flush) //not related to confidence, just makes code more optimized.
                {biggest_threat = 9;}
                else if (straight_flush)
                {biggest_threat = 8;}
                else if (four_of_a_kind)
                {biggest_threat = 7;}
                else if (full_house)
                {biggest_threat = 6;}
                else if (flush)
                {biggest_threat = 5;}
                else if (straight)
                {biggest_threat = 4;}
                else if (three_of_a_kind)
                {biggest_threat = 3;}
                else if (two_pair)
                {biggest_threat = 2;}
                else if (pair)
                {biggest_threat = 1;}    
            }


            void folding()
            {
                if (confidence > 50 && bank>10)
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


class POKER {
    public:
    int Nums[13] = {1,2,3,4,5,6,7,8,9,10,11,12,13}; /*Nums and Suits define the Number of cards per suit (13) A,2,3,4,5,6,7,8,9,10,J,Q,K*/
    char suits[4] = {'D','H','C','S'};
    int game_state = 0;
    string entity_list_3[4] = {"bot 1","bot 2","bot 3","player"};
    string entity_list_4[5] = {"bot 1","bot 2","bot 3","bot 4","player"};
    string entity_list_5[6] = {"bot 1","bot 2","bot 3","bot 4","bot 5","player"};

    card cards[52];

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
    }

    int player_threat_calc(card cards_on_table[5], card hand[2]) 
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

        for (int ivegivenup = 0; ivegivenup<7; ivegivenup++)
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

    for (int iiiii = 0; iiiii<7; iiiii++ )
            {
             confidenceperc= (+confidenceperc -7);
            }
        
        copy (cards, cards + 7,sortedarray1);
        copy (cards, cards + 7,sortedarray2);

        sort_number(sortedarray1,7);
        sort_suit(sortedarray2,7);

        //flush finder 9000
        int flush_val = 5;
        //only exists to check 5 cards, or below 5 cards coz 5 cards needed for flush
        
        for (int counter3 ; counter3<7; counter3++)
        {
            int samesuit = 0;

            for (int counter3i = counter3+1; counter3i<7; counter3i++)
            {
                if (sortedarray1[counter3].suit == sortedarray1[counter3i].suit)
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
        
        for (int i = 0; i < 7; i++)
        //i in this case dictates which card is being used to find a pair of. so cards[0] means finding pairs for card number 1;
        {
            samecards = 0;

            for (int ii = i+1; ii<7; ii++)
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
            for (int counter4 = 0 ; counter4<7; counter4++)
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
                if (numbersinrow == flush_val)
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
          
        }
        if (royal_flush) 
        {return 9;}
        else if (straight_flush)
        {return 8;}
        else if (four_of_a_kind)
        {return 7;}
        else if (full_house)
        {return 6;}
        else if (flush)
        {return 5;}
        else if (straight)
        {return 4;}
        else if (three_of_a_kind)
        {return 3;}
        else if (two_pair)
        {return 2;}
        else if (pair)
        {return 1;}
        return 0;    
    }
    
    card draw_card(){
        int card_index = distr(gen);
        while (!(cards[card_index].exists)){
            card_index = distr(gen);
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
                cards[n].exists = true;
                n++;
            }
        }
        }
    }

    string who_won(int AI1_threat, int AI2_threat, int AI3_threat, int player_threat)
    {
        int x[4];
        x[0] = AI1_threat;
        x[1] = AI2_threat;
        x[2] = AI3_threat;
        x[3] = player_threat;

        string y[4] = {"bot 1","bot 2","bot 3","player"};
        for (int i = 0; i<4; i++)       
        {
            for (int ii = i + 1; ii<4; ii++)
            {
                if (x[i] <= x[ii])
                {
                    int temp = x[i];
                    x[i] = x[ii];
                    x[ii]  = temp;

                    string temp2 = y[i];
                    y[i] = y[ii];
                    y[ii]  = temp2;
                }
            }
        }
        string ret = y[0];
        return ret;
    }

    void main_game(){
        BOTAI AI1;
        BOTAI AI2;
        BOTAI AI3;
        int player_threat;
        bool isgame = true;
        bool player_playing = true;
        int player_bank= 100;
        while (player_playing)
        {
            bool isround = true;
            bool isfold = false;
            int pot = 0;
            
            card dealer[5];
            
            init_deck();
            while (isround)
            {
                card player_hand[2] = {draw_card(),draw_card()};

                AI1.fold = AI2.fold = AI3.fold = false;
               
                AI1.assign_hand(draw_card(),draw_card());AI2.assign_hand(draw_card(),draw_card());AI3.assign_hand(draw_card(),draw_card());
                
                cout<<"\t\t\t"<<"Pot -> "<<pot<<endl;
                cout<<"Your hand: ";
                cout<<player_hand[0].Number<<player_hand[0].suit<<" "<<player_hand[1].Number<<player_hand[1].suit;
                cout<<"   Your bank: "<<player_bank<<endl;

                player_choice(isfold,pot,player_bank);

                AI1.numofcards = AI2.numofcards = AI3.numofcards = 2;
                
                AI1.confidencerating(dealer);
                AI2.confidencerating(dealer);
                AI3.confidencerating(dealer);
                
                if (!AI1.fold)
                {
                    AI1.folding();
                    if (!AI1.fold)
                    {
                        AI1.bank-=10;
                        pot+=10;
                    }
                }
                if (!AI2.fold)
                {
                    AI2.folding();
                    if (!AI2.fold)
                    {
                        AI2.bank-=10;
                        pot+=10;
                    }
                }
                if (!AI3.fold)
                {
                    AI3.folding();
                    if (!AI3.fold)
                    {
                        AI3.bank-=10;
                        pot+=10;
                    }
                }
                
                dealer[0]=draw_card();dealer[1]=draw_card();dealer[2]=draw_card(); // this looks disgusting

                cout<<"\t\t\t"<<"Pot -> "<<pot<<endl;
                cout<<"\t\tDealer Hand -> "<<dealer[0].Number<<dealer[0].suit<<" "<<dealer[1].Number<<dealer[1].suit<<" "<<dealer[2].Number<<dealer[2].suit<<endl;
                cout<<"Your hand: ";
                cout<<player_hand[0].Number<<player_hand[0].suit<<" "<<player_hand[1].Number<<player_hand[1].suit;
                cout<<"   Your bank: "<<player_bank<<endl;
                
                player_choice(isfold,pot,player_bank);
                
                
                AI1.numofcards = AI2.numofcards = AI3.numofcards = 5;
                
                AI1.confidencerating(dealer);
                AI2.confidencerating(dealer);
                AI3.confidencerating(dealer);
                
                if (!AI1.fold)
                {
                    AI1.folding();
                    if (!AI1.fold)
                    {
                        AI1.bank-=10;
                        pot+=10;
                    }
                }
                if (!AI2.fold)
                {
                    AI2.folding();
                    if (!AI2.fold)
                    {
                        AI2.bank-=10;
                        pot+=10;
                    }
                }
                if (!AI3.fold)
                {
                    AI3.folding();
                    if (!AI3.fold)
                    {
                        AI3.bank-=10;
                        pot+=10;
                    }
                }

                dealer[3]=draw_card();
                cout<<"\t\t\t"<<"Pot -> "<<pot<<endl;
                cout<<"\t\tDealer Hand -> "<<dealer[0].Number<<dealer[0].suit<<" "<<dealer[1].Number<<dealer[1].suit<<" "<<dealer[2].Number<<dealer[2].suit<<" "<<dealer[3].Number<<dealer[3].suit<<endl;
                cout<<"Your hand: ";
                cout<<player_hand[0].Number<<player_hand[0].suit<<" "<<player_hand[1].Number<<player_hand[1].suit;
                cout<<"   Your bank: "<<player_bank<<endl;

                player_choice(isfold,pot,player_bank);

                AI1.numofcards = AI2.numofcards = AI3.numofcards = 6;
                
                AI1.confidencerating(dealer);
                AI2.confidencerating(dealer);
                AI3.confidencerating(dealer);
                
                if (!AI1.fold)
                {
                    AI1.folding();
                    if (!AI1.fold)
                    {
                        AI1.bank-=10;
                        pot+=10;
                    }
                }
                if (!AI2.fold)
                {
                    AI2.folding();
                    if (!AI2.fold)
                    {
                        AI2.bank-=10;
                        pot+=10;
                    }
                }
                if (!AI3.fold)
                {
                    AI3.folding();
                    if (!AI3.fold)
                    {
                        AI3.bank-=10;
                        pot+=10;
                    }
                }

                dealer[4]=draw_card();
                cout<<"\t\t\t"<<"Pot -> "<<pot<<endl;
                cout<<"\t\tDealer Hand -> "<<dealer[0].Number<<dealer[0].suit<<" "<<dealer[1].Number<<dealer[1].suit<<" "<<dealer[2].Number<<dealer[2].suit<<" "<<dealer[3].Number<<dealer[3].suit<<" "<<dealer[4].Number<<dealer[4].suit<<endl;
                cout<<"Your hand: ";
                cout<<player_hand[0].Number<<player_hand[0].suit<<" "<<player_hand[1].Number<<player_hand[1].suit;
                cout<<"   Your bank: "<<player_bank<<endl;
                
                player_choice(isfold,pot,player_bank);
                
                
                
                AI1.numofcards = AI2.numofcards = AI3.numofcards = 7;
                
                AI1.confidencerating(dealer);
                AI2.confidencerating(dealer);
                AI3.confidencerating(dealer);
                
                if (!AI1.fold)
                {
                    AI1.folding();
                    if (!AI1.fold)
                    {
                        AI1.bank-=10;
                        pot+=10;
                    }
                }
                if (!AI2.fold)
                {
                    AI2.folding();
                    if (!AI2.fold)
                    {
                        AI2.bank-=10;
                        pot+=10;
                    }
                }
                if (!AI3.fold)
                {

                    AI3.folding();
                    if (!AI3.fold)
                    {
                        AI3.bank-=10;
                        pot+=10;
                    }
                }

                player_threat = player_threat_calc(dealer,player_hand);
                if (isfold){
                    player_threat= 0;
                }
                cout<<"moneYy\n";
                string winner = who_won(AI1.biggest_threat,AI2.biggest_threat,AI3.biggest_threat,player_threat);

                if (winner == "player"){
                    player_bank = player_bank + pot;
                    cout<<"player won";
                    cout<<"\t\t\t"<<player_hand[0].Number<<player_hand[0].suit<<" "<<player_hand[1].Number<<player_hand[1].suit<<endl;
                }
                else if (winner == "bot 1"){
                    AI1.bank = AI1.bank + pot;
                    cout<<"bot 1 won";
                    cout<<"\t\t\t"<<AI1.hand[0].Number<<AI1.hand[0].suit<<" "<<AI1.hand[1].Number<<AI1.hand[1].suit<<endl;
                }
                else if (winner == "bot 2"){
                    AI2.bank = AI2.bank + pot;
                    cout<<"bot 2 won";
                    cout<<"\t\t\t"<<AI1.hand[0].Number<<AI1.hand[0].suit<<" "<<AI1.hand[1].Number<<AI1.hand[1].suit<<endl;
                }
                else if (winner == "bot 3"){
                    AI2.bank = AI2.bank + pot;
                    cout<<"bot 3 won";
                    cout<<"\t\t\t"<<AI1.hand[0].Number<<AI1.hand[0].suit<<" "<<AI1.hand[1].Number<<AI1.hand[1].suit<<endl;
                }
                isround = false;
            }
            int bank_array[4];
            bank_array[0] = AI1.bank;
            bank_array[1] = AI2.bank;
            bank_array[2] = AI3.bank;
            bank_array[3] = player_bank;
            
            sort(bank_array);
            int zeroes = count_zeroes(bank_array);
            if (zeroes == 3){
                player_playing = false;
                cout<<entity_list_3[3]<<" wins with "<<bank_array[3]<<" in the bank!";
            }
            else if (player_bank < 10){
                cout<<"Game over! You went bankrupt!"<<endl;
                player_playing = false;
            }
        }
        
    }
 
    void sort(int arr[]){
        bool swaps = false;
        int temp; string temp2;
        
        do{
            swaps = false;
            for (int i=0; i<3; i++){
                if (arr[i] > arr[i+1]){
                    temp = arr[i];
                    arr[i] = arr[i+1];
                    arr[i+1] = temp;
                    temp2 = entity_list_3[i];
                    entity_list_3[i] = entity_list_3[i+1];
                    entity_list_3[i] = temp2; 
                    swaps = true;
                }
            }

        }while(swaps);
    }

    int count_zeroes(int arr[]){
        int z = 0;
        for (int i = 0; i<4; i++){
            if (arr[i] == 0){
                z++;
            }
        }
        return z;
    }

    void player_choice(bool &fold, int &pot, int &player_bank){
        int choice = 0;
        if (player_bank < 10){
            fold = true;
            return;
        }
        if (!fold){
            cout<<"What do you wish to do sir?"<<endl;
            cout<<"1-Bet."<<"2-Fold"<<endl;
            do{ 
                cin.clear();
                cout<<"-->";
                cin>>choice;
            }while(choice != 1 && choice != 2);

            if (choice == 2){
                fold = true;
                return;
            }
            pot = pot + 10;
            player_bank = player_bank - 10;
            
        } 
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
            <<"\n\n"
            <<"for rules about suites, type 1. for main page, type 0.\n";
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
            <<"High Card - five unmatched cards, so you only consider the card with the highest rank.\n"
            <<"type 0 when don";
        do{
            cout<<"-->";
            cin>>game_state;
        }while(game_state != 0);

        change_gamestate_rules();
    }

    void change_gamestate_mainmenu(){
        if (game_state == 1){
            main_game();
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

    void INIT(){
        cout<<setw(125)<<"<----WELCOME TO POKER TEXAS HOLD'EM---->\n";
        cout<<"1:Start Game.\n2:Rules.\n-1:Exit.\n";
        do{
            cin.clear();
            cout<<"-->";
            cin>>game_state;
        }while(game_state < -1 || cin.fail() || game_state > 2);
        change_gamestate_mainmenu();

    }

};



