#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;
int main()
{
    std::default_random_engine generator;
    std::poisson_distribution<int> distribution(4.1);
    for (int i=0; i<10; ++i)
    {
        int number = distribution(generator);
        cout<<number<<" "<<endl;
    }
    return 0;
}
