#include <cstdlib>
#include <cmath>
#include <iostream>
#include <ctime>
#define LAMBDA 1
#define MIU 0.2
using namespace std;
double poison(double lambda, int time);
bool dice(double probability);
void outprint(bool data[10000], double lambda);
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
					cout << "Block: " << arrivalTime[i].BS << " " << arrivalTime[i].time << endl;
					TotalBlockCount++;
					blockCount[arrivalTime[i].BS]++;
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
		cout << "BS" << i << " Arrival: " << arrivalCount[i] << " Block: " << blockCount[i] << " lambda: " << lambdaForEachCell[i] << " miu: " << miuForEachCell[i] << endl;
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
double poison(double lambda, int time)
{
	int k = 1;
	for (int i = time; i > 0; i--)
	{
		k *= i;
	}
	return pow(2.718281828, -lambda) * pow(lambda, time) / k;
}
bool dice(double probability)
{
	if (rand() / (double)RAND_MAX > probability)
	{
		return true;
	}
	else
	{
		return false;
	}
}
double exponential(double lambda) {
	double u;
	u = rand() / (RAND_MAX + 1.0);
	//return ceil(-log(1 - u) / lambda);
	return -log(-u + 1) / (double)lambda;
}
void outprint(bool data[10000], double lambda)
{
	/*
	cout << "poison distribution:" << endl;
	for(int i = 0; i < 10; i++)
	{
	cout << "k = " << i << ": ";
	for(double j = poison(lambda, i); j > 0; j = j - 0.01)
	{
	cout << "*";
	}
	cout << endl;
	}
	*/
	int count[10] = { 0 };
	for (int i = 1, lastcome = 0; i < 10000; i++)
	{
		if (data[i] == true)
		{
			count[i - lastcome]++;
			lastcome = i;
		}
	}
	cout << "----------------------" << endl;
	cout << "arrival interval: " << endl;
	for (int i = 1; i < 10; i++)
	{
		cout << "interval = " << i << ": " << count[i] << endl;
		for (int j = 0; j < count[i]; j = j + 100)
		{
			cout << "*";
		}
		cout << endl;
	}
}

