#include <cstdlib>
#include <cmath>
#include <iostream>
#include <ctime>
#define LAMBDA 1
#define MIU 0.2
using namespace std;

int exponential(double lambda);
double poison(double lambda, int time);
bool dice(double probability);
int main()
{

    srand(time(NULL));
    double lambdaForEachCell[13];
    double miuForEachCell[13];
    for(int i = 1; i <= 12; i++)
    {
        lambdaForEachCell[i] = LAMBDA * ((i % 4) + 1);
        miuForEachCell[i] = MIU * ((i % 4) + 1);
    }
    int ArrivalCount[13] = {0};
    int BlockCount[13] = {0};
    int TotalArrivalCount = 0;
    int TotalBlockCount = 0;
    int data[13][100] = {0};
    int lastArrive[13] = {0};
    for(int a = 1; a <= 12; a++)
    {
        for(int i = 0; i < 100;)
        {
            //bool isArrive = dice(poison(lambdaForEachCell[a], i - lastArrive[a]));
            int interval = exponential(lambdaForEachCell[a]);
            if(1)
            {
                TotalArrivalCount++;
                ArrivalCount[a]++;
                lastArrive[a] = i;
                if(data[a][i] >= 5)
                {
                    TotalBlockCount++;
                    BlockCount[a]++;
                    i += interval;
                    continue;
                }
                int serviceTime = exponential(miuForEachCell[a]);
                for(int j = 0; j < serviceTime && i + j < 100; j++)
                {
                    data[a][i + j]++;
                }
                i += interval;
                //system("pause");
            }
        }
    }
    for(int i = 1; i <= 12; i++)
    {
        cout << "--------------------------------------" << endl;
        cout << "In BS " << i << ":" << endl;
        cout << "lambda: " << lambdaForEachCell[i] << endl;
        cout << "miu: " << miuForEachCell[i] << endl;
        cout << "Channel used in each minute:" << endl;
        for(int j = 0; j < 100; j++)
        {
            cout << data[i][j];
        }
        cout << endl;
        cout << "Arrivals: " << ArrivalCount[i] << endl;
        cout << "Blocks: " << BlockCount[i] << endl;
    }
    cout << "--------------------------------------" << endl;
    cout << "Total Arivial Count: " << TotalArrivalCount << endl;
    cout << "Total Block Count: " << TotalBlockCount << endl;
    cout << "Average Blocking Probability: " << TotalBlockCount / (double)TotalArrivalCount * 100 << "%" << endl;
    system("pause");
    return 0;
}
double poison(double lambda, int time)
{
    int k = 1;
    for(int i = time; i > 0; i--)
    {
        k *= i;
    }
    return pow(2.718281828, -lambda) * pow(lambda, time) / k;
}
int exponential(double lambda){
    double u;
    u = rand() / (RAND_MAX + 1.0);
    //return ceil(-log(1 - u) / lambda);
    return ceil(-log(-u + 1) / lambda);
}
bool dice(double probability)
{
    if(rand() / (double)RAND_MAX > probability)
    {
        return true;
    }
    else
    {
        return false;
    }
}
