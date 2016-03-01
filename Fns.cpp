#include "Fns.h" // Fns.cpp
#include <math.h> //allowing more than the simple mathematical operations
#include<stddef.h> // this defines the macros NULL and the offsetof. It also includes the types ptrdiff_t, wchar_t, and the size_t. these are used in the algorithim and template Numeric.
using namespace std;  //allows us not to use :: to access the console

template <class Numeric> //this is a header with algorithims that generate a number of sequences of numeric type values

//this function exhibits the probability that a random variable (real) with given probability distribution will be found somewhere in this distribution with a value less than or infact equal to the real variable

// the black and scholes equation uses this as the random part of the equation to generate a probability function (explained in user manual, section 1,2). this is how a probability is introduced into the equation, which is essential when modelling asset values as these are unpredictable
Numeric CND(const Numeric& d){  //using the class Numeric and creating the object CND which feeds in a constant "Numeric& d". The & operator is a uniray address operator detailing an address in Numeric of the variable d. d in this case relates to d1 or d2 of the Balck-Scholes formula. This is called passing by reference and allows us not to spend time with pointers.
	const double A1=0.31938153; //The A's are coefficients
	const double A2=-0.356563782; //this creats a constant double type meaning that the value cannot be change throughout the calculation
	const double A3=1.781477937; 
	const double A4=-1.821255978;
	const double A5=1.330274429;
	const double RSQRT2PI=0.39894228040143267793994605993438;
	double tmp = 1.0 / (1.0 + 0.2316419 * fabs(d));
	double cnd = RSQRT2PI*exp(-0.5*d*d)*(tmp*(A1+tmp*(A2+tmp*(A3+tmp*(A4+tmp*A5)))));
if (d>0) //logic that says, if it is positive, take the value away from 1
	cnd = 1.0 - cnd;
return cnd; // this returns the final Cumulative Normal Distribution which will aid in the generation of a probability factor.
}