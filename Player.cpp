//LISA DE ROSSI

#include "Player.h"

Player::Player(int player) { numPlayer = player; }

int Player::numEliminated = 0;

Player& Player::operator=(const Player& a)
{
    numPlayer = a.getPlayer();
    budget = a.getBudget();
    human = a.isHuman();
    position = a.getPosition();
    eliminated = a.isEliminated();
    houses = a.getHouses();
    hotels = a.getHotels();
    properties = a.getProperties();
    return *this;
}

//funzione che restituisce il lancio dei dadi
int throwDice() {
  int sumDice = 0;
  sumDice = (1 + std::rand() % 6) + (1 + std::rand() % 6);
  return sumDice;
}

std::array<std::array<int, 2>, 4> whoStarts(std::array<Player *, 4> playerOrder, std::string s, std::ofstream& f) {
  
  std::array<Player, 4> playerList;

  //ognuno tira i dadi per vedere chi parte
  for (int i = 0; i < 4; i++) {
    playerList[i] = Player(i + 1);
    if(s == "human" && i == 0)
    {
      std::cout << "Premere \"Invio\" per lanciare i dadi di partenza" << std::endl;
      std::string enter;
      std::getline(std::cin, enter);
    }
    playerList[i].setFirstDice(throwDice());
    f << "- Giocatore " << playerList[i].getPlayer() << " ha tirato i dadi ottenendo un valore di " << playerList[i].getFirstDice() << std::endl;
    std::cout << "- Giocatore " << playerList[i].getPlayer() << " ha tirato i dadi ottenendo un valore di " << playerList[i].getFirstDice() << std::endl;
  }
  //partita con un umano
  if (s == "human") {
    playerList[0].setHuman(true); // giocatore human impostato come giocatore 1
    playerList[1].setHuman(false);
    playerList[2].setHuman(false);
    playerList[3].setHuman(false);
  }
  //partita con quattro computer
  if (s == "computer") {
    playerList[0].setHuman(false);
    playerList[1].setHuman(false);
    playerList[2].setHuman(false);
    playerList[3].setHuman(false);
  }
  
  // se due o più giocatori tirano lo stesso numero, ripetono il tiro
  std::vector<int> dadi_ripetuti;
  bool check = false;

  int i = 0;
  while (check == false || i < 3) {
    if (check == false) {
      i = 0;
    }
    int j = 0;
    bool humanDice = false;
    //controllo se i giocatori hanno lanciato lo stesso numero
    for (j = i + 1; j < 4; j++) {
      if (playerList[i].getFirstDice() == playerList[j].getFirstDice()) {
        if(i == 0) humanDice = true;
        dadi_ripetuti.push_back(j);
      }
    }
    //si rilanciano i dadi dei giocatori che hanno tirato lo stesso numero
    if (dadi_ripetuti.size() > 0) {
      check = false;
      dadi_ripetuti.push_back(i);
      std::sort(dadi_ripetuti.begin(), dadi_ripetuti.end(), std::greater<int>());
      std::cout << "\n--> i giocatori ";
      for (int k = dadi_ripetuti.size() - 1; k >= 0; k--) {
        std::cout << playerList[dadi_ripetuti.at(k)].getPlayer();
        if(k != 0) std::cout << "-";
        playerList[dadi_ripetuti.at(k)].setFirstDice(throwDice());
        //dadi_ripetuti.pop_back();
      }
      std::cout<< " hanno lo stesso tiro, quindi ritirano i dadi\n\n";
      
      for (int k = dadi_ripetuti.size() - 1; k >= 0; k--) {
      	if(humanDice == true && playerList[dadi_ripetuti.at(k)].isHuman() == true)
        {
          std::cout << "Hai ottenuto lo stesso tiro di un altro giocatore. \nPremere \"Invio\" per lanciare nuovamente i dadi" << std::endl;
          std::string enter;
          std::getline(std::cin, enter);
        }
        f << "- Giocatore " << playerList[dadi_ripetuti.at(k)].getPlayer() << " ha tirato i dadi ottenendo un valore di " << playerList[dadi_ripetuti.at(k)].getFirstDice() << std::endl;
        std::cout << "- Giocatore " << playerList[dadi_ripetuti.at(k)].getPlayer() << " ha tirato i dadi ottenendo un valore di " << playerList[dadi_ripetuti.at(k)].getFirstDice() << std::endl;
        dadi_ripetuti.pop_back();
      }      
     
      dadi_ripetuti.clear();

    } else {
      check = true;
      i++;
    }
  }
  
  // ordino playerList in ordine decrescente in base al tiro dei dadi
  std::vector<int> ordine;
  std::vector<int> indiciOrdinati;
  for (int i = 0; i < 4; i++) {
    ordine.push_back(playerList[i].getFirstDice());
  }
  int count = 0;
  while (count < 4) {
    auto max = std::max_element(ordine.begin(), ordine.end());
    int index_max = 0;
    if (max != ordine.end()) {
      index_max = std::distance(ordine.begin(), max);
    }
    indiciOrdinati.push_back(index_max);
    ordine[index_max] = 0;
    count++;
  }

  //stampo l'ordine di gioco 
  std::cout << "\nL'ordine di gioco è: " << std::endl;
  for (int i = 0; i < 4; i++) {
    playerOrder[i] = &playerList[indiciOrdinati.at(i)];
    std::cout << "--- Giocatore " << indiciOrdinati.at(i) + 1 << std::endl;
  }
  std::cout << std::endl;

  std::array<std::array<int, 2>, 4> order;

  for (int i = 0; i < 4; i++) {
    order[i][0] = playerOrder[i]->getPlayer();
    if (playerOrder[i]->isHuman() == true) {
      order[i][1] = 1;
    } else {
      order[i][1] = 0;
    }
  }
  return order; //restituisco l'array con l'ordine dei giocatori e con informazioni sul tipo di giocatore (umano o computer)
}

int find_value(const std::vector<int> &v, int x) 
{
  for (int i = 0; i < v.size(); i++) {
    if (v[i] == x)
      return i;
  }
  return -1;
}

void removeProperties(std::vector<Tile *> &v) {
  for (int i = 0; i < v.size(); i++) {
    v[i]->updateOwner(0);
    v[i]->updateSold(false);
    v[i]->updateHouseSold(false);
    v[i]->updateHotelSold(false);
  }
}

std::vector<Player *> whoWins(Player *actualPlayersOrder[]) {
  //trovo il giocatore con budget più alto
  int maxBudget = actualPlayersOrder[0]->getBudget();
  for (int i = 1; i < 4; i++) {
    if (actualPlayersOrder[i]->getBudget() > maxBudget) {
      maxBudget = actualPlayersOrder[i]->getBudget();
    }
  }

  std::vector<Player *> winners; //array dei vincitori (può esserecene uno o anche di più se hanno lo stesso budget massimo)

  for (int i = 0; i < 4; i++) {
    if (actualPlayersOrder[i]->getBudget() < maxBudget) {
      actualPlayersOrder[i] = nullptr;
    } else {
      winners.push_back(actualPlayersOrder[i]);
    }
  }
  return winners;
}
