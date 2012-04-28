#!/usr/bin/env python

import os, re

searchDirs = ["header", "src"]
filenameRegex = ".*\.[c|cpp|h]"
count = 0

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
                print currentDir
        
def main():
    currentDir = os.getcwd()
    dirs = [currentDir + "/" + d for d in searchDirs]
    countDirs(dirs)
    print "total lines: ", count
    return 0

if __name__ == "__main__":
    main()
