//LISA DE ROSSI

#include "Board.h"

Board::Board() {

  int economy = 8, standard = 10, luxury = 6;
  srand((unsigned int)time(0));

  //inizializzazione di tutte le caselle (le corner sono fisse, le altre sono random)
  //allocazione dinamica della memoria
  for (int i = 0; i < 28; i++) {
    if (i == 0 || i == 7 || i == 14 || i == 21) {
      board[i] = new CornerTile();
      
    } else {
      bool done = false;
      while (!done) {
        int n = std::rand() % 3;
        if (n == 0 && economy > 0) {
          board[i] = new EconomicTile();
          economy--;
          done = true;
        }
        if (n == 1 && standard > 0) {
          board[i] = new StandardTile();
          standard--;
          done = true;
        }
        if (n == 2 && luxury > 0) {
          board[i] = new LuxuryTile();
          luxury--;
          done = true;
        }
      }
    }
  }
  elem = &board[0]; //puntatore al primo elemento dell'oggetto Board
}

Board::~Board() {
  for (int i = 0; i < sz; i++) {
    delete board[i]; // dealloca la memoria per ogni oggetto Tile
  }
}
