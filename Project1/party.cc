
#include "party.h"

Party::Party() {
   
}

Party::Party(const string& reservationName, int numDiners, int timeRequired) {
   std::string* tempRes = new string(reservationName);
   
   this->reservationName = tempRes;
   this->numDiners = numDiners;
   this->timeRequired = timeRequired;
}

Party::~Party() {
   
}