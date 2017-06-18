#include <cstdlib>
#include <cmath>
#include <iostream>
#include <ctime>
#include <iomanip>
#define LAMBDA 0.5
#define RANGE 0.4
#define STAR 20
using namespace std;
double exponential(double lambda);
void InsertData(double time);
double arrivalTime[100000];
int totalArrival = 0;
int main()
{
    srand(time(NULL));
    double time = 0;
    int statistics[1000] = {0};
    for(int i = 0; i < 100000; i++)
    {
        arrivalTime[i] = -1;
    }
    for(int i = 0; i < 100000 && time < 10000; i++)
    {
        InsertData(time);
        totalArrival++;
        double interval = exponential(LAMBDA);
        statistics[(int)(interval / RANGE)]++;
        time += interval;
    }
    //cout << exponential(0.5) << endl;
    for(int i = 0; i < 25; i++)
    {
        cout << "--Interval among " << RANGE * i << " to " << RANGE * (i + 1) << " minutes:" << endl;;
        for(int j = statistics[i]; j > 0; j -= STAR)
        {
            cout << "*";
        }
        cout << endl;
    }
    cout << "Total Arrival: " <<totalArrival << " during 10000 minutes, mean: " << totalArrival / (double) 10000 << endl;;
    system("pause");
    return 0;
}
double exponential(double lambda)
{
    double u;
    u = rand() / (RAND_MAX + 1.0);
    //return ceil(-log(1 - u) / lambda);
    return -log(-u + 1) / (double)lambda;
}
void InsertData(double time)
{
    	for (int i = 0; i < 100000; i++)
	{
		if (arrivalTime[i] < time && arrivalTime[i] != -1)
		{
			continue;
		}
		else
		{
			for (int j = 9999; j > i; j--)
			{
				arrivalTime[j] = arrivalTime[j - 1];
			}
			arrivalTime[i] = time;
			break;
		}
	}
}
