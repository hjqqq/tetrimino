#include <iostream>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "randomqueue.h"

int main()
{
    std::srand(std::time(NULL));
    int history[4] = {5, 3, 5, 3};
    RandomQueue bagRandomQueue(new BagRandomizer());
    RandomQueue historyRandomQueue(new HistoryRollRandomizer<4>(history));

    std::ostream_iterator<int> outputIter(std::cout, " ");

    for (int i = 0; i != 14; ++i){
	std::copy(historyRandomQueue.begin(), historyRandomQueue.end(),
		  outputIter);
	historyRandomQueue.pop();
	std::cout << "\n";
    }
    return 0;
}
