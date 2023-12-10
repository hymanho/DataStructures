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
