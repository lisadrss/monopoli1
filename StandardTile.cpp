//MATILDE VANINV

#include "StandardTile.h"

StandardTile::StandardTile()
{
  land = 10;
  house = 5;
  hotel = 5;
  nightHouse = 4;
  nightHotel = 8;
  sold = false;
  isHouse = false;
  isHotel = false;
  type = tileType::standard;
}

StandardTile::StandardTile(const StandardTile& a)
{
  land = a.land;
  house = a.house;
  hotel = a.hotel;
  nightHouse = a.nightHouse;
  nightHotel = a.nightHotel;
  sold = a.sold;
  isHouse = a.isHouse;
  isHotel = a.isHotel;
}

StandardTile& StandardTile::operator=(const StandardTile& a)
{
  if (a != *this) 
  {
    land = a.land;
    house = a.house;
      hotel = a.hotel;
      nightHouse = a.nightHouse;
      nightHotel = a.nightHotel;
      sold = a.sold;
      isHouse = a.isHouse;
      isHotel = a.isHotel;
    type = a.type;
  }
    return *this;
}

std::string StandardTile::printTile() 
{
  std::string s = "S";
  return s;
}
