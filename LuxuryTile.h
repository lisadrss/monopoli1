//LISA DE ROSSI

#ifndef LuxuryTile_h
#define LuxuryTile_h
#include "LateralTile.h"

class LuxuryTile : public LateralTile
{	
  public:
    LuxuryTile();	
    LuxuryTile(const LuxuryTile&); //costruttore di copia
    LuxuryTile& operator=(const LuxuryTile& a); //overloading operatore di assegnamento
    tileType getType() const {return type;}
    std::string printTile();
};

#endif //LuxuryTile_h
