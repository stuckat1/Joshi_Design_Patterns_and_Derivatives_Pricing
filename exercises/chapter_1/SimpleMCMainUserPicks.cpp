//
//
//	          	SimpleMCMainUserPicks.cpp
//
//     
//       requires Random1.cpp

#include <Random1.h>
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

double SimpleMonteCarloOption(double Expiry, 
								double Strike, 
								double Spot, 
								double Vol, 
								double r,
								bool isCall,
								unsigned long NumberOfPaths)
	{

	double variance = Vol*Vol*Expiry;
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5*variance;

	double movedSpot = Spot*exp(r*Expiry +itoCorrection);
	double thisSpot;
	double runningSum=0;

	for (unsigned long i=0; i < NumberOfPaths; i++)
	{
		double thisGaussian = GetOneGaussianByBoxMuller();
		thisSpot = movedSpot*exp( rootVariance*thisGaussian);
		double thisPayoff = isCall ? Strike - thisSpot : thisSpot - Strike;
    	thisPayoff = thisPayoff >0 ? thisPayoff : 0;
		runningSum += thisPayoff;
	}

	double mean = runningSum / NumberOfPaths;
	mean *= exp(-r*Expiry);
	return mean;
}

int main()
{

	double Expiry;
	double Strike; 
	double Spot; 
	double Vol; 
	double r; 
	unsigned long NumberOfPaths;
	string optionType;

	cout << "\nEnter an option type [call or put]\n";
	cin >> optionType;

	cout << "\nEnter expiry\n";
	cin >> Expiry;

	cout << "\nEnter strike\n";
	cin >> Strike;

	cout << "\nEnter spot\n";
	cin >> Spot;

	cout << "\nEnter vol\n";
	cin >> Vol;

	cout << "\nr\n";
	cin >> r;

	cout << "\nNumber of paths\n";
	cin >> NumberOfPaths;
	 
	double result = SimpleMonteCarloOption(Expiry,
											Strike, 
											Spot, 
											Vol, 
											r,
											0 == optionType.compare("call"),
											NumberOfPaths);

	cout <<"the price is " << result << "\n";

    double tmp;
    cin >> tmp;

	return 0;
}

/*
 *
 * Copyright (c) 2002
 * Mark Joshi
 *
 * Permission to use, copy, modify, distribute and sell this
 * software for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Mark Joshi makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
*/

