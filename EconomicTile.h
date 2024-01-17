//MADDALENA BIONDO

#ifndef EconomicTile_h
#define EconomicTile_h
#include "LateralTile.h"

class EconomicTile : public LateralTile
{	
  public:
    EconomicTile();
    EconomicTile(const EconomicTile&); //costruttore di copia
    EconomicTile& operator=(const EconomicTile& a); //overloading operatore di assegnamento
    tileType getType() const {return type;}
    std::string printTile();
};

#endif //EconomicTile_hc
