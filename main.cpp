#include <iostream>
#include <fstream>
#include "MedalDB.h"
using namespace std;


int main(int argc, char* argv[]) { // driver

  MedalDB table; // makes a hash table
  if (argc != 2) { // checks for number of arguments
    cout << "Usage: assignment1 <testFileName>" << endl;
    return 1;
  }

  string instructionFile = argv[1]; // instruction file
  ifstream infile(instructionFile);
  if (!infile.is_open()) { // checks if file is able to open
    cout << "Unable to open file: " << instructionFile << endl;
    return 1;
  }
  string instructionLine; // instruction line for instruction file
  while (getline(infile, instructionLine)) { // while there is still an avaliable line for in the instruction file
    string data;
    char choice = instructionLine[0];
    switch(choice) {
    case 'i': { // initalizes the table with data from the .csv file
      string recordFile;
      string record;
      getline(infile, recordFile); // gets csv file name
      cout << "Initalizing " << recordFile << "..." << endl;
      ifstream infileCSV(recordFile);
      string header;
      getline(infileCSV, header); // stores header line in header variable, skipping it
      while (getline(infileCSV, record)) { // iterates through each line in the csv file
        DataEntry* entry = table.parseLine(record);
        table.addRecord(entry);
      }
      infileCSV.close();
      break;
    }
   case 'a': {
      getline(infile, data);
      int commaCounter = 0;
      string stringDate = "";
      string country = "";
      char goldCount = '\0';
      char silverCount = '\0';
      char bronzeCount = '\0'; // initalizes variable

      for (int i = 0; i < (int)data.length(); i++) { // iterates through sentence (parses line for data)

        if (i < 4) { // first 4 characters are the years
          stringDate += data[i];
        }

        if (commaCounter == 1) { // after 1 comma, the name of the country will appear
          if (data[i] != ',') {
            country += data[i]; // the country name will be the letters after counting 1 commma in the line
          } else {
            ;
          }
        }

        if (commaCounter == 2) { // after 2 commas, the gold count will appear
          if (data[i] != ',') {
            goldCount = data[i]; // the gold count will be the letters after counting 2 commmas in the line
          } else {
            ;
          }
        }

        if (commaCounter == 3) { // after 3 commas, the silver count will appear
          if (data[i] != ',') {
            silverCount = data[i]; // the silver count will be the letters after counting 3 commmas in the line
          } else {
            ;
          }
        }

        if (commaCounter == 4) { // after 4 commas, the bronze count will appear
          if (data[i] != ',') {
            bronzeCount = data[i]; // the bronze count will be the letters after counting 4 commmas in the line
          } else {
            ;
          }
        }

        if (data[i] == ',') { // counts commas, iterate comma counter by 1 after encountering a comma
          commaCounter++;
        }

      }
   case 'g': {
      getline(infile, data);
      if (table.retrieveRecord(data) == nullptr) {
        cout << "Sorry, the record for " << data << " does not exist and cannot be retrieved." << endl;
      } else {
        DataEntry& target = *table.retrieveRecord(data);
        cout << "Retrieveing medals for " << data << ": " << target.getYear() << ", " << target.getGold() << " gold, " << target.getSilver() << " silver, " << target.getBronze() << " bronze" << endl;
      }
      break;
    }
    case 'r': { // removes a record
      getline(infile, data);
      cout << "Attempting to remove data entry for " << data << "..." << endl;
      bool recordStatus = table.deleteRecord(data);
      if (recordStatus != 0) { // output messages depending on whether deleteRecord(string) returns true or false
        cout << "This record has been sucessfully deleted." << endl;
      } else {
        cout << "Sorry, the data entry for " << data << " couldn't be deleted. Please confirm this is the correct record." << endl;
      }
      break;
    }
 case 'd': // displays records
      table.displayRecords();
      break;

    case 'h': // rehashes table
      table.reHash();
      cout << "The table has been successfully rehashed." << endl;
      break;
    }
  }
  table.deleteTable();
}
