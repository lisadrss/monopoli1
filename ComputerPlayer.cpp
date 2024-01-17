//MATILDE VANIN

#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer(int player)
{
  numPlayer = player;
  human = false;
}

void ComputerPlayer::turnToPlay(Board& b, std::ofstream& f, Player* p1, Player* p2, Player* p3, Player* p4)
{
    //eliminazione del giocatore nella casella del turno precedente
    int oldPosition = getPosition();
    Tile* oldTile = b[oldPosition];
    oldTile->erasePlayersTile(this->getPlayer(), oldPosition);

    //giocatore lancia i dadi
    int new_p = throwDice();
    f << "- Giocatore " << numPlayer << " ha tirato i dadi ottenendo un valore di " << new_p << "\n";
    std::cout << "- Giocatore " << numPlayer << " ha tirato i dadi ottenendo una valore di " << new_p << "\n";
    if (((position + new_p) > 27)) //se il tiro di dadi fa superare la casella di partenza
    {
        budget = budget + 20;
        f << "- Giocatore " << numPlayer << " è passato dal via e ha ritirato 20 fiorini\n";
        std::cout << "- Giocatore " << numPlayer << " è passato dal via e ha ritirato 20 fiorini\n";
        position = (position + new_p) - 28;
    }
    else
    {
        position = position + new_p;
    }
    f << "- Giocatore " << numPlayer << " è arrivato alla casella " << b.getTile(position) << std::endl;
    std::cout<<"- Giocatore " << numPlayer<< " è arrivato alla casella " << b.getTile(position) << std::endl;
    Tile* element = b[position]; //casella dove si trova il giocatore (tipo Tile)
    tileType type = element->getType(); //casella dove si trova il giocatore (tipo tileType)
    element->insertPlayersTile(this->getPlayer(), position); //aggiornamento stato della casella con l'aggiunta del giocatore

    std::string tile;
    if (type == tileType::economic) tile = "economic";
    if (type == tileType::standard) tile = "standard";
    if (type == tileType::luxury) tile = "luxury";	
  
    if ((type == tileType::economic) || (type == tileType::standard) || (type == tileType::luxury))  //se la casella è laterale
    {
        if (element->getOwner() == 0) //se la casella non è proprieta' di nessuno
        {
            if (budget >= element->getLandPrice()) //se il giocatore ha abbastanza fiorini per comprare la casella
            {
                int p = probability();
                if (p == true)
                {
                    budget = budget - element->getLandPrice();
                    element->updateOwner(numPlayer);
                    element->updateSold(true);
                    lands.push_back(position); //aggiorno l'array che contiene le terre del giocatore
                    properties.push_back(element); //aggiornamento delle proprietà del giocatore
                    f << "- Giocatore " << numPlayer << " ha acquistato il terreno " << b.getTile(position) << std::endl;
                    std::cout << "- Giocatore " << numPlayer << " ha acquistato il terreno " << b.getTile(position) << std::endl;
                    std::cout << "- Il terreno acquistato è di tipo " << tile << " ed è costato " << element->getLandPrice() << " fiorini" << std::endl; 
                }
            }
            f << "- Giocatore "<< numPlayer << " ha finito il turno" << std::endl;
            std::cout << "- Giocatore " << numPlayer << " ha finito il turno" << std::endl;
        }
        else
        {
            if ((element->getOwner() == numPlayer)) //se la casella e' di proprietà del giocatore stesso
            {
                if (element->isSold() == true && element->isHouseSold() == false && element->isHotelSold() == false) //controllo se possiede il terreno
                {
                    if (budget >= element->getHousePrice()) //e quindi controllo se può comprare la casa
                    {
                        int p = probability();
                        if (p == true)
                        {
                            budget = budget - element->getHousePrice();
                            element->updateHouseSold(true);
                            houses.push_back(position); //aggiornamento delle case di proprietà del giocatore
                            f << "- Giocatore " << numPlayer << " ha costruito una casa sul terreno " <<  b.getTile(position) << std::endl;
                            std::cout << "- Giocatore " << numPlayer << " ha costruito una casa sul terreno " << 
 b.getTile(position) << std::endl;
                             std::cout << "- La casa acquistata è di tipo " << tile << " ed è costata " << element->getHousePrice() << " fiorini" << std::endl; ;
                        }
                    }
                }
                else
                {
                    if (element->isSold() == true && element->isHouseSold() == true && element->isHotelSold() == false)//se invece possiede già la casa
                    {
                        if (budget >= element->getHotelPrice()) //controllo se può acquistare l'hotel
                        {
                            int p = probability();
                            if (p == true)
                            {
                                budget = budget - element->getHotelPrice();
                                element->updateHotelSold(true);
                                element->updateHouseSold(false);
                                int x = find_value(houses, position); //trova l'indice del vettore nel quale si trova quella casella
                                houses.erase(houses.begin() + x); //rimuovo la proprietà della casa
                                hotels.push_back(position); //aggiornamento degli hotel posseduti dal giocatore
                                f << "- Giocatore " << numPlayer << " ha migliorato una casa in albergo sul terreno "<< b.getTile(position) << std::endl;
                                std::cout << "- Giocatore " << numPlayer << " ha migliorato una casa in albergo sul terreno " << b.getTile(position) << std::endl;
                                 std::cout << "- L'hotel acquistato è di tipo " << tile << " ed è costato " << element->getHotelPrice() << " fiorini" << std::endl; ;
                            }
                        }
                    }   
                }
                f << "- Giocatore " << numPlayer << " ha finito il turno" << std::endl;
                std::cout << "- Giocatore " << numPlayer << " ha finito il turno" << std::endl;
            }
            else //se invece la casella è proprietà di qualcun'altro
            {
                if (element->isHouseSold()) //e se l'altro giocatore possiede già una casa faccio pagare il pernottamento
                {
                    int houseOwner = element->getOwner();
                   
                    if (budget < element->getNightHousePrice()) //giocatore eliminato in quanto non possiede abbastanza fiorini
                    {
                        eliminated = true;
                      
                        //elimino proprietà giocatore eliminato
                        lands.clear();
                        houses.clear();
                        hotels.clear();
                        removeProperties(properties);
                        element->erasePlayersTile(this->getPlayer(), position);
                        numEliminated++;
                      
                        //pagamento al proprietario della casa 
                        switch(houseOwner)
                        {
                            case(1):p1->updateBudget(budget);
                            break;
                            case(2):p2->updateBudget(budget);
                            break;
                            case(3):p3->updateBudget(budget);
                            break;
                            case(4):p4->updateBudget(budget);
                            break;
                        }
                        std::cout << "- Giocatore " << numPlayer << " non ha abbastanza fiorini per pagare il pernottamento nella casa della casella " << b.getTile(position) << " di tipo " << tile << std::endl;
                        std::cout << "- Giocatore " << numPlayer << " paga il giocatore " << houseOwner << " con tutto il suo budget di " << budget << " fiorini" << std::endl;

                        f << "- Giocatore " << numPlayer << " è stato eliminato" << std::endl;
                        std::cout << "- Giocatore " << numPlayer << " è stato eliminato" << std::endl;
                    }
                    else //il giocatore ha abbastanza soldi per pagare il proprietario della casa
                    {
                        //aggiorno budget del proprietario
                        switch(houseOwner)
                        {
                            case(1):p1->updateBudget(element->getNightHousePrice());
                            break;
                            case(2):p2->updateBudget(element->getNightHousePrice());
                            break;
                            case(3):p3->updateBudget(element->getNightHousePrice());
                            break;
                            case(4):p4->updateBudget(element->getNightHousePrice());
                            break;
                        }
                        f << "- Giocatore " << numPlayer << " ha pagato " << (element->getNightHousePrice()) << " fiorini a giocatore "<< houseOwner << " per pernottamento nella casella " << b.getTile(position) << std::endl;
                        std::cout << "- Giocatore " << numPlayer << " ha pagato " << (element->getNightHousePrice()) << " fiorini a giocatore " << houseOwner << " per pernottamento nella casella " << b.getTile(position) << std::endl;
                         std::cout << "- Giocatore " << numPlayer << " ha pernottato in una casa in una casella di tipo " << tile << std::endl; 
                    }
                    budget = budget - element->getNightHousePrice();
                }
                if (element->isHotelSold()) //faccio pagare il pernottamento in hotel
                {
                    int houseOwner = element->getOwner();
                    if (budget < element->getNightHotelPrice()) //giocatore eliminato in quanto non possiede abbastanza fiorini
                    {
                        eliminated = true;
                      
                        //elimino proprietà giocatore eliminato
                        lands.clear();
                        houses.clear();
                        hotels.clear();
                        removeProperties(properties);
                        element->erasePlayersTile(this->getPlayer(), position);
                        numEliminated++;
                      
                        //pagamento al proprietario dell'hotel 
                        switch(houseOwner)
                        {
                            case(1): p1->updateBudget(budget);
                            break;
                            case(2): p2->updateBudget(budget);
                            break;
                            case(3): p3->updateBudget(budget);
                            break;
                            case(4): p4->updateBudget(budget);
                            break;
                        }
                        std::cout << "- Giocatore " << numPlayer << " non ha abbastanza fiorini per pagare il pernottamento nell'hotel della casella " << b.getTile(position) << " di tipo " << tile << std::endl;
                        std::cout << "- Giocatore " << numPlayer << " paga il giocatore " << houseOwner << " con tutto il suo budget di " << budget << " fiorini" << std::endl;
                       
                        f << "- Giocatore " << numPlayer << " è stato eliminato" << std::endl;
                        std::cout << "- Giocatore " << numPlayer << " è stato eliminato" << std::endl;
                    }
                    else //il giocatore ha abbastanza soldi per pagare il proprietario dell'hotel
                    {
                        //aggiorno budget del proprietario
                        switch(houseOwner)
                        {
                            case(1):p1->updateBudget(element->getNightHotelPrice());
                            break;
                            case(2):p2->updateBudget(element->getNightHotelPrice());
                            break;
                            case(3):p3->updateBudget(element->getNightHotelPrice());
                            break;
                            case(4):p4->updateBudget(element->getNightHotelPrice());
                            break;
                        }
                        f << "- Giocatore " << numPlayer << " ha pagato " << (element->getNightHotelPrice()) << " fiorini a giocatore " << houseOwner << " per pernottamento nella casella " << b.getTile(position) << std::endl;
                        std::cout << "- Giocatore " << numPlayer << " ha pagato " << (element->getNightHotelPrice()) << " fiorini a giocatore " << houseOwner << " per pernottamento nella casella " << b.getTile(position) << std::endl;
                        std::cout << "- Giocatore " << numPlayer << " ha pernottato in un hotel in una casella di tipo " << tile << std::endl; 
                    }
                    budget = budget - element->getNightHotelPrice();
                }
                f << "- Giocatore " << numPlayer << " ha finito il turno" << std::endl;
                std::cout <<  "- Giocatore " << numPlayer << " ha finito il turno" << std::endl;
            }
        }
    }
    else
    {
      f << "- Giocatore " << numPlayer << " ha finito il turno" << std::endl;
      std::cout <<  "- Giocatore " << numPlayer << " ha finito il turno" << std::endl;
    }
}

bool probability() {
  int n = std::rand() % 4;
  if (n == 0)
    return true;
  else
    return false;
}
