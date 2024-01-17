//MATILDE VANIN

#include "Tile.h"

void Tile::insertPlayersTile(int player, int newPosition)
{
  playersInTile[newPosition][player-1] = 1;
}

void Tile::erasePlayersTile(int player, int oldPosition)
{
  playersInTile[oldPosition][player-1] = 0;
}

void Tile::startPlayersTile()
{
  for (int i = 0; i < 4; i++)
  {
    playersInTile[0][i] = 1;
  } 
}

std::string Tile::printHouseOrHotel()
{
  std::string s;
  if (isHouseSold() == true)
  { 
    s = "*";
  }
  else if (isHotelSold() == true)
  {
    s = "^";
  }
  return s;
}

std::string Tile::printPlayers(int index)
{
  std::vector<int> players;
  for (int i = 0; i < 4; i++)
  {
    if (playersInTile[index][i] == 1)
    {
      players.push_back(i+1);
    }
  }
  std::string s ;
  for (int i = 0; i < players.size(); i++)
  {
    s = s + std::to_string(players[i]) + "-";
  }
  if (s.size()>0)
  {
      s.erase (s.end()-1);
      players.clear();
  }
  return s;
}

Tile::Tile(const Tile& a)
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

Tile& Tile::operator=(const Tile& a)
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
  }
    return *this;
}

std::string Tile::printTile() 
{
  std::string s = "T";
  return s;
}

bool operator==(const Tile& a, const Tile& b)
{
  if (a.getLandPrice() == b.getLandPrice() &&
    a.getHousePrice() == b.getHousePrice() &&
    a.getHotelPrice() == b.getHotelPrice() &&
    a.getNightHousePrice() == b.getNightHousePrice() &&
    a.getNightHotelPrice() == b.getNightHotelPrice())
  {
     return true;
  }
  return false;
}

bool operator!=(const Tile& a, const Tile& b)
{
   return (!(a == b)); 
}
