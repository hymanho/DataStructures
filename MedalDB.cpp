#include <cstdlib>
#include <iostream>
#include "MedalDB.h"
#include <vector>
#include "DataEntries.h"
int HASHTABLE_SIZE = 17; // table size

using namespace std;


MedalDB::MedalDB() { // vector of vector<DataEntry> constructor
  for (int i = 0; i < HASHTABLE_SIZE; i++) { // pushes a vector onto every index
    dataEntries.push_back(entryChain);

  }
  size = 0; // make size = 0

}


int MedalDB::hash(string key) { // hash formula

  char letter;
  int summation = 0;
  int keyLength = key.length();
  int counter = 1;
  for (int i = 0; i < keyLength; i++) { // iterates through every character in the country name

    letter = key[i];
    int value = (int)letter; // ASCII value of the character
    summation = summation + (counter*value); // the part of the formula that is the summatation
    counter++; // increase counter
  }
  int hashValue = summation % HASHTABLE_SIZE; // modulate by hash table size
  return hashValue;

}

bool MedalDB::addRecord(DataEntry* entry) { // adds a record

  int index = hash(entry->getCountry());
  if (getRecord(entry->getCountry()) != nullptr) { // if the country already exists in the hash table, update the record
    if (getRecord(entry->getCountry())->getYear() > entry->getYear()) { // if the recod in the hash table's year is greater than the entry's, return false
      return false;
    } else { // update medals using helper
      DataEntry copy(entry->getYear(), entry->getCountry(),entry->getGold(),entry->getSilver(),entry->getBronze());
      update(getRecord(entry->getCountry()), copy.getYear(), copy.getGold(), copy.getSilver(), copy.getBronze());


      return true;
    }
  } else { // if the country does not exist, insert it at given index
    DataEntry* newRecord = new DataEntry(entry->getYear(), entry->getCountry(), entry->getGold(), entry->getSilver(), entry->getBronze());
    dataEntries[index].push_back(newRecord);
    size++;
    return true;
  }
  return false;
}

void MedalDB::update(DataEntry* existingEntry, int newYear, int newGold, int newSilver, int newBronze) { // update helper method to update an exisitng record

    existingEntry->setYear(newYear);
    existingEntry->setGold(newGold);
    existingEntry->setSilver(newSilver);
    existingEntry->setBronze(newBronze); // use setters

}

DataEntry* MedalDB::getRecord(string key) { // searches for a record in the table

  if (size == 0) { // if table is empty, return nullptr
    return nullptr;
  }

  int index = hash(key);


  for (int i = 0; i < (int)dataEntries[index].size(); i++) { // for loop searches through the specified bucket indicated by the hash function
    DataEntry* currentRecord = dataEntries[index][i]; // record that is currently being viewed by for loop
    if (currentRecord->getCountry() == key) {
      return currentRecord; // returns the desired entry if found
    }
  }

  return nullptr; // nullptr if not found
}

DataEntry* MedalDB::retrieveRecord(string key) { // helper method for getRecord

  if (size == 0) { // failure mesage if table is empty
    return nullptr;
  }
  DataEntry* target = getRecord(key); // attemps to search for the key
  if (target == nullptr) { // failure and sucess message depending on whether or not getRecord returns nullptr
    return nullptr;
  }
  return target;
}

void MedalDB::displayRecords() { // displays the table

  if (size == 0) { // failure message is table is empty
    cout << "Table is empty." << endl;
    return;
  }

  for (int i = 0; i < HASHTABLE_SIZE; i++) {
    cout << "INDEX " << i << ":" << endl; // states index
    for (int j = 0; j < (int)dataEntries[i].size(); j++) { // nested for loops to iterate through entire hash table
      DataEntry* currentRecord = dataEntries[i][j]; // current record being viewed
      cout << currentRecord->getCountry() << ": " << currentRecord->getGold() << " gold, " << currentRecord->getSilver() << " silver, " << currentRecord->getBronze() << " bronze " << endl; // displays information
    }

  }
}

bool MedalDB::deleteRecord(string key) { // deletes a record

  if (getRecord(key) == nullptr) { // failure message if the record to be deleted does not exist
    return false;
  }

  int index = hash(key); // index at which desired record is stored

  for (int i = 0; i < (int)dataEntries[index].size(); i++) { // uses a for loop to iterate over the vector in our desired inex
    DataEntry& currentEntry = *dataEntries[index][i];
    if (currentEntry.getCountry() == key) { // if the entry we are currently looking at is equal to our target, remove it)
      delete dataEntries[index][i]; // deallocates the memory pointed to our desired record
      dataEntries[index].erase(dataEntries[index].begin() + i); // uses erase to clear that value out of the vector
      size--; // reduce size by 1
      return true;
    }
  }
  return false;
}

DataEntry* MedalDB::parseLine(string data) { // parses line
  string stringDate;
  string medalType;
  string country; // initalizes key variables, the date of the olympics, type of medal, and country
  int commaCounter = 0; // counts commas in line
  for (int i = 0; i < (int)data.length(); i++) { // iterates over all characters in the line

    if (i < 4) { // first 4 characters are the years
      stringDate += data[i];
    }

    if (commaCounter == 6) { // after 6 commas, the name of the country will appear
      if (data[i] != ',') {
        country += data[i]; // the country name will be the letters after counting 6 commmas in the line
      } else {
        ;
      }
    }

    if (commaCounter == 9) { // after 9 commas, the type of medal will appear. follow same process as above
      if (data[i] != ',') {
        medalType += data[i];
      } else {
        ;
      }
    }

    if (data[i] == ',') { // counts commas, iterate comma counter by 1 after encountering a comma
      commaCounter++;
    }
  }

  int numDate = stoi(stringDate); // changes stringDate into an integer

  if (medalType == "Gold") { // lines below will make a data entry depending on the medal type, and return it
    DataEntry* entry = new DataEntry(numDate, country, 1, 0, 0);
    return entry;
  }

  if (medalType == "Silver") {
    DataEntry* entry = new DataEntry(numDate, country, 0, 1, 0);
    return entry;
  }

  if (medalType == "Bronze") {
    DataEntry* entry = new DataEntry(numDate, country, 0, 0, 1);
    return entry;
  }
  return nullptr;
}

void MedalDB:: deleteTable() { // deletes entire hash table

  for (int i = 0; i < HASHTABLE_SIZE; i++) {
    for (int j = 0; j < (int)dataEntries[i].size(); j++) {
      dataEntries[i][j] = nullptr;
      delete dataEntries[i][j];
    }
    dataEntries[i].clear();
  }
  size = 0;
}

int MedalDB::nextPrime() { // returns next prime after doubling table size
  int newSize;
  int currentSize = HASHTABLE_SIZE;
  newSize = currentSize * 2; // double current hash table size
  bool isPrime = false;
  int counter = 0;
  while (isPrime != true) { // while the number is not a prime
    for (int i = 2; i <= currentSize / 2; i++) { // iterates from 2 up to half of the currentSize's number.
      if (newSize % i != 0) {                    // this is because the module of numbers above currentSize / 2 against newSize will not be 0 regardless
        counter++; // iterate counter if the module returned does not equal 0, proving that i is not a factor to newSize
      }
      if (newSize % i == 0) { // this means i is a factor, so exit the loop
        break;
      }
      if (counter == (currentSize / 2)-2) { // if we iterated through all values up to currentSize / 2 and they return 0 after modulating, that means the number is a prime
        isPrime = true;
        break; // exits the loop
      }
    }
    if (isPrime == true) { // checks if the boolean isPrime has been changed, and if so it will exit the while loop
      break;
    }
    newSize++; // otherwise iterate by 1 on the new size and test it again in the for loop to see if it is a prime
  }
  return newSize;
}

void MedalDB::newSize() { // sets new size to be value returned by nextPrime()
  HASHTABLE_SIZE = nextPrime();
}

void MedalDB::reHash() { // rehashes the table


  vector<DataEntry*> copyOfRecords; // a vector to hold copies of old hash table

  for (int i = 0; i < HASHTABLE_SIZE; i++) {
    for (int j = 0; j < (int)dataEntries[i].size(); j++) { // nested for loops to iterate through entire hash table
      DataEntry* copy = dataEntries[i][j];
      copyOfRecords.push_back(new DataEntry(copy->getYear(), copy->getCountry(), copy->getGold(), copy->getSilver(), copy->getBronze())); // copies data from old hash table to the copy vector
    }
  }


  deleteTable(); // deletes data in old table
  newSize(); // sets new size of hash table
  dataEntries.resize(HASHTABLE_SIZE); // resizes the original vector with the modified hash table size first

  for (int i = 0; i < (int)copyOfRecords.size(); i++) { // copies data from the copy over to the new rehashed table
    addRecord(copyOfRecords[i]);
  }

  for (int i = 0; i < (int)copyOfRecords.size(); i++) { // deletes the pointers in copy
    delete copyOfRecords[i];
    copyOfRecords[i] = nullptr;


  }
  copyOfRecords.clear(); // clears the copy vector

}










