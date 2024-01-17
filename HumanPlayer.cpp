//MADDALENA BIONDO

#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(int player) {
  
  numPlayer = player;
  human = true;
}

void HumanPlayer::turnToPlay(Board &b, std::ofstream &f, Player *p1, Player *p2, Player *p3, Player *p4) {
        
  std::cout << "\nÈ il tuo turno, premere \"Invio\" per lanciare i dadi" << std::endl;

  static int count = 0;
  std::string enter;
  if (count != 0)
  {
    std::getline(std::cin, enter);
  }
  std::getline(std::cin, enter);
  count++;
    
  //eliminazione del giocatore nella casella del turno precedente
  int oldPosition = getPosition();
  Tile *oldTile = b[oldPosition];
  oldTile->erasePlayersTile(this->getPlayer(), oldPosition);

  //giocatore lancia i dadi
  int howManySteps = throwDice();
  f << "- Giocatore " << numPlayer << " ha tirato i dadi ottenendo un valore di " << howManySteps << std::endl;
  std::cout << "- Giocatore " << numPlayer << " ha tirato i dadi ottenendo un valore di " << howManySteps << std::endl;
  if (position + howManySteps > 27) { //il giocatore passa dal via
    budget = budget + 20;
    position = position + howManySteps - 28;
    f << "- Giocatore " << numPlayer << " è passato dal via e ha ritirato 20 fiorini" << std::endl;
    std::cout << "- Giocatore " << numPlayer << " è passato dal via e ha ritirato 20 fiorini" << std::endl;
  } 
  else {
    position = position + howManySteps;
  }

  Tile *currentTile = b[position]; //casella dove si trova attualmente il giocatore
  tileType type = currentTile->getType(); //tipo della casella puntata da currentTile

  currentTile->insertPlayersTile(this->getPlayer(), position); //aggiornamento stato della casella con l'aggiunta del giocatore

  f << "- Giocatore " << numPlayer << " è arrivato alla casella " << b.getTile(position) << std::endl;
  std::cout << "- Giocatore " << numPlayer << " è arrivato alla casella " << b.getTile(position) << std::endl;

  //prendo l'input del giocatore
  bool check = false;
  bool backToPlay = false;
  std::string s;
  while (backToPlay == false) {
    check = false;
    while (check == false) {
      std::cout << std::endl
                << "Digitare: \n"
                   "- \"show\" per visualizzare il tabellone (compresi i budget dei giocatori e le proprietà da essi possedute);\n"
                   "- \"game\" per continuare a giocare."
                << std::endl;
      try {
        std::cin >> s;
        if (s != "show" && s != "game") {
          throw std::invalid_argument("Error");
        } 
        else {
          check = true;
        }
      } 
      catch (std::invalid_argument e) {
        std::cout << "\nInput non corretto." << std::endl;
      }
    }
    if (s == "show") {
      show(b, p1, p2, p3, p4);
      backToPlay = true;
    }
    if (s == "game") {
      std::cout << std::endl;
      backToPlay = true;
    }
  }

  std::string tile;
  if (type == tileType::economic)
    tile = "economic";
  if (type == tileType::standard)
    tile = "standard";
  if (type == tileType::luxury)
    tile = "luxury";

  //caso in cui la casella è angolare (non succede nulla)
  if (type == tileType::corner) {
  
    f << "- Giocatore " << numPlayer << " ha finito il turno" << std::endl;
    std::cout << "- Giocatore " << numPlayer << " ha finito il turno" << std::endl;
  } 
  else { //casella laterale
  
    if (currentTile->isSold() == false) { // caso in cui la casella non è ancora stata venduta
    
      //il giocatore ha abbastanza soldi per comprare il terreno
      if (budget >= currentTile->getLandPrice()) {
      	
        std::cout << "Vuoi comprare la casella " << b.getTile(position) << " di tipo " << tile << " (costo di " << currentTile->getLandPrice() << " fiorini)?" << std::endl;

        bool check = false;
        std::string s;
        while (check == false) {
          std::cout << "Digitare \"S\" se si vuole procedere con l'acquisto, \"N\" altrimenti."
                       "\nPer visualizzare il tabellone (compresi i budget dei giocatori e le proprietà da essi possedute) digitare \"show\"."
                    << std::endl;
          try {
            std::cin >> s;
            if (s != "S" && s != "N" && s != "show") {
              throw std::invalid_argument("Error");
            } 
            else {
               if (s == "show") {
	          show(b, p1, p2, p3, p4);
	       }
	       if (s == "S") { // il giocatore compra il terreno   
		  budget = budget - currentTile->getLandPrice();
		  currentTile->updateSold(true);
                  currentTile->updateOwner(numPlayer);
	          lands.push_back(position); // aggiungo l'acquisto nel vettore delle terre del giocatore                                     
	          properties.push_back(currentTile); // aggiungo l'acquisto nel vettore delle proprietà del giocatore
		  f << "- Giocatore " << numPlayer << " ha acquistato il terreno " << b.getTile(position) << std::endl;
		  std::cout << "- Giocatore " << numPlayer << " ha acquistato il terreno " << b.getTile(position) << std::endl;
		  check = true;
	       }
	       if (s == "N") {
		  check = true;
	       }
            }
          } 
          catch (std::invalid_argument e) {
            std::cout << "\nInput non corretto." << std::endl;
          }         
        }        
      }
      f << "- Giocatore " << numPlayer << " ha finito il turno" << std::endl;
      std::cout << "- Giocatore " << numPlayer << " ha finito il turno" << std::endl;
    }

    else if (currentTile->isSold() == true && currentTile->isHouseSold() == false && currentTile->isHotelSold() == false) { // caso in cui la casella è stata venduta ma non è stata ancora costruita una cas        
      if (currentTile->getOwner() == numPlayer) {  // il giocatore di turno è il proprietario della casella (se non lo è non succede nulla)
      
        //il giocatore ha abbastanza soldi per comprare la casa
        if (budget >= currentTile->getHousePrice()) {
          std::cout << "Vuoi acquistare una casa nella casella " << b.getTile(position) << " di tipo " << tile << " (costo di " << currentTile->getHousePrice() << " fiorini)?" << std::endl;
          
          bool check = false;
          std::string s;
          while (check == false) {
            std::cout << "Digitare \"S\" se si vuole procedere con l'acquisto, \"N\" altrimenti."
                       "\nPer visualizzare il tabellone (compresi i budget dei giocatori e le proprietà da essi possedute) digitare \"show\"."
                      << std::endl;
            try {
              std::cin >> s;
              if (s != "S" && s != "N" && s != "show") {
                throw std::invalid_argument("Error");
              } 
              else {
                if (s == "show") {
                   show(b, p1, p2, p3, p4);              
                }
                if (s == "S") { //il giocatore compra la casa
	           budget = budget - currentTile->getHousePrice();
	           currentTile->updateHouseSold(true);
	           houses.push_back(position); //la casa viene inserita tra le proprietà del giocatore
	           f << "- Giocatore " << numPlayer << " ha costruito una casa sul terreno " << b.getTile(position) << std::endl;
	           std::cout << "- Giocatore " << numPlayer << " ha costruito una casa sul terreno " << b.getTile(position) << std::endl;
	           check = true;
	        }
                if (s == "N") {
	           check = true;
	        }
	      }
            } 
            catch (std::invalid_argument e) {
              std::cout << "\nInput non corretto." << std::endl;
            }
          }         
        }
      }
      f << "- Giocatore " << numPlayer << " ha finito il turno" << std::endl;
      std::cout << "- Giocatore " << numPlayer << " ha finito il turno" << std::endl;
    }

    else if (currentTile->isSold() == true && currentTile->isHouseSold() == true && currentTile->isHotelSold() == false) { // caso in cui la casella ha una casa
      
      if (currentTile->getOwner() != numPlayer) { //il giocatore di turno non è il proprietario
       
        int houseOwner = currentTile->getOwner();
        if (budget >= currentTile->getNightHousePrice()) { // il giocatore ha abbastanza soldi per pagare il pernottamento
          budget = budget - currentTile->getNightHousePrice();

          //trasferimento dei soldi al proprietario della casa
          switch (houseOwner) {
          case (1):
            p1->updateBudget(currentTile->getNightHousePrice());
            break;
          case (2):
            p2->updateBudget(currentTile->getNightHousePrice());
            break;
          case (3):
            p3->updateBudget(currentTile->getNightHousePrice());
            break;
          case (4):
            p4->updateBudget(currentTile->getNightHousePrice());
            break;
          }
          f << "- Giocatore " << numPlayer << " ha pagato " << currentTile->getNightHousePrice() << " fiorini a giocatore " << houseOwner << " per pernottamento nella casa della casella " << b.getTile(position) << std::endl;
          std::cout << "- Giocatore " << numPlayer << " ha pagato " << currentTile->getNightHousePrice() << " fiorini a giocatore " << houseOwner << " per pernottamento nella casa della casella " << b.getTile(position) << std::endl;
          std::cout << "- Giocatore " << numPlayer << " ha pernottato in una casa in una casella di tipo " << tile << std::endl; 
       } 
          
       else { // il giocatore non ha abbastanza fiorini per pagare il pernottamento, viene eliminato e il suo budget viene trasferito al proprietario della casa

	 eliminated = true;
	 lands.clear();
	 houses.clear();   //tutte le proprietà vengono azzerate 
	 hotels.clear();
	 removeProperties(properties);
	 currentTile->erasePlayersTile(this->getPlayer(), position); //giocatore cancellato dalla casella 
	 numEliminated++; //aumento il numero di giocatori eliminati

	 std::cout << "- Giocatore " << numPlayer << " non ha abbastanza fiorini per pagare il pernottamento nella casa della casella " << b.getTile(position) << std::endl;
	 std::cout << "- Giocatore " << numPlayer << " paga il giocatore " << houseOwner << " con tutto il suo budget di " << budget << " fiorini" << std::endl;
	 f << "- Giocatore " << numPlayer << " è stato eliminato" << std::endl;
	 std::cout << "- Giocatore " << numPlayer << " è stato eliminato" << std::endl;

	 //trasferimento dei soldi al proprietario della casa
	 switch (houseOwner) {
	 case (1):
           p1->updateBudget(budget);
	   break;
	case (2):
	   p2->updateBudget(budget);
	   break;
	case (3):
	   p3->updateBudget(budget);
	   break;
	case (4):
	   p4->updateBudget(budget);
	   break;
	}
      } 
    }
    else { // il giocatore è il proprietario della casella e può scegliere se costruire l'hotel
 
        //il giocatore ha abbastanza soldi per costruire l'hotel
        if (budget >= currentTile->getHotelPrice()) {
          std::cout << "Vuoi migliorare la casa in albergo nella casella " << b.getTile(position) << " di tipo " << tile << " (costo di " << currentTile->getHotelPrice() << " fiorini)?" <<  std::endl;
                    
          bool check = false;
          std::string s;
          while (check == false) {
            std::cout << "Digitare \"S\" se si vuole procedere con l'acquisto, \"N\" altrimenti."
                       "\nPer visualizzare il tabellone (compresi i budget dei giocatori e le proprietà da essi possedute) digitare \"show\"."
                      << std::endl;
            try {
              std::cin >> s;
              if (s != "S" && s != "N" && s != "show") {
                throw std::invalid_argument("Error");
              } 
              else {
              	if (s == "show") {
                   show(b, p1, p2, p3, p4);
	        }
                if (s == "S") { //il giocatore costruisce l'hotel
	           budget = budget - currentTile->getHotelPrice();
		   currentTile->updateHouseSold(false); //la casa viene rimossa
		   currentTile->updateHotelSold(true);
		   int x = find_value(houses, position);
		   houses.erase(houses.begin() + x); //casa rimossa dalle proprietà del giocatore
		   hotels.push_back(position); //hotel inserito nelle proprietà del giocatore
		   f << "- Giocatore " << numPlayer << " ha migliorato una casa in albergo sul terreno " << b.getTile(position) << std::endl;
		   std::cout << "- Giocatore " << numPlayer << " ha migliorato una casa in albergo sul terreno " << b.getTile(position) << std::endl;
		   check = true;
		}
	        if (s == "N") {
		   check = true;
		}
	      }
            } 
            catch (std::invalid_argument e) {
              std::cout << "\nInput non corretto." << std::endl;
            }           
          }         
        }
      }
      f << "- Giocatore " << numPlayer << " ha finito il turno" << std::endl;
      std::cout << "- Giocatore " << numPlayer << " ha finito il turno" << std::endl;
    }

    else if (currentTile->isSold() == true && currentTile->isHouseSold() == false && currentTile->isHotelSold() == true) { // caso in cui la casella ha un hotel
       
      //se il giocatore di turno non è il proprietario deve pagare il pernottamento
      if (numPlayer != currentTile->getOwner()) {
        int hotelOwner = currentTile->getOwner();
        if (budget >= currentTile->getNightHotelPrice()) { //il giocatore ha abbastanza fiorini per pagare il pernottamento
          
          budget = budget - currentTile->getNightHotelPrice();

	  //trasferimento dei soldi al proprietario dell'hotel
          switch (hotelOwner) {
          case (1):
            p1->updateBudget(currentTile->getNightHotelPrice());
            break;
          case (2):
            p2->updateBudget(currentTile->getNightHotelPrice());
            break;
          case (3):
            p3->updateBudget(currentTile->getNightHotelPrice());
            break;
          case (4):
            p4->updateBudget(currentTile->getNightHotelPrice());
            break;
          }
          f << "- Giocatore " << numPlayer << " ha pagato " << currentTile->getNightHotelPrice() << " fiorini a giocatore " << hotelOwner << " per pernottamento nell'hotel della casella " << b.getTile(position) << std::endl;
          std::cout << "- Giocatore " << numPlayer << " ha pagato " << currentTile->getNightHotelPrice() << " fiorini a giocatore " << hotelOwner << " per pernottamento nell'hotel della casella " << b.getTile(position) << std::endl;
          std::cout << "- Giocatore " << numPlayer << " ha pernottato in un hotel in una casella di tipo " << tile << std::endl; 
        } 
        else {  // il giocatore non ha abbastanza fiorini per pagare il pernottamento, viene eliminato e il suo budget viene trasferito al proprietario dell'hotel
          
          eliminated = true;
          lands.clear();
          houses.clear();    //azzero tutte le proprietà del giocatore
          hotels.clear();
          removeProperties(properties);
          currentTile->erasePlayersTile(this->getPlayer(), position); //giocatore cancellato dalla casella
          numEliminated++; //aumento il numero di giocatori eliminati

          std::cout << "- Giocatore " << numPlayer << " non ha abbastanza fiorini per pagare il pernottamento nell'hotel della casella " << b.getTile(position) << std::endl;
          std::cout << "- Giocatore " << numPlayer << " paga il giocatore " << hotelOwner << " con tutto il suo budget di " << budget << " fiorini" << std::endl;
          f << "- Giocatore " << numPlayer << " è stato eliminato" << std::endl; 
          std::cout << "- Giocatore " << numPlayer << " è stato eliminato" << std::endl;

	  //trasferimento dei soldi al proprietario dell'hotel
          switch (hotelOwner) {
          case (1):
            p1->updateBudget(budget);
            break;
          case (2):
            p2->updateBudget(budget);
            break;
          case (3):
            p3->updateBudget(budget);
            break;
          case (4):
            p4->updateBudget(budget);
            break;
          }
        }
      }
      f << "- Giocatore " << numPlayer << " ha finito il turno" << std::endl;
      std::cout << "- Giocatore " << numPlayer << " ha finito il turno" << std::endl;
    }
  }
}

void HumanPlayer::show(Board &b, Player *p1, Player *p2, Player *p3, Player *p4) {
  
  std::cout << "-----------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
  std::cout << "\nVisualizzazione del tabellone:" << std::endl << std::endl;

  //stampo la prima riga
  printf("%11s%-6s", "", "1");
  printf("%11s%-6s", "", "2");
  printf("%11s%-6s", "", "3");
  printf("%11s%-6s", "", "4");
  printf("%11s%-6s", "", "5");
  printf("%11s%-6s", "", "6");
  printf("%11s%-6s", "", "7");
  printf("%11s%-6s\n\n", "", "8");

  //stampo il resto delle righe, le quali contengono la lettera corrispondente (dalla A alla H), e per ogni casella presente sulla riga sono stampati il tipo della casella, * o ^ a seconda che ci sia una casa o un albergo, e i giocatori sulla casella
  printf("%-5s%-2s%-2s%-7s%1s%5s", "A", "|", "P", (b[0]->printPlayers(0)).c_str(), "|", "");
  printf("%-2s%1s%1s%-7s%1s%5s", "|", (b[1]->printTile()).c_str(), (b[1]->printHouseOrHotel()).c_str(), (b[1]->printPlayers(1)).c_str(), "|", "");
  printf("%-2s%1s%1s%-7s%1s%5s", "|", (b[2]->printTile()).c_str(), (b[2]->printHouseOrHotel()).c_str(), (b[2]->printPlayers(2)).c_str(), "|", "");
  printf("%-2s%1s%1s%-7s%1s%5s", "|", (b[3]->printTile()).c_str(), (b[3]->printHouseOrHotel()).c_str(), (b[3]->printPlayers(3)).c_str(), "|", "");
  printf("%-2s%1s%1s%-7s%1s%5s", "|", (b[4]->printTile()).c_str(), (b[4]->printHouseOrHotel()).c_str(), (b[4]->printPlayers(4)).c_str(), "|", "");
  printf("%-2s%1s%1s%-7s%1s%5s", "|", (b[5]->printTile()).c_str(), (b[5]->printHouseOrHotel()).c_str(), (b[5]->printPlayers(5)).c_str(), "|", "");
  printf("%-2s%1s%1s%-7s%1s%5s", "|", (b[6]->printTile()).c_str(), (b[6]->printHouseOrHotel()).c_str(), (b[6]->printPlayers(6)).c_str(), "|", "");
  printf("%-2s%-2s%-7s%1s\n", "|", (b[7]->printTile()).c_str(), (b[7]->printPlayers(7)).c_str(), "|");
  printf("%-5s%-2s%1s%1s%-7s%1s%107s", "B", "|", (b[27]->printTile()).c_str(), (b[27]->printHouseOrHotel()).c_str(), (b[27]->printPlayers(27)).c_str(), "|", " ");
  printf("%-2s%1s%1s%-7s%1s\n", "|", (b[8]->printTile()).c_str(), (b[8]->printHouseOrHotel()).c_str(), (b[8]->printPlayers(8)).c_str(), "|");
  printf("%-5s%-2s%1s%1s%-7s%1s%107s", "C", "|", (b[26]->printTile()).c_str(), (b[26]->printHouseOrHotel()).c_str(), (b[26]->printPlayers(26)).c_str(), "|", " ");
  printf("%-2s%1s%1s%-7s%1s\n", "|", (b[9]->printTile()).c_str(), (b[9]->printHouseOrHotel()).c_str(), (b[9]->printPlayers(9)).c_str(), "|");
  printf("%-5s%-2s%1s%1s%-7s%1s%107s", "D", "|", (b[25]->printTile()).c_str(), (b[25]->printHouseOrHotel()).c_str(), (b[25]->printPlayers(25)).c_str(), "|", " ");
  printf("%-2s%1s%1s%-7s%1s\n", "|", (b[10]->printTile()).c_str(), (b[10]->printHouseOrHotel()).c_str(), (b[10]->printPlayers(10)).c_str(), "|");
  printf("%-5s%-2s%1s%1s%-7s%1s%107s", "E", "|", (b[24]->printTile()).c_str(), (b[24]->printHouseOrHotel()).c_str(), (b[24]->printPlayers(24)).c_str(), "|", " ");
  printf("%-2s%1s%1s%-7s%1s\n", "|", (b[11]->printTile()).c_str(), (b[11]->printHouseOrHotel()).c_str(), (b[11]->printPlayers(11)).c_str(), "|");
  printf("%-5s%-2s%1s%1s%-7s%1s%107s", "F", "|", (b[23]->printTile()).c_str(), (b[23]->printHouseOrHotel()).c_str(), (b[23]->printPlayers(23)).c_str(), "|", " ");
  printf("%-2s%1s%1s%-7s%1s\n", "|", (b[12]->printTile()).c_str(), (b[12]->printHouseOrHotel()).c_str(), (b[12]->printPlayers(12)).c_str(), "|");
  printf("%-5s%-2s%1s%1s%-7s%1s%107s", "G", "|", (b[22]->printTile()).c_str(), (b[22]->printHouseOrHotel()).c_str(), (b[22]->printPlayers(22)).c_str(), "|", " ");
  printf("%-2s%1s%1s%-7s%1s\n", "|", (b[13]->printTile()).c_str(), (b[13]->printHouseOrHotel()).c_str(), (b[13]->printPlayers(13)).c_str(), "|");
  printf("%-5s%-2s%-2s%-7s%1s%5s", "H", "|", (b[21]->printTile()).c_str(), (b[21]->printPlayers(21)).c_str(), "|", "");
  printf("%-2s%1s%1s%-7s%1s%5s", "|", (b[20]->printTile()).c_str(), (b[20]->printHouseOrHotel()).c_str(), (b[20]->printPlayers(20)).c_str(), "|", "");
  printf("%-2s%1s%1s%-7s%1s%5s", "|", (b[19]->printTile()).c_str(), (b[19]->printHouseOrHotel()).c_str(), (b[19]->printPlayers(19)).c_str(), "|", "");
  printf("%-2s%1s%1s%-7s%1s%5s", "|", (b[18]->printTile()).c_str(), (b[18]->printHouseOrHotel()).c_str(), (b[18]->printPlayers(18)).c_str(), "|", "");
  printf("%-2s%1s%1s%-7s%1s%5s", "|", (b[17]->printTile()).c_str(), (b[17]->printHouseOrHotel()).c_str(), (b[17]->printPlayers(17)).c_str(), "|", "");
  printf("%-2s%1s%1s%-7s%1s%5s", "|", (b[16]->printTile()).c_str(), (b[16]->printHouseOrHotel()).c_str(), (b[16]->printPlayers(16)).c_str(), "|", "");
  printf("%-2s%1s%1s%-7s%1s%5s", "|", (b[15]->printTile()).c_str(), (b[15]->printHouseOrHotel()).c_str(), (b[15]->printPlayers(15)).c_str(), "|", "");
  printf("%-2s%-2s%-7s%1s\n", "|", (b[14]->printTile()).c_str(), (b[14]->printPlayers(14)).c_str(), "|");
  
  std::cout << std::endl;
  
  std::cout << "-----------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
  
  std::cout << "\nLista dei terreni/case/alberghi posseduti da ogni giocatore:\n\n";

  //i giocatori vengono ordinati da 1 a 4
  std::array<Player *, 4> order = {p1, p2, p3, p4};
  std::sort(order.begin(), order.end(), [](Player *a, Player *b) {return a->getPlayer() < b->getPlayer();});

  //per ogni giocatore viene stampata la lista delle sue proprietà (terreni, case e hotel)
  for (int i = 0; i < 4; i++) {
    std::cout << "Giocatore " << order[i]->getPlayer() << ": " << std::endl;
    std::cout << "\tTerreni: ";
    for (int j = 0; j < order[i]->getLands().size(); j++) {
      std::cout << b.getTile(order[i]->getLands().at(j)) << ", ";
    }
    std::cout << "\b\b " << std::endl;
    std::cout << "\tCase: ";
    for (int j = 0; j < order[i]->getHouses().size(); j++) {
      std::cout << b.getTile(order[i]->getHouses().at(j)) << ", ";
    }
    std::cout << "\b\b " << std::endl;
    std::cout << "\tAlberghi: ";
    for (int j = 0; j < order[i]->getHotels().size(); j++) {
      std::cout << b.getTile(order[i]->getHotels().at(j)) << ", ";
    }
    std::cout << "\b\b " << std::endl;
  }
  
  std::cout << std::endl;
  
  std::cout << "-----------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
  
  std::cout << "\nBudget attuali dei giocatori:\n\n";
  
  //per ogni giocatore stampo il suo budget in fiorini; se il giocatore è eliminato ciò viene fatto presente
  for (int i = 0; i < 4; i++) {
    if (order[i]->isEliminated() == true) {
      std::cout << "Giocatore " << order[i]->getPlayer() << " è stato eliminato." << std::endl;
    } 
    else {
      std::cout << "Giocatore " << order[i]->getPlayer() << " possiede " << order[i]->getBudget() << " fiorini." << std::endl;
    }
  }

  std::cout << std::endl << "-----------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
}
