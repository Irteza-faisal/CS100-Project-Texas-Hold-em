using namespace std;

class POKER {
    public:
    int Nums = [1,2,3,4,5,6,7,8,9,10,11,12,13]; /*Nums and Suits define the Number of cards per suit (13) A,1,2,3,4,5,6,7,8,9,10,J,Q,K*/
    char suits = ['D','H','C','S'];

    int Initial_game_states = [1,2,-1]; /*Defines initial game states of Start game, Rules, Exit game, 1 starts game, 2 is rules, -1 Exit game*/

    int Start_sub_states = [1,2,3] /*Substates when in Start game to choose between number of players 1->3 2->4 3->5*/

    typedef struct {
        int Number;
        char suit;
    }card;

    card cards[52];

    void init_deck(){
        int n = 0;
        while (n != 52){
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 13){
                cards[n].Number = Nums[j];
                cards[n].suit = suits[i];
                n++;
            }
        }
        }
    }
    
};

