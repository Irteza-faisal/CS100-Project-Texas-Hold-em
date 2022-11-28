using namespace std;
#include<iostream>

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
    }card;

    card cards[52];

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
        cout<<"SUBHANI WRITE THE RULES HERE PLS.\n";

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

    void test(){
        cout<<game_state;
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

