using namespace std;

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

    void choose_number_of_players(){

    }

    void rules(){
        cout<<"RULES???WHERE RULES???NO RULES.\n";
        cout<<"TOO MUCH TYPING FOR RULES, HERE TAKE SUITS {\"suite\",\"Number/JQKA\"}";
        cout<<"";
    }

    void change_gamestate_mainmenu(){
        if (game_state = 1){
            POKER::choose_number_of_players();
        }
        else if (game_state = 2){
            POKER::rules();
        }
        else if (game_state = 0){
            POKER::INIT();
        }
    }

    

    void INIT(){
        cout<<setw(125)<<"<----WELCOME TO POKER TEXAS HOLD'EM---->\n";
        cout<<"1:Start Game.\n2:Rules.\n-1:Exit.\n";
        do{
            cout<<"-->";
            cin>>game_state;
        }while(game_state != 1 || game_state != 2 || game_state != -1 );
        
        POKER::change_gamestate_mainmenu();

    }

    
};

