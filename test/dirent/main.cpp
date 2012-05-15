#include <iostream>
#include <dirent.h>

int main(int argc, char **argv)
{
    DIR *dir = opendir(argv[1]);
    if (dir){
	while (dirent *d = readdir(dir)){
	    std::cout << d->d_ino << " " << d->d_name << "\n";
	}
    }
    closedir(dir);
    return 0;
}
