//LISA DE ROSSI

#ifndef LateralTile_h
#define LateralTile_h
#include "Tile.h"

class LateralTile : public Tile
{
  protected: 

    tileType type = tileType::lateral;
    LateralTile() { }
};

#endif //LateralTile_h
