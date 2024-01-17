//LLISA DE ROSSI

#include "LuxuryTile.h"

LuxuryTile::LuxuryTile()
{
  land = 20;
  house = 10;
  hotel = 10;
  nightHouse = 7;
  nightHotel = 14;
  sold = false;
  isHouse = false;
  isHotel = false;
  type = tileType::luxury;

}

LuxuryTile::LuxuryTile(const LuxuryTile& a)
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

LuxuryTile& LuxuryTile::operator=(const LuxuryTile& a)
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

std::string LuxuryTile::printTile() 
{
  std::string s = "L";
  return s;
}

