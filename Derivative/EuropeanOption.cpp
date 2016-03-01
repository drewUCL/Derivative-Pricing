#include "europeanOption.h" // EuropeanOption.cpp
#include "Fns.cpp" // has to be *.cpp to include the CND for the probability factor generation
#include<math.h> //math library for C++ allowing more than the usual operations with the iostream
using namespace std; //using this allows us not to use ::cout etc to access the console

double EuropeanOption::PutPrice(){ //accessing the private member function of the class EuropeanOption
	double tmp = sig * sqrt(T); //Volatility multiplied by the square root of maturity.
	double d1 = (log(S/K) + (b + (sig*sig)*0.5)*T)/tmp; //BS standard d1 term (Full Explanation: Section 1.2)
	double d2 = d1 - tmp; //BS standard d2 term (Full Explanation: Section 1.2)
	return (-S*exp((b-r)*T)*CND(-d1) + K*exp(-r*T)*CND(-d2)); //return the put price via Black-Scholes
}

void EuropeanOption::init() { //initialize all default values, these are the default values of the class EuropeanOption
	r=0.08;
	sig = 0.30;
	K=65.0;
	T=0.25;
	S=60.0;
	b=r;
}

EuropeanOption::EuropeanOption(){ // default put option
	init(); //for a default put option, basically initialise the 
}

//Functions that calculates option prices and sensitivities
double EuropeanOption::Price(){ //accessing the public member function of the class EuropeanOption
	return PutPrice(); //member function called PutPrice(). This is called and returns the option price via 'Fns' and europeanOption.h files and the user input within the main().
}