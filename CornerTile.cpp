//MATILDE VANIN

#include "CornerTile.h"

CornerTile::CornerTile(const CornerTile& a)
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

CornerTile& CornerTile::operator=(const CornerTile& a)
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

std::string CornerTile::printTile() 
{
  std::string s = " ";
  return s;
}
