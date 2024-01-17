//LISA DE ROSSI

/*La classe Board permette di creare il tabellone di gioco. Il tabellone viene visto come un array di dimensione 28 che contiene puntatori di tipo Tile*. Creando un oggetto di tipo Board si va ad allocare dinamicamente la memoria, per questo si è reso necessario l'utilizzo di un distruttore che dealloca la memoria per ogni oggetto Tile. Le caselle laterali del tabellone vengono inizializzate in modo random per assegnare loro il tipo tra economic, standard e luxury. Al contrario, le caselle angolari sono fisse, inclusa ovviamente la casella di partenza P che sarà sempre in alto a sinistra nel tabellone rettangolare.*/

#ifndef Board_h
#define Board_h
#include <array>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <exception>
#include "LateralTile.h"
#include "CornerTile.h"
#include "EconomicTile.h"
#include "StandardTile.h"
#include "LuxuryTile.h"


class Board
{
  static constexpr int sz = 28;
  Tile** elem;
  std::array<Tile*, sz> board;
  std::array<std::string, 28> coordinate = {"A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8",
                        "B8", "C8", "D8", "E8", "F8", "G8", 	
                        "H8", "H7", "H6", "H5", "H4", "H3", "H2", "H1",
                        "G1", "F1", "E1", "D1", "C1", "B1"};  //array con le coordinate delle caselle del tabellone

  public:

    Board(); //costruttore di default
    Tile* operator[] (int n) {return elem[n];} //overloading dell'operatore [], che restituisce un puntatore di tipo Tile
    std::array<std::string, 28> getCoordArray() {return coordinate;}
    std::string getTile(int n) {return coordinate[n];} //per prendere coordinata sul tabellone

    ~Board(); //nella creazione di un nuovo oggetto di tipo Board si allocano i vari tipi di Tile quindi è necessario  
              //l'uso del distruttore per liberare la memoria occupata dai vari oggetti di tipo Tile

};


#endif //Board_h
