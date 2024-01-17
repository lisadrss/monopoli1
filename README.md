##PROGETTO FINALE

#COMPILAZIONE

La cartella che contiene tutti i file necessari si chiama ProgettoFinale. Abbiamo utilizzato CMake, creando la cartella "include" (dove abbiamo inserito tutti i file header delle classi create) e "src" (dove sono contenuti i file .cpp). Un altro file necessario e presente nella cartella ProgettoFinale è CMakeLists.txt, che contiene direttive e istruzioni che descrivono i file del progetto.
Per la compilazione usare i seguenti comandi nel terminale:
cd ProgettoFinale
mkdir build
cd build
cmake ..
make
./main human (nel caso di partita con un umano e tre computer)
./main computer (nel caso di partita con quattro computer)
NOTA BENE: Per una corretta visualizzazione dell'output si consiglia di impostare il terminale a schermo intero.


#HUMANPLAYER

NOTA BENE: Quando si prende l'input enter per andare a capo quando il giocatore deve tirare i dadi, questo comando stranamente viene letto solo una volta (al primo turno); è stato quindi necessario aggiungere due std::getline(std::cin, enter), solo che per il primo turno deve leggerne solo uno altrimenti l'utente dovrebbe andare a capo due volte, mentre nei turni successivi ne servono due per andare a capo solo una volta. Ci siamo dunque servite di una variabile statica per contare il numero di turni. Abbiamo provato in altri modi che all'apparenza sembravano più logicamente corretti ma nessuno di questi ha funzionato.

#MAIN

NOTA BENE: Siccome i giocatori ritirano sempre 20 fiorini passando dal via, è praticamente improbabile che la partita termini con tre giocatori eliminati, ma terminerà sempre per il raggiungimento del numero massimo di turni; abbiamo fatto anche prove con numeri alti di turni (milioni di turni) ma la partita non terminava per le eliminazioni. Diminunendo invece la quantità dei fiorini ritirati passando dal via ad un numero minimo (+1 fiorino ad ogni passaggio) e con un numero di turni massimo pari a 500, si ha che il gioco termina con tre giocatori eliminati (prova fatta con partita di quattro computer).
In ogni caso nel main.cpp abbiamo tenuto come numero massimo di turni 40, per rendere più comprensibili anche i file di log delle partite esempio.
