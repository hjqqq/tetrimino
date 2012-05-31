#!/usr/bin/env python

import os, re

menuDirs = ["header/menu", "src/menu"]
soundDirs = ["header/sound", "src/sound"]
gameDirs = ["header/game", "src/game"]
globaldataDirs = ["header/globaldata", "src/globaldata"]
utilityDirs = ["header/utility", "src/utility"]

allDirs = ["header", "src"]

filenameRegex = ".*\.(cpp|h)$"
count = 0
totalCount = 0;

def countFile(filename):
    f = open(filename)
    return len(f.readlines())

def countDirs(dirs):
    global count
    for currentDir in dirs:
        if os.path.isdir(currentDir):
            countDirs([currentDir + "/" + d for d in os.listdir(currentDir)])
        else:
            if re.match(filenameRegex, currentDir):
                count += countFile(currentDir)
                #print currentDir
        
def main():
    global count
    
    currentDir = os.getcwd()
    
    dirs = [currentDir + "/" + d for d in menuDirs]
    countDirs(dirs)
    print "total menu lines:", count;
    count = 0

    dirs = [currentDir + "/" + d for d in soundDirs]
    countDirs(dirs)    
    print "total sound lines:", count;
    count = 0

    dirs = [currentDir + "/" + d for d in gameDirs]
    countDirs(dirs)    
    print "total game lines:", count;
    count = 0

    dirs = [currentDir + "/" + d for d in globaldataDirs]
    countDirs(dirs)    
    print "total globaldata lines:", count;
    count = 0

    dirs = [currentDir + "/" + d for d in utilityDirs]
    countDirs(dirs)    
    print "total utilitydata lines:", count;
    count = 0

    dirs = [currentDir + "/" + d for d in allDirs]
    countDirs(dirs)    
    print "total lines:", count;
    
    return 0

if __name__ == "__main__":
    main()
