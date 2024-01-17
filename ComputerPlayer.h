//MATILDE VANIN

/*Nel caso del giocatore computer, la funzione è analoga a quella dell'umano tranne che per il fatto che non viene preso alcun input per le opzioni di visualizzazione e i vari acquisti vengono fatti con una probabilità del 25%.*/

#ifndef ComputerPlayer_h
#define ComputerPlayer_h
#include "Player.h"

class ComputerPlayer : public Player
{
  public:	
    ComputerPlayer() { }
    ComputerPlayer(int player);
    void turnToPlay(Board& b, std::ofstream& f, Player* p1, Player* p2, Player* p3, Player* p4); //funzione per il turno di gioco del computer
};
bool probability(); //funzione per calcolare la probabilità del computer di comprare proprietà 

#endif //ComputerPlayer_h
