//MATILDE VANIN

#ifndef StandardTile_h
#define StandardTile_h
#include "LateralTile.h"

class StandardTile : public LateralTile
{	
 public:
  StandardTile();
  StandardTile(const StandardTile&); //costruttore di copia
  StandardTile& operator=(const StandardTile& a); //overloading operatore di assegnamento
  tileType getType() const {return type;}
  std::string printTile();
};

#endif //StandardTile_h
