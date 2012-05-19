#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <stdexcept>
#include "SDL.h"
#include "setting.h"
#include "optiondata.h"
#include "resourcedata.h"
#include "playerdata.h"

using namespace std;

Setting::Setting(const string &_file, const string & _default_file) : 
    file(_file), 
    default_file(_default_file)
{}

Setting::~Setting()
{}

void Setting::loadSetting()
{
    fs.clear();
    fs.open(file.c_str(), fstream::in);
    if ( !fs ){
	cout << "load default settings" << endl;
	loadDefaultSetting();
    }
    else{
	while ( fs >> key >> value ) {
	    setting_map[key] = value;
	}
	fs.close();
	checkIn();
    }
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
    checkOut();
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

void Setting::loadDefaultSetting()
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
	else if( key == "musicVolume" ) {
	    OptionData::musicVolume = (int)value;
	    ResourceData::sound->setVolumeMusic( (int)value );
	}
	else if( key == "chunkVolume" ){
	    OptionData::chunkVolume = (int)value;
	    ResourceData::sound->setVolumeChunk( (int)value );
	}
      
	// 1p settings
	else if( key == "1pGhost" )
	    OptionData::playerData1.ghost = (bool)value;
	else if( key == "1pHolder" )
	    OptionData::playerData1.holder = (bool)value;
	else if( key == "1pDasDelayTime" )
	    OptionData::playerData1.dasDelayTime = (Uint32)value;
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
      
	// 2p settings
	else if( key == "2pGhost" )
	    OptionData::playerData2.ghost = (bool)value;
	else if( key == "2pHolder" )
	    OptionData::playerData2.holder = (bool)value;
	else if( key == "2pDasDelayTime" )
	    OptionData::playerData2.dasDelayTime = (Uint32)value;
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

	// 3p settings
	else if( key == "3pGhost" )
	    OptionData::playerData3.ghost = (bool)value;
	else if( key == "3pHolder" )
	    OptionData::playerData3.holder = (bool)value;
	else if( key == "3pDasDelayTime" )
	    OptionData::playerData3.dasDelayTime = (Uint32)value;
	else if( key == "3pHorizontalSpeed" )
	    OptionData::playerData3.horizontalSpeed = value;
	else if( key == "3pNormalDropSpeed" )
	    OptionData::playerData3.normalDropSpeed = value;
	else if( key == "3pSoftDropSpeed" )
	    OptionData::playerData3.softDropSpeed = value;
	else if( key == "3pRandomQueueDataIndex" )
	    OptionData::playerData3.randomQueueDataIndex = (int)value;
	else if( key == "3pRandomizerType" )
	    OptionData::playerData3.randomizerType = (PlayerData::RandomizerType)value;
	else if( key == "3pMoveLeft" )
	    OptionData::playerData3.moveLeft = (SDLKey)value;
	else if( key == "3pMoveRight" )
	    OptionData::playerData3.moveRight = (SDLKey)value;
	else if( key == "3pRotateLeft" )
	    OptionData::playerData3.rotateLeft = (SDLKey)value;
	else if( key == "3pRotateRight" )
	    OptionData::playerData3.rotateRight = (SDLKey)value;
	else if( key == "3pSoftDrop" )
	    OptionData::playerData3.softDrop = (SDLKey)value;
	else if( key == "3pHardDrop" )
	    OptionData::playerData3.hardDrop = (SDLKey)value;
	else if( key == "3pHold" )
	    OptionData::playerData3.hold = (SDLKey)value;

	// 4p settings
	else if( key == "4pGhost" )
	    OptionData::playerData4.ghost = (bool)value;
	else if( key == "4pHolder" )
	    OptionData::playerData4.holder = (bool)value;
	else if( key == "4pDasDelayTime" )
	    OptionData::playerData4.dasDelayTime = (Uint32)value;
	else if( key == "4pHorizontalSpeed" )
	    OptionData::playerData4.horizontalSpeed = value;
	else if( key == "4pNormalDropSpeed" )
	    OptionData::playerData4.normalDropSpeed = value;
	else if( key == "4pSoftDropSpeed" )
	    OptionData::playerData4.softDropSpeed = value;
	else if( key == "4pRandomQueueDataIndex" )
	    OptionData::playerData4.randomQueueDataIndex = (int)value;
	else if( key == "4pRandomizerType" )
	    OptionData::playerData4.randomizerType = (PlayerData::RandomizerType)value;
	else if( key == "4pMoveLeft" )
	    OptionData::playerData4.moveLeft = (SDLKey)value;
	else if( key == "4pMoveRight" )
	    OptionData::playerData4.moveRight = (SDLKey)value;
	else if( key == "4pRotateLeft" )
	    OptionData::playerData4.rotateLeft = (SDLKey)value;
	else if( key == "4pRotateRight" )
	    OptionData::playerData4.rotateRight = (SDLKey)value;
	else if( key == "4pSoftDrop" )
	    OptionData::playerData4.softDrop = (SDLKey)value;
	else if( key == "4pHardDrop" )
	    OptionData::playerData4.hardDrop = (SDLKey)value;
	else if( key == "4pHold" )
	    OptionData::playerData4.hold = (SDLKey)value;
    }
}

void Setting::checkOut()
{
    // regular settings
    setting_map["areDelayTime"] = (double)OptionData::areDelayTime;
    setting_map["lockDelayTime"] = (double)OptionData::lockDelayTime;
    setting_map["playerSize"] = (double)OptionData::playerSize;
    setting_map["ghostAlpha"] = (double)OptionData::ghostAlpha;
    setting_map["musicVolume"] = (double)OptionData::musicVolume;
    setting_map["chunkVolume"] = (double)OptionData::chunkVolume;
    
    // player1 settings
    setting_map["1pGhost"] = (double)OptionData::playerData1.ghost;
    setting_map["1pHolder"] = (double)OptionData::playerData1.holder;
    setting_map["1pDasDelayTime"] = (double)OptionData::playerData1.dasDelayTime;
    setting_map["1pHorizontalSpeed"] = (double)OptionData::playerData1.horizontalSpeed;
    setting_map["1pNormalDropSpeed"] = (double)OptionData::playerData1.normalDropSpeed;
    setting_map["1pSoftDropSpeed"] = (double)OptionData::playerData1.softDropSpeed;
    setting_map["1pRandomQueueDataIndex"] = (double)OptionData::playerData1.randomQueueDataIndex;
    setting_map["1pRandomizerType"] = (double)OptionData::playerData1.randomizerType;
    setting_map["1pMoveLeft"] = (double)OptionData::playerData1.moveLeft;
    setting_map["1pMoveRight"] = (double)OptionData::playerData1.moveRight;
    setting_map["1pRotateLeft"] = (double)OptionData::playerData1.rotateLeft;
    setting_map["1pRotateRight"] = (double)OptionData::playerData1.rotateRight;
    setting_map["1pSoftDrop"] = (double)OptionData::playerData1.softDrop;
    setting_map["1pHardDrop"] = (double)OptionData::playerData1.hardDrop;
    setting_map["1pHold"] = (double)OptionData::playerData1.hold;

    // player2 settings
    setting_map["2pGhost"] = (double)OptionData::playerData2.ghost;
    setting_map["2pHolder"] = (double)OptionData::playerData2.holder;
    setting_map["2pDasDelayTime"] = (double)OptionData::playerData2.dasDelayTime;
    setting_map["2pHorizontalSpeed"] = (double)OptionData::playerData2.horizontalSpeed;
    setting_map["2pNormalDropSpeed"] = (double)OptionData::playerData2.normalDropSpeed;
    setting_map["2pSoftDropSpeed"] = (double)OptionData::playerData2.softDropSpeed;
    setting_map["2pRandomQueueDataIndex"] = (double)OptionData::playerData2.randomQueueDataIndex;
    setting_map["2pRandomizerType"] = (double)OptionData::playerData2.randomizerType;
    setting_map["2pMoveLeft"] = (double)OptionData::playerData2.moveLeft;
    setting_map["2pMoveRight"] = (double)OptionData::playerData2.moveRight;
    setting_map["2pRotateLeft"] = (double)OptionData::playerData2.rotateLeft;
    setting_map["2pRotateRight"] = (double)OptionData::playerData2.rotateRight;
    setting_map["2pSoftDrop"] = (double)OptionData::playerData2.softDrop;
    setting_map["2pHardDrop"] = (double)OptionData::playerData2.hardDrop;
    setting_map["2pHold"] = (double)OptionData::playerData2.hold;

    // player3 settings
    setting_map["3pGhost"] = (double)OptionData::playerData3.ghost;
    setting_map["3pHolder"] = (double)OptionData::playerData3.holder;
    setting_map["3pDasDelayTime"] = (double)OptionData::playerData3.dasDelayTime;
    setting_map["3pHorizontalSpeed"] = (double)OptionData::playerData3.horizontalSpeed;
    setting_map["3pNormalDropSpeed"] = (double)OptionData::playerData3.normalDropSpeed;
    setting_map["3pSoftDropSpeed"] = (double)OptionData::playerData3.softDropSpeed;
    setting_map["3pRandomQueueDataIndex"] = (double)OptionData::playerData3.randomQueueDataIndex;
    setting_map["3pRandomizerType"] = (double)OptionData::playerData3.randomizerType;
    setting_map["3pMoveLeft"] = (double)OptionData::playerData3.moveLeft;
    setting_map["3pMoveRight"] = (double)OptionData::playerData3.moveRight;
    setting_map["3pRotateLeft"] = (double)OptionData::playerData3.rotateLeft;
    setting_map["3pRotateRight"] = (double)OptionData::playerData3.rotateRight;
    setting_map["3pSoftDrop"] = (double)OptionData::playerData3.softDrop;
    setting_map["3pHardDrop"] = (double)OptionData::playerData3.hardDrop;
    setting_map["3pHold"] = (double)OptionData::playerData3.hold;

    // player4 settings
    setting_map["4pGhost"] = (double)OptionData::playerData4.ghost;
    setting_map["4pHolder"] = (double)OptionData::playerData4.holder;
    setting_map["4pDasDelayTime"] = (double)OptionData::playerData4.dasDelayTime;
    setting_map["4pHorizontalSpeed"] = (double)OptionData::playerData4.horizontalSpeed;
    setting_map["4pNormalDropSpeed"] = (double)OptionData::playerData4.normalDropSpeed;
    setting_map["4pSoftDropSpeed"] = (double)OptionData::playerData4.softDropSpeed;
    setting_map["4pRandomQueueDataIndex"] = (double)OptionData::playerData4.randomQueueDataIndex;
    setting_map["4pRandomizerType"] = (double)OptionData::playerData4.randomizerType;
    setting_map["4pMoveLeft"] = (double)OptionData::playerData4.moveLeft;
    setting_map["4pMoveRight"] = (double)OptionData::playerData4.moveRight;
    setting_map["4pRotateLeft"] = (double)OptionData::playerData4.rotateLeft;
    setting_map["4pRotateRight"] = (double)OptionData::playerData4.rotateRight;
    setting_map["4pSoftDrop"] = (double)OptionData::playerData4.softDrop;
    setting_map["4pHardDrop"] = (double)OptionData::playerData4.hardDrop;
    setting_map["4pHold"] = (double)OptionData::playerData4.hold;
}
