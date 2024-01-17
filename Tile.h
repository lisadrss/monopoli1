//MADDALENA BIONDO

/*La classe base Tile generalizza un oggetto casella. Sono state create due classi derivate di Tile, ovvero LateralTile e CornerTile, rispettivamente per le caselle laterali e angolari. Inoltre da LateralTile sono state derivate tre ulteriori classi:
-EconomicTile
-StandardTile
-LuxuryTile
La distinzione tra i vari tipi di caselle permette di applicare i metodi descritti nel codice per i tre tipi di caselle laterali i cui dati membro (che comprendono il proprietario della casella, il costo dei terreni/case/hotel e il costo dei pernottamenti in una casa o in un hotel) assumono valori diversi.*/

#ifndef Tile_h
#define Tile_h
#include <array>
#include <iostream>
#include <vector>
#include "TileType.h"

class Tile
{
  protected:
    int owner; //proprietario della casella
    int land; //costo del terreno
    int house; //costo della casa
    int hotel; //costo dell'hotel
    int nightHouse; //costo del pernottamento nella casa
    int nightHotel; //costo del pernottamento nell'hotel
    std::array<std::array<int, 4>, 28> playersInTile; //giocatori nella casella
    bool sold = false; //all'inzio la casella non è stata venduta
    bool isHouse = false;
    bool isHotel = false;
    tileType type = tileType::tile;

  public:
    Tile() { }
    Tile(const Tile&); //costruttore di copia
    Tile& operator=(const Tile& a); //overloading operatore di assegnamento

    int getOwner() {return owner;} //restituisce il proprietario della casella
    void updateOwner(int n) {owner = n;} //aggiorna il proprietario
    void updateSold (bool n) {sold = n;} //aggiorna lo stato di vendita del terreno
    void updateHouseSold(bool n) {isHouse = n;} //aggiorna lo stato di vendita della casa
    void updateHotelSold (bool n) {isHotel = n;} //aggiorna lo stato di vendita dell'hotel
    bool isSold() const {return sold;} //per controllare se il terreno è venduto
    bool isHouseSold() const {return isHouse;} //per controllare se la casa è venduta
    bool isHotelSold() const {return isHotel;} //per controllare se l'hotel è venduto
    int getLandPrice() const {return land;} //per prendere il costo del terreno
    int getHousePrice() const {return house;} //per prendere il costo della casa
    int getHotelPrice() const {return hotel;} //per prendere il costo dell'hotel
    int getNightHousePrice() const {return nightHouse;} //per prendere il costo del pernottamento nella casa
    int getNightHotelPrice() const {return nightHotel;} //per prendere il costo del pernottamento nell'hotel
    void insertPlayersTile(int player, int newPosition); //per inserire un giocatore nella casella
    void erasePlayersTile(int player, int oldposition); //per rimuovere un giocatore dalla casella
    void startPlayersTile(); //per inizializzare i giocatori nella casella di partenza
    std::array<std::array<int, 4>, 28> getPlayersInTile() const {return playersInTile;} //per prendere la lista di giocatori nella casella

    virtual tileType getType() const {return type;} //per prendere il tipo di casella
    virtual std::string printTile(); //per stampare la casella
    std::string printHouseOrHotel(); //per stampare la casa o l'hotel nella casella
    std::string printPlayers(int index); //per stampare i giocatori nella casella
};

bool operator==(const Tile& a, const Tile& b); //overloading operatore di uguaglianza
bool operator!=(const Tile& a, const Tile& b); //overloading operatore di disuguaglianza

#endif //Tile_h
