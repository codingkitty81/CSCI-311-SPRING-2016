
#include <iostream>
#include "restaurant.h"

void Restaurant::getInput() {
   std::string option;
   std::string tableName;
   int seats;
   std::string server;
   std::string resName;
   int dinersNum;
   int requiredTime;
   
   while(std::cin>>option) {
      if(option=="table") {
         std::cin>>tableName;
         std::cin>>seats;
         std::cin>>server;
         Table* newTable = new Table(tableName, seats, server);
         available.append(newTable);
      } else if(option=="party") {
         std::cin>>dinersNum;
         std::cin>>resName;
         std::cin>>requiredTime;
         Party* newParty = new Party(resName, dinersNum, requiredTime);
         waiting.append(newParty);
      } else {
         break;
      }
   }
}

void Restaurant::serveParties() {
   Table* openTable = available.first();
   Party* theParty = waiting.first();
   Table* takenTable = occupied.first();

   while (theParty != nullptr || takenTable != nullptr) {
      while (takenTable != nullptr) {
         if (takenTable->getTimer() == 0) {
            std::cout << *(takenTable->getParty()->getReservationName());
            std::cout << " finished at " << *(takenTable->getTableID()) << std::endl;
            takenTable->clearTable();
            available.append(takenTable);
            takenTable = occupied.remove();
         } else {
            takenTable->decrementTimer();
            takenTable = occupied.next();
         }
     
      }
   
    openTable = available.first();
    theParty = waiting.first();
   
      while (theParty != nullptr && openTable != nullptr) {
         if (theParty->getNumDiners() <= openTable->getNumSeats()) {
            std::cout << *(theParty->getReservationName());
            std::cout << " seated at " << *(openTable->getTableID()) << std::endl;
            servers[*(openTable->getServerName())] += theParty->getNumDiners();
            openTable->seatParty(theParty);
            occupied.append(openTable);
            available.remove();
            waiting.remove();
            theParty = waiting.first();
            openTable = available.first();
         } else {
            if ((openTable = available.next()) == nullptr) {
               openTable = available.first();
               theParty = waiting.next();
         }
      }
    }
    
    openTable = available.first();
    theParty = waiting.first();
    takenTable = occupied.first();
   }
   
   for (std::map<string,int>::iterator it=servers.begin(); it!=servers.end(); ++it) {
      std::cout << it->first << " served " << it->second << std::endl;
   }
}
 
int main() {
   Restaurant myDiner;
   myDiner.getInput();
   myDiner.serveParties();
   return 0;
}