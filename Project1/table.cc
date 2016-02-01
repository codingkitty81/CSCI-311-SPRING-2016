
#include "table.h"

Table::Table() {
   
}

Table::Table(const string& tableID, int numSeats, const string& serverName) {
   this.tableID = tableID;
   this.numSeats = numSeats;
   this.serverName = serverName;
}

Table::~Table() {
   
}

void Table::seatParty(const Party* newParty) {
   
}