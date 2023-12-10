#ifndef MedalDB_H
#define MedalDB_H
#include <string>
#include <vector>
#include "DataEntries.h"
using namespace std;


class MedalDB { // hash table class
private:
  int size;
  string key;
  vector<vector<DataEntry*>> dataEntries; // hash table implemented using vector of vectors
  vector<DataEntry*> entryChain; // inner vector
  int hash(string key); // hash function
  DataEntry* getRecord(string country);
  //void reHash();
  //int newSize(int currentSize);
  //int newPrime();
public:
  MedalDB(); // constructor for the table
  void update(DataEntry* entry, int year, int gold, int silver, int bronze); // update using setter methods from DataEntries.h
  bool addRecord(DataEntry* entry);
  DataEntry* retrieveRecord(string country); // helper for getRecord
  bool deleteRecord(string key);
  void displayRecords();
  DataEntry* parseLine(string data); // parses a line for data to return a DataEntry*
  void deleteTable();
  void reHash();
  void newSize();
  int nextPrime();
};

#endif
