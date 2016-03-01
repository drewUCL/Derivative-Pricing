#ifndef _ _EUROPEANOPTION_HPP // europeanOption.hpp
#define _ _EUROPEANOPTION_HPP //define what this class is called using the file name
#include <iostream>

class EuropeanOption { //this is a class called EuropeanOption. We can use this in conjunction with an object, such as putOptionD which is used for contract 2
public: //these are variables of type double that are indeed public within the class EuropeanOption
	double r; //interest rate
	double sig; //volatility
	double K; //Strike price
	double T; //expiry date
	double S; //current underlying price
	double b; //cost of carry

public:
	EuropeanOption(); //again these are member functions and do not need to be defined away from the variables. This style just makes the programme more readable. 
	double Price(); //a member function that can return a double, which will be the price

private: //these can only be accessed while in the cless and defined object
	void init(); //initialize all default values
	double PutPrice(); //private member function
};
#endif //end the definition of this class