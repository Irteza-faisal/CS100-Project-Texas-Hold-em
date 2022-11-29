using namespace std;
#include<iostream>
#include<iomanip>
#include<random>

class POKER {
    public:
    int Nums[13] = {1,2,3,4,5,6,7,8,9,10,11,12,13}; /*Nums and Suits define the Number of cards per suit (13) A,1,2,3,4,5,6,7,8,9,10,J,Q,K*/
    char suits[4] = {'D','H','C','S'};
    int game_state = 0;
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

    void main_game_3bots(){
        
    }

    void choose_number_of_players(){
        /*Deliverable 3 for it just executes the setup for 1 vs 1 vs 1 vs 1*/
        main_game_3bots();
    }

    void rules(){

        game_state = 0;
        cout<<"RULES???WHERE RULES???NO RULES.\n";
        cout<<"TOO MUCH TYPING FOR RULES, HERE TAKE SUITS {\"suite\",\"Number/JQKA\"}\n";
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
            <<"in this, if you stopped betting at any round, you can longer bet in the other rounds, as you have\'folded\'\n"
            <<"in the end, if you have the best hand, congrats, you win the pot, if you don't have the best hand, well, you lose your bets\n"
            <<"first to go broke loses, which automatically means im losing"
            <<"\n\n"
            <<"so hands, in order of power (descending):\n"
            <<"Royal Flush — five cards of the same suit, ranked ace through ten\n\t"
            <<"Straight Flush — five cards of the same suit and consecutively ranked\n\t"
            <<"Four of a Kind — four cards of the same rank\n\t"
            <<"Full House — three cards of the same rank and two more cards of the same rank\n\t"
            <<"Flush — any five cards of the same suit\n\t"
            <<"Straight — any five cards consecutively ranked\n\t"
            <<"Three of a Kind — three cards of the same rank\n\t"
            <<"Two Pair — two cards of the same rank and two more cards of the same rank\n\t"
            <<"One Pair — two cards of the same rank\n\t"
            <<"High Card — five unmatched cards\n"
            <<"\n\n"
            <<"hope this helps. if it didnt, check this site \"https://www.pokernews.com/poker-rules/texas-holdem.htm\"";
        do{
            cout<<"-->";
            cin>>game_state;
        }while(game_state != 1 || game_state != 0);
        change_gamestate_rules();
    }

    void rules_suites(){
        cout<<"SUITES LIKH DO IDHAR MERI JAAN\n";
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

    class BOTAI {
        public:
            card hand[2];
            int confidence;


    };
};

