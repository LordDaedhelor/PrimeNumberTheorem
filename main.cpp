#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <string>
#include <sys/time.h>
#include <sstream>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

bool isPrime(int n)
{ 
    //This function was not written by me and was found at 
    //https://www.geeksforgeeks.org/primality-test-set-1-introduction-and-school-method/

    if (n <= 1) {return false;}
    if (n <= 3) {return true;} 
   
   	if (n%2 == 0 || n%3 == 0) {return false;}
  
    for (int i = 5; (i * i) <= n; i = i + 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
        {
           return false;
        }
    }

    return true; 
}

int calcNumPrimes(int n)
{
	int numPrimes = 0;
	for (int i = 0; i <= n; i++)
	{
		if (isPrime(i))
		{
			numPrimes++;
		}
	}
	return numPrimes;
}

double primeNumberTheorem(double n)
{
	double LegendreConstant = -1.08366;

	if (n <= 1000)
	{
		return (n / (log(n) - 1));
	}
	else if (n <= 1000000)
	{
		return (n / (log(n) + LegendreConstant));
	}
	else
	{
		return (n / log(n));
	}
}

long getTimeDiff(struct timeval * tp1, struct timeval * tp2)
{
	long sec = tp2->tv_sec - tp1->tv_sec;
	long musec = tp2->tv_usec - tp1->tv_usec;
	
	if (musec < 0)
	{
		musec += (int)1e6;
		sec--;
	}

	long time = (sec * 1000000) + musec;
	return time;
}

void output(int n)
{
	struct timeval cNPStart, cNPEnd;
	gettimeofday(&cNPStart, 0);
	cout << "The number of primes below " << n << " is " << calcNumPrimes(n) << endl;
	gettimeofday(&cNPEnd, 0);

	struct timeval pNTStart, pNTEnd;
	gettimeofday(&pNTStart, 0);
	cout << "The number of primes below " << n << " calculated by the PNT is approximately " << round(primeNumberTheorem(n)) << endl;
	gettimeofday(&pNTEnd, 0);

	cout << endl;

	cout << "Time to calculate the number of primes: ";
	cout << getTimeDiff(&cNPStart,&cNPEnd) << " microseconds" << endl;

	cout << "Time to use the Prime Number Theorem: ";
	cout << getTimeDiff(&pNTStart,&pNTEnd) << " microseconds" << endl;
}

void outputAverageToFile()
{
	struct timeval cNPStart, cNPEnd, pNTStart, pNTEnd;
	int cnp, pnt;
	ofstream outfile;
	outfile.open("data.csv", ios::out | ios::trunc);
	for (int j = 0; j < 50; j++)
	{
		gettimeofday(&cNPStart, 0);
		cnp = calcNumPrimes(1000000);
		gettimeofday(&cNPEnd, 0);


		gettimeofday(&pNTStart, 0);
		pnt = primeNumberTheorem(1000000);
		gettimeofday(&pNTEnd, 0);
		
		outfile << 1000000 << "," << cnp << "," << pnt << "," << getTimeDiff(&cNPStart,&cNPEnd) << "," << getTimeDiff(&pNTStart,&pNTEnd) << "\n";
	}
	outfile.close();
}

void outputDifferenceToFile()
{
	struct timeval cNPStart, cNPEnd, pNTStart, pNTEnd;
	int cnp, pnt;
	ofstream outfile;
	outfile.open("data3.csv", ios::out | ios::trunc);
	for (int i = 10000; i <= 1000000; i += 10000)
	{
		cnp = calcNumPrimes(i);
		pnt = primeNumberTheorem(i);
		outfile << i << "," << cnp << "," << pnt << "\n";
	}
	outfile.close();
}

int main (int argc, char ** argv)
{
	int opt;
	int n = 100;
	while((opt = getopt(argc, argv, "n:")) != -1)
	{
		switch(opt)
		{
			case 'n':
				n = atoi(optarg);
				break;
			default:
				break;
		}
	}

	output(n);

	//outputAverageToFile();

	//outputDifferenceToFile();
}
