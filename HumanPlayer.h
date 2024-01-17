//MADDALENA BIONDO

/*Oltre all'override di turnToPlay per il giocatore umano, in HumanPlayer è implementata la funzione show per visualizzare in output lo stato della partita (vedere il tabellone, la lista delle varie proprietà dei giocatori e i budget di ognuno di essi). Per stampare il tabellone si è utilizzato il metodo printf(...), il quale si è rivelato adeguato per una visualizzazione con formattazione corretta in output.*/

#ifndef HumanPlayer_h
#define HumanPlayer_h
#include <stdio.h>
#include "Player.h"

class HumanPlayer : public Player
{
  public:
    HumanPlayer() { }
    HumanPlayer(int player);	
    void turnToPlay(Board& b, std::ofstream& f, Player* p1, Player* p2, Player* p3, Player* p4); //funzione per il turno di gioco dell'umano
  
    void show(Board& b, Player* p1, Player* p2, Player* p3, Player* p4); //funzione per stampare il tabellone, la lista dei terreni/case/hotel posseduti dai giocatori e i budget dei giocatori    
};

#endif //HumanPlayer_h
