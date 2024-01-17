//MADDALENA BIONDO

#include "EconomicTile.h"

EconomicTile::EconomicTile()
{
  land = 6;
  house = 3;
  hotel = 3;
  nightHouse = 2;
  nightHotel = 4;
  sold = false;
  isHouse = false;
  isHotel = false;
  type = tileType::economic;
}

EconomicTile::EconomicTile(const EconomicTile& a)
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

EconomicTile& EconomicTile::operator=(const EconomicTile& a)
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

std::string EconomicTile::printTile() 
{
  std::string s = "E"; 
  return s;
}

