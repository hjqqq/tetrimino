#ifndef _SETTING_H_
#define _SETTING_H_

#include <fstream>
#include <string>
#include <map>

using namespace std;

class Setting{
 public:
  Setting(const string &_file);
  ~Setting();

  void loadSetting();
  void saveSetting();
  void loadDefaultSetting(const string &);

 private:
  fstream fs;
  string file;
  string key;
  double value;
  map<string,double> setting_map;
  
  void print();
  void checkIn();
  void checkOut();
};

#endif /* _SETTING_H_ */
