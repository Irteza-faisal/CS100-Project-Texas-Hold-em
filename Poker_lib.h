
/*<---Initialise Poker Values.--->*/
void poker_init(){

}

int validgamechoice(int game){
    switch(game){
        case 1 : return 1; break;
        case 2 : return 1; break;
        case -1 : return 1; break;
        default : return 0;
    }
}

void start_game(){

}

void show_rules(){
    int currentstate = 0;
    cout<<"Poker is a game of luck and mental fortitude you have what it takes to determine your enemies chances\nor will you fall to the wayside poor and forgotten like the peasant you are."<<endl;
    cout<<"The rules are simple (for most people), each player is dealt two cards from a deck of 52 unique cards,\n";
    cout<<"each player will then participate in a round of betting, with a min bet of $5 (players start with $1000)\n";
}

