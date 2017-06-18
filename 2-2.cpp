// ConsoleApplication1.cpp : 定義主控台應用程式的進入點。
//

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <ctime>
#include <iomanip>
#define LAMBDA 1
#define MIU 0.2
using namespace std;
double exponential(double lambda);
void InsertData(int BS, double time);
struct event
{
	double time;
	int BS;
};
struct event arrivalTime[10000];
int main()
{
	int friendCell[13][6] =
	{ 0, 0, 0, 0, 0, 0,
	  8, 3, 2, 0, 0, 0,//BS1
	  1, 3, 10, 0, 0, 0,//BS2
	  1, 2, 4, 5, 8, 10,//BS3
	  3, 5, 6, 8, 9, 0,
	  3, 4, 6, 10, 12, 0,
	  4, 5, 0, 0, 0, 0,
	  8, 9, 0, 0, 0, 0,
	  1, 3, 4, 7, 9, 0,
	  4, 7, 8, 0, 0, 0,
	  2, 3, 5, 11, 12, 0,
	  10, 12, 0, 0, 0, 0,
	  5, 10, 11, 0, 0, 0 };

	int TotalArrivalCount = 0;
	int TotalBlockCount = 0;
	int arrivalCount[13] = { 0 };
	int blockCount[13] = { 0 };
	double channelBusy[13][5] = {0};
	srand(time(NULL));
	for (int i = 0; i < 10000; i++)
	{
		arrivalTime[i].time = -1;
	}
	double lambdaForEachCell[13];
	double miuForEachCell[13];
	for (int i = 1; i <= 12; i++)
	{
		lambdaForEachCell[i] = LAMBDA * ((i % 4) + 1);
		miuForEachCell[i] = MIU * ((i % 4) + 1);
	}
	for (int i = 1; i <= 12; i++)
	{
		double time = 0;
		for (int j = 0; time < 100; j++)
		{
			InsertData(i, time);
			TotalArrivalCount++;
			arrivalCount[i]++;
			double interval = exponential(lambdaForEachCell[i]);
			time += interval;
		}
	}
	for (int i = 0; i < 10000 && arrivalTime[i].time != -1; i++)
	{
		double interval = exponential(miuForEachCell[arrivalTime[i].BS]);
		for (int j = 0; j < 5; j++)
		{
			if (channelBusy[arrivalTime[i].BS][j] > arrivalTime[i].time)
			{
				if (j == 4)
				{
					//cout << std::setprecision(8) << "Overload: " << arrivalTime[i].BS << " at time " << arrivalTime[i].time << endl;
					//TotalBlockCount++;
					//blockCount[arrivalTime[i].BS]++;

					int available[6] = { 0 };
					for (int a = 0; a < 6 && friendCell[arrivalTime[i].BS][a] != 0; a++)//friend seq
					{
						for (int b = 0; b < 5; b++)//channel seq
						{
							if (channelBusy[friendCell[arrivalTime[i].BS][a]][b] < arrivalTime[i].time)
							{
								available[a]++;
							}
						}
					}
					int select = 0;
					int max = 0;
					for (int a = 0; a < 6; a++)
					{
						if (available[a] > max)
						{
							max = available[a];
							select = friendCell[arrivalTime[i].BS][a];
						}
					}
					if (max == 0)
					{
						cout << std::setprecision(8) << "Block:  " << arrivalTime[i].BS << " at time " << arrivalTime[i].time << ", friend channel idle remain: " << available[0] << available[1] << available[2] << available[3] << available[4] << available[5] << endl;
						TotalBlockCount++;
						blockCount[arrivalTime[i].BS]++;
					}
					else
					{
						for (int a = 0; a < 5; a++)
						{
							if (channelBusy[select][a] < arrivalTime[i].time)
							{
								channelBusy[select][a] = arrivalTime[i].time + interval;
								cout << std::setprecision(8) << "Borrow: from " << select << " to " << arrivalTime[i].BS << " at " << arrivalTime[i].time << ", friend channel idle remain: " << max << ", using channel " << ((select - 1) % 3) * 5 + a + 1 << ", return time: " << channelBusy[select][a] << endl;
								break;
							}
						}
					}

				}
				continue;
			}
			else
			{
				channelBusy[arrivalTime[i].BS][j] += interval;
				break;
			}
		}
	}
	for (int i = 1; i <= 12; i++)
	{
		cout << "BS" << i << " Arrival: " << arrivalCount[i] << " Block: " << blockCount[i] << endl;
	}
	cout << "Total Arrival: " << TotalArrivalCount << " Total Block: " << TotalBlockCount << endl;
	cout << "Blocking probability: " << TotalBlockCount / (double)TotalArrivalCount * 100 << "%" << endl;
	system("pause");
	return 0;
}
void InsertData(int BS, double time)
{
	for (int i = 0; i < 10000; i++)
	{
		if (arrivalTime[i].time < time && arrivalTime[i].time != -1)
		{
			continue;
		}
		else
		{
			for (int j = 9999; j > i; j--)
			{
				arrivalTime[j].BS = arrivalTime[j - 1].BS;
				arrivalTime[j].time = arrivalTime[j - 1].time;
			}
			arrivalTime[i].BS = BS;
			arrivalTime[i].time = time;
			break;
		}
	}
}
double exponential(double lambda) {
	double u;
	u = rand() / (RAND_MAX + 1.0);
	//return ceil(-log(1 - u) / lambda);
	return -log(-u + 1) / (double)lambda;
}
