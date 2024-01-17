//MADDALENA BIONDO

/*Dalla riga dei comandi si va a decidere che tipo di partita verrà giocata: un umano e tre computer se si passa "human" oppure quattro computer se si passa "computer".
Successivamente i giocatori tirano i dadi e i quattro giocatori vengono inizializzati (utilizzando anche dei puntatori Player*).
Si imposta un numero massimo di turni e i giocatori giocano uno dopo l'altro in base all'ordine stabilito all'inizio della partita. 
Se tre giocatori vengono eliminati allora l'ultimo rimasto vince, se invece viene raggiunto il massimo di turni e non è rimasto solo un giocatore allora quello con il budget più alto vince (se ce n'è più di uno allora ci saranno più vincitori).*/

#include "Board.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"

int main(int argc, char *argv[]) {

  srand((unsigned int)time(0)); //per randomizzare il tiro dei dadi

  std::string gameType;
  
  try {
    if (argv[1] != NULL) {
      gameType = argv[1];
    } else {
      throw std::logic_error("Error");
    }
    if (gameType != "human" && gameType != "computer") {
      throw std::invalid_argument("Error");
    }
  } catch (std::exception e) {
    std::cout << "Non è stato specificato il tipo di partita da giocare. "
                 "Scegliere tra \"human\" e \"computer\"." << std::endl;
    return 0;
  }

  std::cout << "\n\nBENVENUTO A MONOPOLY! Cominciamo a giocare!\n\n";

   Board board = Board();
   std::array<Player, 4> playerList; //array dei giocatori
   std::array<Player*, 4> playerOrder; //array dei giocatori in ordine

   std::array<std::array<int, 2>, 4> order;

  //PARTITA CON TRE COMPUTER E UN UMANO
  if (gameType == "human") {

    std::cout << "Hai scelto la modalità partita 3 computer vs 1 umano. Ogni giocatore tira il dado.\nSei il giocatore 1.\n" << std::endl;
      
    std::ofstream outputFile;
    outputFile.open("log.txt"); //creazione del file di log  
      
    order = whoStarts(playerOrder, "human", outputFile); //per decidere l'ordine di inizio partita

   //per vedere quando gioca nel primo turno il giocatore umano
   std::cout << "Tirerai per ";
   for (int i = 0; i < 4; i++)
   {
      if (i == 0 && order[i][0] == 1) { std::cout << "primo.\n\n";}
      if (i == 1 && order[i][0] == 1) { std::cout << "secondo.\n\n";}
      if (i == 2 && order[i][0] == 1) { std::cout << "terzo.\n\n";}
      if (i == 3 && order[i][0] == 1) { std::cout << "quarto.\n\n";}
   }

  //creazione dei puntatori ai quattro giocatori
  Player* p1 = nullptr;
  Player* p2 = nullptr;
  Player* p3 = nullptr;
  Player* p4 = nullptr;

  HumanPlayer a = HumanPlayer(1);
  ComputerPlayer b = ComputerPlayer(order[0][0]);
  ComputerPlayer c = ComputerPlayer(order[1][0]);
  ComputerPlayer d = ComputerPlayer(order[2][0]);
  ComputerPlayer e = ComputerPlayer(order[3][0]);

  //inizializzazione dei puntatori (questa è la numerazione dell'attuale ordine di gioco, ma il Giocatore 1 è comunque sempre l'umano, non è detto poi che sia il primo a giocare)
  if (order[0][1] == 1) //giocatore 1 umano
  {
    p1 = &a; 
  }
  else //giocatore 1 computer
  {
    p1 = &b;
  }	
  if (order[1][1] == 1) //giocatore 2 umano
  {
    p2 = &a;
  }
  else //giocatore 2 computer
  {
    p2 = &c;
  }
  if (order[2][1] == 1) //giocatore 3 umano
  {
    p3 = &a;
  }
  else //giocatore 3 computer
  {
    p3 = &d;
  }
  if (order[3][1] == 1) //giocatore 4 umano
  {
    p4 = &a;
  }
  else //giocatore 4 computer
  {
    p4 = &e;
  }

  board[0]->startPlayersTile(); //inizializzazione dei giocatori nel tabellone

  int numTurns = 0; //variabile che conta il numero di turni; un turno consiste in tutti e quattro i giocatori che giocano

  Player* actualPlayersOrder[4] = {p1, p2, p3, p4}; //ordine attuale di gioco
  Player* currentPlayer = actualPlayersOrder[0]; //giocatore corrente, all'inizio è p1

  //ciclo che continua finché non finiscono i turni o finché tre giocatori su quattro vengono eliminati
  while (numTurns < 40)
  {	
      if (currentPlayer->getNumEliminated() == 3)
      {
        for (int i = 0; i < 4; i++)
        {
          if (actualPlayersOrder[i]->isEliminated() == false)
          {
            outputFile << "- Giocatore " << actualPlayersOrder[i]->getPlayer() << " ha vinto la partita" << std::endl;
            std::cout << "\nLa partita è terminata perché sono stati eliminati tre giocatori." << std::endl;
            std::cout << "- Giocatore " << actualPlayersOrder[i]->getPlayer() << " ha vinto la partita" << std::endl;
            outputFile.close();
            return 0;
          }
        }			
      }

      for (int i = 0; i < 4; i++)
      {
        if (actualPlayersOrder[i]->isEliminated() == false)
        {
          currentPlayer = actualPlayersOrder[i];
          currentPlayer->turnToPlay(board, outputFile, p1, p2, p3, p4);
        }
      }
      numTurns++;
  }

  std::cout << "\nLa partita è finita per raggiungimento di numero massimo di turni di gioco. Vediamo chi ha vinto (vittoria determinata in base a chi ha il budget massimo)!\n\n";
    
  std::vector<Player*> winners = whoWins(actualPlayersOrder);
  if (winners.size() == 1)
  {
    outputFile << "- Giocatore " << winners[0]->getPlayer() << " ha vinto la partita" << std::endl;
    std::cout << "- Giocatore " << winners[0]->getPlayer() << " ha vinto la partita" << std::endl;
    outputFile.close();
    return 0;
  }
  else
  {
    std::string s = "";
    while (!(winners.empty()))
    {
      Player* winner = winners.back();
      winners.pop_back();
      std::string numOfPlayer = std::to_string(winner->getPlayer());
      s = s + numOfPlayer + " ";
    }
    s = s + "\b";

    outputFile << "- I giocatori " << s << " hanno vinto la partita" << std::endl;
    std::cout << "- I giocatori " << s << " hanno vinto la partita" << std::endl;
    outputFile.close();
    return 0;
  }

  } 
  
  //PARTITA CON QUATTRO COMPUTER
  else // gameType == "computer"
    {
    std::cout << "Hai scelto la modalità partita con 4 computer." << std::endl;

    std::ofstream outputFile;
    outputFile.open("log.txt"); //creazione del file di log	
	
    order = whoStarts(playerOrder, "computer", outputFile);

    ComputerPlayer a = ComputerPlayer(order[0][0]);
    ComputerPlayer b = ComputerPlayer(order[1][0]);
    ComputerPlayer c = ComputerPlayer(order[2][0]);
    ComputerPlayer d = ComputerPlayer(order[3][0]);

    Player* p1 = &a;
    Player* p2 = &b;
    Player* p3 = &c;
    Player* p4 = &d;

    int numTurns = 0; //variabile che conta il numero di turni; un turno consiste in tutti e quattro i giocatori che giocano

    Player* actualPlayersOrder[4] = {p1, p2, p3, p4};
    Player* currentPlayer = actualPlayersOrder[0];

    while (numTurns < 40)
    {	
      if (currentPlayer->getNumEliminated() == 3)
      {
        for (int i = 0; i < 4; i++)
        {
          if (actualPlayersOrder[i]->isEliminated() == false)
          {
		    outputFile << "- Giocatore " << actualPlayersOrder[i]->getPlayer() << " ha vinto la partita" << std::endl;
		    std::cout << "\nLa partita è terminata perché sono stati eliminati tre giocatori." << std::endl;
		    std::cout << "- Giocatore " << actualPlayersOrder[i]->getPlayer() << " ha vinto la partita" << std::endl;
		    outputFile.close();
		    return 0;
          }
        }			
      }

     for (int i = 0; i < 4; i++)
     {
       if (actualPlayersOrder[i]->isEliminated() == false)
       {
         currentPlayer = actualPlayersOrder[i];
         currentPlayer->turnToPlay(board, outputFile, p1, p2, p3, p4);
       }
     }
     numTurns++;
    }

    std::cout << "\nLa partita è finita per raggiungimento di numero massimo di turni di gioco. Vediamo chi ha vinto (vittoria determinata in base a chi ha il budget massimo)!\n\n";
    std::vector<Player*> winners = whoWins(actualPlayersOrder);

    if (winners.size() == 1)
    {
      outputFile << "- Giocatore " << winners[0]->getPlayer() << " ha vinto la partita" << std::endl;
      std::cout << "- Giocatore " << winners[0]->getPlayer() << " ha vinto la partita" << std::endl;
      outputFile.close();
      return 0;
    }
    else
    {
      std::string s = "";
      while (!(winners.empty()))
      {
        Player* winner = winners.back();
        winners.pop_back();
        std::string numOfPlayer = std::to_string(winner->getPlayer());
        s = s + numOfPlayer + " ";
      }
    s = s + "\b";

    outputFile << "- I giocatori " << s << " hanno vinto la partita" << std::endl;
    std::cout << "- I giocatori " << s << " hanno vinto la partita" << std::endl;
    outputFile.close();
    return 0;
    }
  }
}
