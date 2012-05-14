#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <stdexcept>
#include "SDL.h"
#include "setting.h"
#include "optiondata.h"
#include "playerdata.h"

using namespace std;

Setting::Setting(const string &_file) : file(_file)
{}

Setting::~Setting()
{}

void Setting::loadSetting()
{
  fs.clear();
  fs.open(file.c_str(), fstream::in);
  if ( !fs )
    throw runtime_error("no user setting file");
  while ( fs >> key >> value ) {
    setting_map[key] = value;
  }
  fs.close();
  checkIn();
  print();
}

void Setting::print()
{
  for(map<string,double>::iterator iter = setting_map.begin(); iter != setting_map.end(); ++iter)
    {
      cout <<"[" << iter->first << ", " << iter->second << "]" << endl;
    }
}

void Setting::saveSetting()
{
  fs.clear();
  fs.open(file.c_str(), fstream::out);
  for(map<string,double>::iterator iter = setting_map.begin(); iter != setting_map.end(); ++iter)
    {
      key = iter->first;
      value = iter->second;
      fs << key << " " <<  value << endl;;
    }
  fs.close();
}

void Setting::loadDefaultSetting(const string & default_file)
{
  fs.clear();
  fs.open(default_file.c_str(), fstream::in);
  if( !fs )
    throw runtime_error("no default setting file");
  while ( fs >> key >> value ) {
    setting_map[key] = value;
  }
  fs.close();
  checkIn();
  print();
}

void Setting::checkIn()
{
  int pos_x_1p = 0;
  int pos_y_1p = 0;
  int pos_x_2p = 0;
  int pos_y_2p = 0;
  for(map<string,double>::iterator iter = setting_map.begin(); iter != setting_map.end(); ++iter)
    {
      key = iter->first;
      value = iter->second;
      
      // regular settings
      if( key == "areDelayTime" )
	OptionData::areDelayTime = (int)value;
      else if( key == "lockDelayTime" )
	OptionData::lockDelayTime = (int)value;
      else if( key == "playerSize" )
	OptionData::playerSize = (int)value;
      else if( key == "ghostAlpha" )
	OptionData::ghostAlpha = (int)value;
      
      // 1p settings
      else if( key == "1pGhost" )
	OptionData::playerData1.ghost = (bool)value;
      else if( key == "1pHolder" )
	OptionData::playerData1.holder = (bool)value;
      else if( key == "1pHorizontalSpeed" )
	OptionData::playerData1.horizontalSpeed = value;
      else if( key == "1pNormalDropSpeed" )
	OptionData::playerData1.normalDropSpeed = value;
      else if( key == "1pSoftDropSpeed" )
	OptionData::playerData1.softDropSpeed = value;
      else if( key == "1pRandomQueueDataIndex" )
	OptionData::playerData1.randomQueueDataIndex = (int)value;
      else if( key == "1pRandomizerType" )
	OptionData::playerData1.randomizerType = (PlayerData::RandomizerType)value;
      else if( key == "1pMoveLeft" )
	OptionData::playerData1.moveLeft = (SDLKey)value;
      else if( key == "1pMoveRight" )
	OptionData::playerData1.moveRight = (SDLKey)value;
      else if( key == "1pRotateLeft" )
	OptionData::playerData1.rotateLeft = (SDLKey)value;
      else if( key == "1pRotateRight" )
	OptionData::playerData1.rotateRight = (SDLKey)value;
      else if( key == "1pSoftDrop" )
	OptionData::playerData1.softDrop = (SDLKey)value;
      else if( key == "1pHardDrop" )
	OptionData::playerData1.hardDrop = (SDLKey)value;
      else if( key == "1pHold" )
	OptionData::playerData1.hold = (SDLKey)value;
      else if( key == "1pPosX" )
	pos_x_1p = (int)value;
      else if( key == "1pPosY" )
	pos_y_1p = (int)value;
      
      // 2p settings
      else if( key == "2pGhost" )
	OptionData::playerData2.ghost = (bool)value;
      else if( key == "2pHolder" )
	OptionData::playerData2.holder = (bool)value;
      else if( key == "2pHorizontalSpeed" )
	OptionData::playerData2.horizontalSpeed = value;
      else if( key == "2pNormalDropSpeed" )
	OptionData::playerData2.normalDropSpeed = value;
      else if( key == "2pSoftDropSpeed" )
	OptionData::playerData2.softDropSpeed = value;
      else if( key == "2pRandomQueueDataIndex" )
	OptionData::playerData2.randomQueueDataIndex = (int)value;
      else if( key == "2pRandomizerType" )
	OptionData::playerData2.randomizerType = (PlayerData::RandomizerType)value;
      else if( key == "2pMoveLeft" )
	OptionData::playerData2.moveLeft = (SDLKey)value;
      else if( key == "2pMoveRight" )
	OptionData::playerData2.moveRight = (SDLKey)value;
      else if( key == "2pRotateLeft" )
	OptionData::playerData2.rotateLeft = (SDLKey)value;
      else if( key == "2pRotateRight" )
	OptionData::playerData2.rotateRight = (SDLKey)value;
      else if( key == "2pSoftDrop" )
	OptionData::playerData2.softDrop = (SDLKey)value;
      else if( key == "2pHardDrop" )
	OptionData::playerData2.hardDrop = (SDLKey)value;
      else if( key == "2pHold" )
	OptionData::playerData2.hold = (SDLKey)value;
      else if( key == "2pPosX" )
	pos_x_2p = (int)value;
      else if( key == "2pPosY" )
	pos_y_2p = (int)value;
    }
  OptionData::playerData1.showPixPos = Vector2<int>(pos_x_1p, pos_y_1p);
  OptionData::playerData2.showPixPos = Vector2<int>(pos_x_2p, pos_y_2p);
}

void Setting::checkOut()
{
  
}
