#include <algorithm>

#include "randomizer.h"

BagRandomizer::BagRandomizer():
    current(bag + blockPackageSize)
{
    for (int i = 0; i != blockPackageSize; ++i)
	bag[i] = i;
}

int BagRandomizer::get()
{
    if (current == bag + blockPackageSize){
	current = bag;
	std::random_shuffle(bag, bag + blockPackageSize);	
    }
    return *current++;
}

