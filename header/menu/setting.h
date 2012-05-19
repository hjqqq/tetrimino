#ifndef _SETTING_H_
#define _SETTING_H_

#include <fstream>
#include <string>
#include <map>

using namespace std;

/**
   @file setting.h
 */

/**
   @brief 从文件中读取或保存状态，初始化游戏全局变量
 */
class Setting{
 public:
    /**
       @param _file 传入用户个性化配置文件名（包含路径）
       @param _default_file 传入系统默认配置文件名（包含路径）
     */
  Setting(const string &_file, const string &_default_file);
  ~Setting();

    /**
       加载并初始化全局变量，如果用户配置加载不成功，加载系统默认配置
     */
  void loadSetting();

    /**
       保存用户配置文件，覆盖源配置文件
     */
  void saveSetting();

    /**
       加载系统默认配置文件
     */
  void loadDefaultSetting();

 private:
  fstream fs;
  string file;
  string default_file;
  string key;
  double value;
  map<string,double> setting_map;
  
  void print();
  void checkIn();
  void checkOut();
};

#endif /* _SETTING_H_ */
