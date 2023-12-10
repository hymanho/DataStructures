File Edit Options Buffers Tools C++ Help
#ifndef DataEntries_H
#define DataEntries_H
#include <string>
using namespace std;

class DataEntry {
 private:
  int year; // up to this year
  string country;
  int gold; //total gold medal count for country
  int silver; //total silver medal count for country
  int bronze; //total bronze medal count for country
 public:

  DataEntry (int year, string country, int gold, int silver, int bronze) { // data entry type constructor
    this->year = year;
    this->country = country;
    this->gold = gold;
    this->silver = silver;
    this->bronze = bronze;
  }

  int getYear() {
    return year;
  }

  string getCountry() {
    return country;
  }

  int getGold() {
    return gold;
  }

  int getSilver() {
    return silver;
  }

  int getBronze() { // getter methods
    return bronze;
  }

  void setYear(int year) {
    this->year = year;
  }

  void setGold(int gold) {
    this->gold += gold;
  }

  void setSilver(int silver) {
    this->silver += silver;
  }

  void setBronze(int bronze) { // setter methods
    this->bronze += bronze;
  }

};
#endif
