
#include "table.h"

Table::Table() {
   
}

Table::Table(const string& tableID, int numSeats, const string& serverName) {
   std::string* tempTable = new string(tableID);
   std::string* tempServer = new string(serverName);
   
   this->tableID = tempTable;
   this->numSeats = numSeats;
   this->serverName = tempServer;
   party = nullptr;
   timer = 0;
}

Table::~Table() {
   
}

void Table::seatParty(const Party* newParty) {
   party = newParty;
   setTimer(party->getTimeRequired());
}