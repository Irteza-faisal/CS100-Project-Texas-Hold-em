/*<---Initial Declarations--->*/
#include <iostream>
#include <iomanip>
#include "Poker_lib.h"
using namespace std;

/*<---Main Function--->*/
int main(){
    int game = 0;
    while (game != -1 ){
        cout<<setw(135)<<"------------>Welcome to Texas Hold'em<------------\n";
        cout<<"Enter :\n"
            <<"\t 1:Start Bot match (1P vs 3B)\n"
            <<"\t 2:Rules\n"
            <<"\t-1:Exit\n";
        cout<<"-->";
        cin>>game;    
        while(!validgamechoice(game)){
            cout<<"-->";
            cin>>game;
            cin.clear();
        }

        if (game == 1){
            start_game();
        }
        else if (game == 2){
            show_rules();
        }
        else{
            break;
        }

        

        
    }
    return 0;
}
