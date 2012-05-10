#include <iostream>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "randomqueue.h"

void printRandomQueue(RandomQueue &randomQueue){
    for (RandomQueue::iterator iter = randomQueue.begin();
	 iter != randomQueue.end(); ++iter){
	std::cout << *iter << " ";
    }
    std::cout << "\n";
}

int main()
{
    std::srand(std::time(NULL));

    RandomQueueData randomQueueData(new BagRandomizer());
    RandomQueue randomQueue0(&randomQueueData);
    RandomQueue randomQueue1(&randomQueueData);
    
    randomQueueData.print();
    printRandomQueue(randomQueue0);
    printRandomQueue(randomQueue1);
    
    randomQueue0.pop();
    randomQueue0.pop();
    randomQueue0.pop();
    randomQueue1.pop();
    randomQueue1.pop();
    
    randomQueueData.print();    
    printRandomQueue(randomQueue0);
    printRandomQueue(randomQueue1);
    
    randomQueue1.pop();
    randomQueue1.pop();
    randomQueue1.pop();
    
    randomQueueData.print();    
    printRandomQueue(randomQueue0);
    printRandomQueue(randomQueue1);
    
    
    std::cout << std::endl;
    return 0;
}
