#ifndef _file_H
#define _file_H
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <stdio.h>
#include <errno.h>
#include <string>
#include <iostream>
#include <fstream.h>
class Allfilename{
private:
	DIR *dp;
	struct dirent *dirp;
	std::vector<std::string> allname;

public:
	Allfilename();
	~Allfilename();
	void show();
	std::string get_name(int);
	int num_musics();

};

#endif
