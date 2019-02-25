#include <iostream>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include <queue>
#include <fstream>
#include <thread> // std::this_thread::sleep_for
#include <chrono>
using namespace std;

const static double percentage = 0.01;
const static int K = 5;

class processors
{
  public:
    int interval;
    double loadUnits;

    processors(int time, double load)
    {
        interval = time;
        loadUnits = load;
    }

    processors()
    {
        interval = 0;
        loadUnits = 0;
    }
};

bool inRange(double value, double range)
{
    double upperBound = range + (percentage * range);
    double lowerBound = range - (percentage * range);
    if ((value >= floor(lowerBound) || value >= ceil(lowerBound)) && (value <= floor(upperBound) || value <= ceil(upperBound)))
    {
        return true;
    }
    return false;
}

void balanceProcess(processors elements[], int elem)
{
    int p1 = (elem - 1) % K;
    if (elem == 0)
    {
        p1 = K - 1;
    }

    int p2 = (elem + 1) % K;
    bool noActions = false;
    double average = (elements[p1].loadUnits + elements[p2].loadUnits + elements[elem].loadUnits) / 3;
    while (!noActions)
    {
        noActions = true;
        //both less than p[i]
        cout << "calling in range from balance process" << endl;
        if ((elements[p1].loadUnits < average && !inRange(elements[p1].loadUnits, average)) && (elements[p2].loadUnits < average && !inRange(elements[p2].loadUnits, average)))
        {
            //distribute to both
            cout << "calling in range from balance process - first" << endl;
            elements[p1].loadUnits += 1;
            elements[p2].loadUnits += 1;
            elements[elem].loadUnits -= 2;
            noActions = false;
        }
        else if (elements[p1].loadUnits < average && !inRange(elements[p1].loadUnits, average))
        {
            cout << "calling in range from balance process - second" << endl;
            elements[p1].loadUnits += 1;
            elements[elem].loadUnits -= 1;
            noActions = false;
        }
        else if (elements[p2].loadUnits < average && !inRange(elements[p2].loadUnits, average))
        {
            cout << "calling in range from balance process - third" << endl;
            elements[p2].loadUnits += 1;
            elements[elem].loadUnits -= 1;
            noActions = false;
        }
        else if (elements[elem].loadUnits > average && inRange(elements[p2].loadUnits, average) && inRange(elements[p1].loadUnits, average))
        {
            cout << "calling in range from balance process - fourth" << endl;
            elements[p1].loadUnits += 1;
            elements[p2].loadUnits += 1;
            elements[elem].loadUnits -= 2;
            noActions = false;
        }
    }
}

bool isBalanced(processors elements[], int j)
{

    int p1 = (j - 1) % K;
    if (j == 0)
    {
        p1 = K - 1;
    }

    int p2 = (j + 1) % K;
    double average = (elements[j].loadUnits + elements[p1].loadUnits + elements[p2].loadUnits) / 3;

    cout << "calling in range from isBalanced" << endl;
    if (inRange(elements[p1].loadUnits, average) && inRange(elements[p2].loadUnits, average))
    {
        return true;
    }

    return false;
}

bool balancedSystem(processors elements[])
{
    cout << "**** in balanced system function ****" << endl;
    int balancedP = 0;
    int i;
    for (i = 0; i < K; i++)
    {
        if (isBalanced(elements, i))
        {
            balancedP++;
        }
    }

    if (balancedP == 0)
    {
        return false;
    }
    double val = (balancedP / K);

    if (val >= 0.9)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int loadBalancer(processors elements[])
{
    std::random_device device;
    std::default_random_engine loadGenerator(device());
    std::uniform_int_distribution<int> loadDistribution(100, 1000);
    int index;
    for (index = 0; index < K; index++)
    {
        int time = loadDistribution(loadGenerator);
        elements[index].interval = time;
    }
    int cycles = 0;
    int numElems = 0;
    while (!balancedSystem(elements))
    {
        cout << "current cycle is = " << cycles << endl;
        for (index = 100; index <= 1000; index++)
        {
            for (int n = 0; n < K; n++)
            {
                if (elements[n].interval == index)
                {
                    balanceProcess(elements, n);
                }
            }
        }
        cycles++;
        for (index = 0; index < K; index++)
        {
            int time = loadDistribution(loadGenerator);
            elements[index].interval = time;
        }
    }

    return cycles;
}

int main()
{
    processors elements[K];
    std::random_device device;
    std::default_random_engine generator(device());
    std::uniform_int_distribution<int> distribution(10, 1000);
    int cycles;
    int index;

    int numUnbalanced = 0;

    for (index = 0; index < K; index++)
    {
        int units = distribution(generator);
        elements[index].loadUnits = units;
        cout << "index = " << index << " units = " << elements[index].loadUnits << endl;
    }

    for (index = 0; index < K; index++)
    {
        int p1 = (index - 1);
        if (index == 0)
        {
            p1 = K - 1;
        }

        int p2 = (index + 1);
        p2 %= K;
        cout << "p - 1 = " << elements[p1].loadUnits << " p = " << elements[index].loadUnits << " p + 1 " << elements[p2].loadUnits << endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(10));

    cycles = loadBalancer(elements);
    cout << endl
         << endl
         << endl
         << "*** RESULTS ***";
    for (index = 0; index < K; index++)
    {
        int p1 = (index - 1);
        if (index == 0)
        {
            p1 = K - 1;
        }

        int p2 = (index + 1);
        p2 %= K;

        cout << "p - 1 = " << elements[p1].loadUnits << " p = " << elements[index].loadUnits << " p + 1 " << elements[p2].loadUnits << endl;
    }

    cout << "total cycles = " << cycles << endl;

    return 0;
}