//MATILDE VANIN

#ifndef CornerTile_h
#define CornerTile_h
#include "Tile.h"

class CornerTile : public Tile
{
  tileType type = tileType::corner;

    public:
      CornerTile() { }
      CornerTile(const CornerTile&); //costruttore di copia
      CornerTile& operator=(const CornerTile& a); //overloading operatore di assegnamento
      tileType getType() const {return type;} 
      std::string printTile();

};

#endif //CornerTile_h
