#include "filena.h"

Allfilename::Allfilename(){
	dp=opendir("./musics");
	while (((dirp=readdir(dp))!=NULL))
				{
					allname.push_back(dirp->d_name);
				}
	std::vector<std::string>::iterator it;
	int i = 0;
	for(it=allname.begin();it!=allname.end();){
		if((*it)==".."||(*it)=="."){
			allname.erase(it);
			++i;
		}
		else
			++it;
		if(i==2)
			break;
	}
}

Allfilename::~Allfilename(){
	closedir(dp);
}

void Allfilename::show(){
	ofstream fstr("music.txt");
	for(int i=0;i<allname.size();++i){
		std::cout<<allname[i]<<std::endl;
		fstr<<allname[i]<<std::endl;
	}
	fstr.close();
}

std::string Allfilename::get_name(int n){
	return allname[n];
}

int Allfilename::num_musics(){
	return allname.size();
}

