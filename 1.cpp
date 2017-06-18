#include <cstdlib>
#include <cmath>
#include <iostream>
#include <ctime>
using namespace std;
double poison(double lambda, int time);
bool dice(double probability);
void outprint(bool data[10000], double lambda);
int exponential(double lambda);
int main()
{
    srand(time(NULL));
    cout << "arrival rate = 0.5" << endl;
    bool channel[10000];
    int lambda = 0.5;
    int lastcome = 0;
    cout << "time of each arrival:" << endl;
    //Sleep(2000);
    for(int i = 0; i < 10000;)
    {
        cout << i << " ";
        int interval = exponential(2);
        channel[i + interval] = true;
        i = i + interval;
    }
    cout << endl;
    /*
    for(int i = 0; i < 10000; i++)
    {
        channel[i] = dice(poison(lambda, i - lastcome));
        if(channel[i] == true)
        {
            lastcome = i;
        }
    }
    */
    outprint(channel, lambda);
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
bool dice(double probability)
{
    if(rand()/(double)RAND_MAX > probability)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int exponential(double lambda){
    double u;
    u = rand() / (RAND_MAX + 1.0);
    //return ceil(-log(1 - u) / lambda);
    return ceil(-log(-u + 1) / lambda);
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
    int count[10] = {0};
    for(int i = 1, lastcome = 0; i < 10000; i++)
    {
        if(data[i] == true)
        {
            count[i - lastcome]++;
            lastcome = i;
        }
    }
    cout << "----------------------" << endl;
    cout << "arrivial interval: " << endl;
    for(int i = 1; i < 10; i++)
    {
        cout << "interval = " << i << ": " << count[i] << endl;
        for(int j = 0; j < count[i]; j = j + 100)
        {
            cout << "*";
        }
        cout << endl;
    }
}
