//LISA DE ROSSI

/*La classe base Player contiene le varie funzioni di ritorno per i suoi dati membro (tra cui vi sono il numero del giocatore, il suo budget, la sua posizione nel tabellone ecc.) e le funzioni per aggiornare alcuni di questi dati.
Inoltre, in Player.cpp sono implementate le helper function whoStarts(...) per inizializzare l'ordine dei giocatori e whoWins(...) per decretare il vincitore o i vincitori nel caso in cui la partita deve terminare per aver raggiunto il massimo numero di turni giocabili (si precisa che per un singolo turno si intende che ogni giocatore tira i dadi e gioca).
Le classi derivate di Player (HumanPlayer e ComputerPlayer) implementano l'override della funzione virtuale turnToPlay(...) definendo le possibili azioni di gioco dopo che il giocatore ha tirato il dado; esso una volta arrivato nella nuova casella potrà (se questa è di tipo economic, standard o luxury, mentre se è corner non succede nulla) a seconda della situazione acquistare terreni, costruire una casa, un hotel, oppure pagare un pernottamento a un altro giocatore. Se il giocatore di turno non ha abbastanza soldi per pagare il pernottamento in una casa o in un hotel al giocatore proprietario della casella allora viene eliminato e il suo budget restante viene incassato dal giocatore proprietario della casella in questione.*/

#ifndef Player_h
#define Player_h
#include <cstdlib>
#include <ctime>
#include <array>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "Board.h"

class Player
{	
  protected:
    int numPlayer;
    int budget = 100; //budget iniziale
    bool human; //true se il giocatore è un umano, false se è un computer
    int position = 0; //all'inizio è 0 perché nella casella di partenza
    int firstDice; //valore del primo tiro di dadi
    static int numEliminated; //numero di giocatori eliminati
    bool eliminated = false; //all'inizio impostata a false perché nessuno è eliminato
    std::vector <int> lands; //proprietà possedute dal giocatore
    std::vector <int> houses; //case possedute dal giocatore
    std::vector <int> hotels; //hotel posseduti dal giocatore
    std::vector <Tile*> properties;

  public:
    Player() { } //costruttore di default
    Player(int player); 
    int getPlayer() const {return numPlayer;} //restituisce il numero giocatore
    int getBudget() const {return budget;} //restituisice il budget del giocatore
    void updateBudget(int n) {budget = budget + n;} //aggiorna il budget 
    int getPosition() const {return position;} //restituisce la posizione del giocatore sul tabellone
    std::vector<int> getLands() const {return lands;} //restituisce i terreni possedute dal giocatore
    std::vector<int> getHouses() const {return houses;} //restituisce le case possedute dal giocatore
    std::vector<int> getHotels() const {return hotels;} //restituisce gli hotel posseduti dal giocatore
    std::vector<Tile*> getProperties() const {return properties;} //restituisce le proprietà possedute dal giocatore
    bool isHuman() const {return human;} //per verificare se un giocatore è umano
    void setHuman(bool h) {human = h;} //imposta se un giocatore è umano
    bool isEliminated() const {return eliminated;} //per verificare se un giocatore è stato eliminato
    int getNumEliminated() const {return numEliminated;} //restituisce il numero di giocatori eliminati
    int getFirstDice() const {return firstDice;} //dadi di partenza
    void setFirstDice(int dice) {firstDice = dice;} //dadi di partenza
    virtual void turnToPlay(Board& b, std::ofstream& f, Player* p1, Player* p2, Player* p3, Player* p4) { } //funzione per il turno di gioco
    Player& operator=(const Player& a); //overloading dell'operatore di assegnamento
};

int throwDice(); //funzione per il lancio dei dadi

std::array<std::array<int, 2>, 4> whoStarts(std::array<Player*, 4> playerOrder, std::string s, std::ofstream& f); //funzione per decidere chi inizia per primo
std::vector<Player*> whoWins(Player* actualPlayersOrder[]); //funzione per decidere chi vince

int find_value(const std::vector<int>& v, int x); //per trovare la posizione di un valore in un vettore
void removeProperties (std::vector<Tile*>& v); //per aggiornare i dati membro delle caselle Tile in cui il giocatore eliminato aveva le proprieta' 

#endif //Player_h
