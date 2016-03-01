/* 
C++ IN FINANCE

Author: Andrew D. Mann
_______________________________________________________________________________________________
*/

#include "europeanOption.h" // This file includes the definitions for the object EuropeanOption allowing the data type and member functions to be implemented
#include "Fns.h" // This is a header file that ocntains the numerical template for the Cumilative Normal Distribution
#include <iostream> //This is the library that allows user input (cin and cout)
#include <math.h> // This is included so that more complicated mathematics can be performed. This is essentially the library for mathematical operations
#include <fstream> // Including this so that I can save the contract specifications
#include <ctime> //for printing the time that a contract was generated. This is essential as the contracts price will change rapidly over the course of the day
#include <string> //Used for user input strings. this will however be rejected as the system logic works on 1 and 0. 
using namespace std; // This means that we do not need to use, for example: std::cout, everytime we want a user input

int main () { //starting the main function where the programme will run out of

	int choice; // initializing some variables that I will be using throughout the programme 
	int currency; // This is a variable that is used to identify the currency throughout the system, including printing the contract specification
	const char* USD = " USD"; // for pricing in $
	const char* GBP = " GBP"; //As £ symbol does not show on the console
	const char* JPY = " JPY"; //As symbol does not show
	const char* YUAN = " CNY"; //As symbol does not show
	const char* workCurrency; // this constant character ** that cannot be modified ** is a tool to alow the contract to be priced in the currency of choice as well as seving the specifications with a currency code. this is essential when pricing an option

/**********************************************   LOOPING   **********************************************/
	LOOP: do { // A DO / WHILE loop is implemented. The follwoing will be done: while (choice is 1 OR 2 OR 3 OR 4 OR 5)
/**********************************************   CURRENCY   **********************************************/
	cout << "\nPLEASE ENTER THE CURRENCY YOU WISH TO WORK WITH:" << endl; // Asking for user input on the following currencies they wish to work with
	cout << "1. USD" << endl;  //USD is the most common currency to price an option with
	cout << "2. GBP" << endl;  // British Sterling
	cout << "3. YEN" << endl;  // Japanese
	cout << "4. YUAN" << endl; // Chinese currency
AGAIN1: // A 'goto' function is used as an error handler. "Throw, catch(char*error)" could have been used, however as we are dealing with numerical and string errors, the code is shorter and more optimised when using this format
	cout << "\nENTER THE CURRENCY NUMBER YOU WISH TO WORK WITH TO CONTINUE:" << ends;  //this outputs to the console
	cin >> currency;  //Now the user must choose the surrency they wish to work with
		if (currency == 1) {  //this logic is used throughout this selection and will assign different parameters to the contract dependant on the choice (currency)
			workCurrency = USD; //work currency will add the currency to the user interface allowing an ease of use while pricing the contract
		}else if (currency == 2) {
			workCurrency = GBP;
		}else if (currency == 3){
			workCurrency = JPY;
		}else if (currency == 4){
			workCurrency = YUAN;
		}else if (currency != 1 || 2 || 3 || 4 || (!(cin >> currency))) {  //Error handling. If the user has not inputted any of the accepted options, the user will be directed to this loop, the programme will output the error message and go to AGAIN1. The user can only get past this point after inputting a correct value 
			cout << "\nYOU MUST ENTER A CORRESPONDING NUMBER" << endl; //Error message
			cin.clear(); //This resets any error tags that may have occurred. In this case there will have been an error to get to this point
			cin.ignore(100, '\n'); // This line of code extracts & discards the data from the stream within the programme while passing in a new line. In this case it will extract up to 100 characters and output a newline.
			cout << "PLEASE ENTER A VALID CHOICE:\n";
			goto AGAIN1;  //Will revert the system back to AGAIN1 where the programme will start reading downwards (essentially allows he user to make multiple errors)
			};

	cout << "PLEASE CHOOSE A CONTRACT OF YOUR CHOICE:" << endl; //outputting to the console
	cout << "\n" << endl;  //ensuring an extra space between the choices and contract definition
	cout << "1. UNDERLYING ASSET WITH NO DIVIDENDS" << endl;
	cout << "2. ASSET WHICH PAYS A DIVIDEND" << endl;
	cout << "3. ON FOREIGN CURRENCY BOND WITH INTEREST RATE (RF)" << endl;
	cout << "4. ON COMMODITY WITH STORAGE COST" << endl;
	cout << "5. ON A FUTURES CONTRACT" << endl;
AGAIN2:  //error handling, this will be reverted to if user does not enter a choice from 1 to 5. Any other value, the programme will go back to the point and ask the user to re enter the data, from the list.
	cout << "\nPLEASE ENTER THE NUMBER CORRESPONDING TO THE CONTRACT YOU WISH TO PRICE:" << ends; //Outputting to the console
	cin >> choice;  //This variables, choice, is the variable that will carry the numbers 1 to 5. the use of 'if/else' logic is implemented. this is how the programme differentiates what contract parameters to price
/*******************************************   ERROR HANDLING   *******************************************/
		if (choice == 1) { // If the user chooses to price the first contract, please go to BASE_CAMP
			goto BASE_CAMP; //Base camp is essentially the start of the contract specifications. This acts as an anchor to the programme
		}else if (choice == 2) { //The same logic is used for contract one to five
			goto BASE_CAMP;
		}else if (choice == 3){
			goto BASE_CAMP;
		}else if (choice == 4){
			goto BASE_CAMP;
		}else if(choice == 5){
			goto BASE_CAMP;
		}else if (choice != 1 || 2 || 3 || 4 || (!(cin >> choice))) { //The initiation of error handling. This statement says that if the user has typed a choice not relation to the list, the system will project an error message
			cout << "\nYOU MUST ENTER A CORRESPONDING NUMBER" << endl; //Alerting the user that there has been a fault
			cin.clear(); //**Same logic as discussed above**
			cin.ignore(100, '\n'); //**Same logic as discussed above**
			cout << "PLEASE ENTER A VALID CHOICE:\n"; //Now the user must try to select another contract that is valid
			goto AGAIN2; //instating this allows the system to go beck to the initialisation of this user input allowing the user to make multiple errors without affecting the speed of processing
			}; //If the following error has occurred, please go back to the start to price again
	
// The above safe gaurds the currency choice. The user can only type 1 to 5 as a selection for the programme to continue.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************   1. ZERO DIVIDEND CONTRACT   **********************************************/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
BASE_CAMP: //This is the main point of the programme. It ankors the start of the programme to the latter section of the programme.
	if (choice == 1) {  //Contract One, if the user has inputted a 1 for their choice (integer that was defined at the start of the programme), this section of the loop will be implemented
		cout << "\nPUT OPTION: ZERO DIVIDEND ASSET: " << endl; //Outputting to the console
		EuropeanOption putOption0;  //creating an object called putOption0 from the class EuropeanOption
RETRY:  //base point from which to handle errors. the programme will revert back to this point if an error occurs in the asset pricing (i.e. the input is negative or !number)
		cout << "\nPLEASE ENTER THE ASSET PRICE: " << workCurrency << ends;
		cin >> putOption0.S; // asking the user for an input. this is the stock price (asset price). essentially what is happening is that the input is repated to the object and the use of a 'dot' allows the input to access europeanOption.h where the data type is.
		cout << endl; // Ensuring there is a gap between each user input. This allows the system to be more user friendly

		while (!cin){ //If the user interes a wrong valie that is not a number this while loop is used. This line states that if the user has not inputed the correct value (if not input >>>> if not expected input)
			cout << "MUST BE NUMERIC" << endl; //Message telling the user what went wrong
			cin.clear();  //**Same logic as discussed above** 
			cin.ignore(100, '\n'); //**Same logic as discussed above**
			cout << "PLEASE ENTER ANOTHER STOCK PRICE: " << workCurrency << " " << ends; // Asking the user to input another value for the stock price, the use of workCurrency is implemented here. This is assigns the currency the user is working in to the value they enter
			cin >> putOption0.S; //Once again, the input object relating to the type of data it is (i.e. a double). This is accessing the header and implementation files via the object and dot operator
		} //stop the while statement
		int problem_solver = (putOption0.S > 0); //This helps us to specify, if the stock price is a valid number (i.e possitive), go to the next specification. 
		if (problem_solver){ // If the input is above zero, log this value and go to the next section, which in this case is the strike recognised by the STRIKE_NOW key word derived from the 'goto' logic
			goto STRIKE_NOW; //Go and get the strike data now from the user. This means that all has been successful and the system will move on.
		}else if(putOption0.S != problem_solver){ // however, if the value is below zero, this statement will occur and the user will be asked to re enter the data
        cout << "MUST BE VALID" << endl;  //**SAME LOGIC AS DISCUSSED**
        cin.clear(); //**Same logic as discussed above** 
        cin.ignore(100, '\n'); //**Same logic as discussed above** 
        cout << "PLEASE ENTER ANOTHER STOCK PRICE: " << workCurrency << " " << ends; //again mking sure the users choice of currency is present throughout the programme. The programme has been designed with ease of use in mind
		cin >> putOption0.S; //enter the stock price again via the object putOption0 from the class EuropeanOption using the variable S which is denoted as a double in the class decleration (header file)
		}

STRIKE_NOW:  //FROM HERE THE SAME LOGIC APPLIES, I WILL COMMENT A LINE WHEN THERE IS SOMETHING NEW OR DIFFERENT IN OPERATION

		cout << "PLEASE ENTER THE STRIKE PRICE: " << workCurrency << ends;
		cin >> putOption0.K;
		cout << endl;

		while (!cin){
			cout << "MUST BE NUMERIC" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			cout << "PLEASE ENTER ANOTHER STRIKE PRICE: " << workCurrency << " " << ends;
			cin >> putOption0.K;
		}
		int problem_solver_K = (putOption0.K > 0);
		if (problem_solver_K){
			goto MATURITY_NOW;
		}else if(putOption0.K != problem_solver_K){
        cout << "MUST BE VALID" << endl;
        cin.clear();
        cin.ignore(100, '\n');
        cout << "PLEASE ENTER ANOTHER STRIKE PRICE: " << workCurrency << " " << ends;
		cin >> putOption0.K;
		}

MATURITY_NOW:
			cout << "PLEASE ENTER THE MATURITY HORIZON TIME T: " << ends;
			cin >> putOption0.T;
			cout << endl;
			
		while (!cin){
			cout << "MUST BE NUMERIC" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			cout << "PLEASE ENTER ANOTHER MATURITY HORIZON TIME: " << ends;
			cin >> putOption0.T;
		}
		int problem_solver_T = (putOption0.T > 0);
		if (problem_solver_T){
			goto RF_NOW;
		}else if(putOption0.T != problem_solver_T){
        cout << "MUST BE VALID" << endl;
        cin.clear();
        cin.ignore(100, '\n');
        cout << "PLEASE ENTER ANOTHER MATURITY HORIZON TIME: " << ends;
		cin >> putOption0.T;
		}
RF_NOW:
			cout << "PLEASE ENTER RISK FREE INTEREST RATE: " << ends;
			cin >> putOption0.r;
			cout << endl;
			
			while (!cin){
			cout << "MUST BE NUMERIC" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			cout << "PLEASE ENTER ANOTHER RISK FREE INTEREST RATE: " << ends;
			cin >> putOption0.r;
		}
		int problem_solver_R = (putOption0.r > 0);
		if (problem_solver_R){
			goto VOLA_NOW;
		}else if(putOption0.r != problem_solver_R){
        cout << "MUST BE VALID" << endl;
        cin.clear();
        cin.ignore(100, '\n');
        cout << "PLEASE ENTER ANOTHER RISK FREE INTEREST RATE: " << ends;
		cin >> putOption0.r;
		}
VOLA_NOW:
			cout << "PLEASE ENTER THE VOLATILITY LEVEL: " << ends;
			cin >> putOption0.sig;
			cout << endl;

			while (!cin){
				cout << "MUST BE NUMERIC" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER VOLATILITY LEVEL: " << ends;
				cin >> putOption0.sig;
		}
		int problem_solver_V = (putOption0.sig > 0);
		if (problem_solver_V){
			goto PRICE_IT;
		}else if(putOption0.sig != problem_solver_V){
        cout << "MUST BE VALID" << endl;
        cin.clear();
        cin.ignore(100, '\n');
        cout << "PLEASE ENTER ANOTHER RISK FREE INTEREST RATE: " << workCurrency << " " << ends;
		cin >> putOption0.sig;
		}
PRICE_IT:
			double q_0 = 0.0; // dividend yield. This is set at zero seen as the user has selected to price a no divident contract

			putOption0.b = putOption0.r - q_0; //We now calculate the 'b' in the equation. This section is variable dependant on the contract. In this case it is just the interest rate as its a zero dividend contract, if it was a dividend contract, this would be the interest rate minus the dividend
			if (putOption0.Price() <= 0) { //If the contract is zero there has been a miss specification and the user is alerted to this. This section uses a member function price() to calculate the option value from the Fns*****************NOT SURE
				cout << "ERROR IN INPUT VALUES!" << endl;
			}else{ //However, if the contract is not negative, this would imply that the option has been priced correctly, taking into consideration the error handling, the price should be correct
				cout << "ZERO DIVIDEND PRICE: " << workCurrency << " " << putOption0.Price() << endl;
			}

/**********************************************   Get Time   **********************************************/

			time_t now = time(0); // current date/time based on current system using the class time_t and an object called now
			char* dt = ctime(&now); // convert now to string form. We can now use this as a string. This is char type data.
			//NOTE: This could have been defined outside the loop which would allow this to be defined only once. I have writen it this way, and it is operational, however, to make the code more concise, one would define it out of the 'do' loop.
/***************************************   SAVING CONTRACT DETAILS   ***************************************/

			int saveDetails;  //initialising the variable saveDetails as an integer. this is used in the logic to save the specifications
			cout << "\n " << endl; //ensure a space on the console
			cout << "WOULD YOU LIKE TO SAVE THE CONTRACT SPECIFICATIONS? (Y=1|N=0): " << ends; //Output: the user can choose to save the contract
			cin >> saveDetails;  //Input from user to: either 0 or 1. if its a 1, then the programme will save the specifications
			if (saveDetails == 1) { //'if/else' logic implemented to seave file
				string fileName; //The users unique name for the file saved in a string format
				int willWeContinue; //Initilisation of a new variable which will help us price another contract or jump out of this 'do' loop
				cout << "\nNOTE: YOU SHOULD NOT INCLUDE ANY FILE EXTENSION (e.g .txt)." << endl;
				cout << "PLEASE CHOOSE A UNIQUE FILE NAME: " << ends;
				cin >> fileName;  //the user now types the unique file name
				string extension = ".txt"; // adding the required file extension after the user unique file name
				string newFileName = fileName + extension; //We now have the full file name and this is built with the filename and the extension. For this programme we are saving the data as a text file
/******************************************   Writing Data To File   ******************************************/
				/*****   essentially we are now implementing a form of file processing *****/

					ofstream myfile; //using the library <fstream> .. the class ofstream and the object 'myfile' that has been created to process the info
					myfile.open(fileName + ".txt"); //Creating the file under the users unique name 
					//this could be smoother using a variable relating to the initial choice. This would be a much more automated way of processing the info. (Future Dev) : could implement this in the same way as the workCurrency operates
					myfile << "Contract: Underlying Asset With No Dividends\n"; //Writing in the file: What contract did they choose
					myfile << "Framework: Black-Scholes\n";  //specifying what contract framework was used. This is a constan throughout this programme
					myfile << "Currency Code: " << workCurrency; //Adding currency code that the user has specified at the begining
					myfile << "\n "; // New line in the file
					myfile << "\nSpecifications:"; //the use of \n specifies a new line. Each section of info starts on a new line. 
					myfile << "\n\tInitial Stock Price: " << workCurrency << " " << putOption0.S; // using workCurrency and the user input putOption0.S the values are written to the file. The use of \t is implementing a tab. this is used to make the data more readable
					myfile << "\n\tStrike Price: " << workCurrency << " " << putOption0.K; //same logic as line 249
					myfile << "\n\tVolatility Level: " << putOption0.sig << "%"; //same logic as line 249
					myfile << "\n\tMaturity Of Contract: " << putOption0.T << " years"; //same logic as line 249
					myfile << "\n\tRisk Free Interest Rate: " << putOption0.r << "%" << endl; //same logic as line 249
					myfile << "\nDate Priced: " << dt; //same logic as 249, however we are using the time that the contract was priced. this logic can be found on line 221/222
					myfile << "Zero Paying Dividend Put Option: " << workCurrency << " " << putOption0.Price() << endl; //same logic as line 249
					myfile.close(); //Closing the file...the specifications have now been saved
					cout << "\n " << endl;
					cout << "CONTRACT SPECIFICATIONS HAVE BEEN DOCUMENTED" << endl;  //Telling the user the success of this (Future Dev: scans and tests to see if the file was infact successfully saved
					cout << "LOCATION: DIRECTORY" << endl; //Tells the user where the specifications have been saved to
					cout << "FILE NAME: " + fileName << ".txt" << endl; //showing the user what the file will be under and the type of file (Future Dev: allow the possability to output to an Excel file)
					
					cout << "\nWOULD YOU LIKE TO PRICE ANOTHER CONTRACT? (Y=1|N=0): " << ends; //Using logic: it is  now possible for the user to exit the programme or price another contract. 
					cin >> willWeContinue; //implementing the variable that was initiated at the start of this if loop
					if (willWeContinue == 1){  //logic
						goto LOOP; //If the user wants to price again, go back to the start of the programme and ask them what currency they wish to work with
					}else{
						goto EXIT; //If they do not need to price another contract, exit this 'do' loop and go to the EXIT label. As a computer programme is read from top to bottom, the compilier has already read through it and knows the existance of EXIT. 
					}
				} else if (saveDetails == 0) { //Error logic. This states that if the user does not want to save the details , they should be offered the chance to price another contract
					int priceAnotherContract; //initialisation
					cout << "\nWOULD YOU LIKE TO PRICE ANOTHER CONTRACT? (Y=1|N=0): " << ends;
					cin >> priceAnotherContract; //using this variable as the logic to allow us to continue to price option contracts or jump out of this loop and allow the user to exit. The data will have been saved if they so wish and there is no problem in exiting the programme
					if (priceAnotherContract == 1) {
						goto LOOP; //if the user wants to price another contract, go back to the start of this loop, which starts with the choice of currency
					}else{
						goto EXIT; //jump out of the loop and allow the user to exit the pricing logic.
					}
				} //ends the if statement corresponding to contract one. The exact same logic is carried throughout the programme for every contract

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************   2. DIVIDEND PAYING CONTRACT   ********************************************/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}else if (choice == 2) {
		cout << "\nPUT OPTION ON DIVIDEND PAYING ASSET:" << endl;
		EuropeanOption putOptionD; // a new member of type EuropeanOption named putOption
		double q; // dividend yield

			cout << "\nPLEASE ENTER THE ASSET VALUE: " << workCurrency << ends;
			cin >> putOptionD.S;
			cout << endl;
			
		while (!cin){
			cout << "MUST BE NUMERIC" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			cout << "PLEASE ENTER ANOTHER ASSET PRICE: " << workCurrency << " " << ends;
			cin >> putOptionD.S;
		}
		int problem_solver_Sdiv = (putOptionD.S > 0);
		if (problem_solver_Sdiv){
			goto DIV_STRIKE;
		}else if(putOptionD.S != problem_solver_Sdiv){
        cout << "MUST BE VALID" << endl;
        cin.clear();
        cin.ignore(100, '\n');
        cout << "PLEASE ENTER ANOTHER ASSET PRICE: " << workCurrency << " " << ends;
		cin >> putOptionD.S;
		}
DIV_STRIKE:
			cout << "PLEASE NETER THE STRIKE PRICE: " << workCurrency << ends;
			cin >> putOptionD.K;
			cout << endl;
			
		while (!cin){
			cout << "MUST BE NUMERIC" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			cout << "PLEASE ENTER ANOTHER STRIKE PRICE: " << workCurrency << " " << ends;
			cin >> putOptionD.K;
		}
		int problem_solver_Kdiv = (putOptionD.K > 0);
		if (problem_solver_Kdiv){
			goto DIV_TIME;
		}else if(putOptionD.K != problem_solver_Kdiv){
        cout << "MUST BE VALID" << endl;
        cin.clear();
        cin.ignore(100, '\n');
        cout << "PLEASE ENTER ANOTHER STRIKE PRICE: " << workCurrency << " " << ends;
		cin >> putOptionD.K;
		}

DIV_TIME:
			cout << "PLEASE ENTER THE MATURITY HORIZON TIME: " << ends;
			cin >> putOptionD.T;
			cout << endl;

		while (!cin){
			cout << "MUST BE NUMERIC" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			cout << "PLEASE ENTER ANOTHER MATURITY HORIZON: " << ends;
			cin >> putOptionD.T;
		}
		int problem_solver_Tdiv = (putOptionD.T > 0);
		if (problem_solver_Tdiv){
			goto DIV_INTEREST;
		}else if(putOptionD.T != problem_solver_Tdiv){
        cout << "MUST BE VALID" << endl;
        cin.clear();
        cin.ignore(100, '\n');
        cout << "PLEASE ENTER ANOTHER MATURITY HORIZON: " << workCurrency << " " << ends;
		cin >> putOptionD.T;
		}
DIV_INTEREST:
			cout << "PLEASE ENTER THE RISK FREE INTEREST RATE: " << ends;
			cin >> putOptionD.r;
			cout << endl;

		while (!cin){
			cout << "MUST BE NUMERIC" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			cout << "PLEASE ENTER ANOTHER RISK FREE INTEREST RATE: " << ends;
			cin >> putOptionD.r;
		}
		int problem_solver_Rdiv = (putOptionD.r > 0);
		if (problem_solver_Rdiv){
			goto DIV_VOLA;
		}else if(putOptionD.r != problem_solver_Rdiv){
        cout << "MUST BE VALID" << endl;
        cin.clear();
        cin.ignore(100, '\n');
        cout << "PLEASE ENTER ANOTHER RISK FREE INTEREST RATE: " << ends;
		cin >> putOptionD.r;
		}
DIV_VOLA:
			cout << "PLEASE ENTER THE VOLATILITY LEVEL: " << ends;
			cin >> putOptionD.sig;
			cout << endl;

		while (!cin){
			cout << "MUST BE NUMERIC" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			cout << "PLEASE ENTER ANOTHER VOLATILITY LEVEL: " << ends;
			cin >> putOptionD.sig;
		}
		int problem_solver_SIGdiv = (putOptionD.sig > 0);
		if (problem_solver_SIGdiv){
			goto DIV_YIELD;
		}else if(putOptionD.sig != problem_solver_SIGdiv){
        cout << "MUST BE VALID" << endl;
        cin.clear();
        cin.ignore(100, '\n');
        cout << "PLEASE ENTER ANOTHER VOLATILITY LEVEL: " << ends;
		cin >> putOptionD.sig;
		}
DIV_YIELD:
			cout << "PLEASE ENTER THE DIVIDEND YIELD: " << ends; //Here we use a dividend. This is different from  the first contract and is implemented using a simple int type.
			cin >> q;
			cout << endl;

			while (!cin){
				cout << "MUST BE NUMERIC" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER DIVIDEND YIELD: " << ends;
				cin >> q;
			}
			int problem_solver_DIVIdiv = (q > 0);
				if (problem_solver_DIVIdiv){
					goto DIV_PRICE;
			}else if(q != problem_solver_DIVIdiv){
				cout << "MUST BE VALID" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER DIVIDEND YIELD: " << ends;
				cin >> q;
			}
DIV_PRICE:
			putOptionD.b = putOptionD.r - q; //calculating the variable b in the BS formula. This is inter changable dependent on the contract being priced and holds a different value.

			if (putOptionD.Price() <= 0) {
				cout << "ERROR IN INPUT VALUES!" << endl;
			}else{
				cout << "PRICE: DIVIDEND PAYING CONTRACT: " << workCurrency << " " << putOptionD.Price() << endl;
			}

/**********************************************   Get Time   **********************************************/

			time_t now = time(0); // current date/time based on current system using the class time_t and an object called now
			char* dt_2 = ctime(&now); // convert now to string form. We can now use this as a string. This is char type data.

/***************************************   SAVING CONTRACT DETAILS   ***************************************/

			int saveDetails_2;
			cout << "\n " << endl;
			cout << "WOULD YOU LIKE TO SAVE THE CONTRACT SPECIFICATIONS? (Y=1 | N=0): " << ends;
			cin >> saveDetails_2;
			if (saveDetails_2 == 1) {
				string fileName_2;
				int willWeContinue_2;
				cout << "\nNOTE: YOU SHOULD NOT INCLUDE THE FILE EXTENSION (e.g .txt)." << endl;
				cout << "PLEASE CHOOSE A UNIQUE FILE NAME: " << ends;
				cin >> fileName_2;
				string extension_2 = ".txt";
				string newFileName = fileName_2 + extension_2;
/******************************************   Writing Data To File   ******************************************/
					ofstream myfile;
					myfile.open(fileName_2 + ".txt");
					myfile << "Contract: Dividend Paying\n";
					myfile << "Framework: Black-Scholes\n";
					myfile << "Currency Code: " << workCurrency;
					myfile << "\n ";
					myfile << "\nSpecifications:";
					myfile << "\n\tInitial Stock Price: " << workCurrency << " " << putOptionD.S;
					myfile << "\n\tStrike Price: " << workCurrency << " " << putOptionD.K;
					myfile << "\n\tVolatility Level: " << putOptionD.sig << "%";
					myfile << "\n\tMaturity Of Contract: " << putOptionD.T << " years";
					myfile << "\n\tRisk Free Interest Rate: " << putOptionD.r << "%";
					myfile << "\n\tDividend: " << q << endl;
					myfile << "\nDate Priced: " << dt_2;
					myfile << "Dividend Paying Put Option: " << workCurrency << " " << putOptionD.Price() << endl;
					myfile.close();
					cout << "\n " << endl;
					cout << "CONTRACT SPECIFICATIONS HAVE BEEN DOCUMENTED" << endl;
					cout << "LOCATION: DIRECTORY" << endl;
					cout << "FILE NAME: " + fileName_2 << ".txt" << endl;
					
					cout << "\nWOULD YOU LIKE TO PRICE ANOTHER CONTRACT? (Y=1 | N=0): " << ends;
					cin >> willWeContinue_2;
					if (willWeContinue_2 == 1){
						goto LOOP;
					}else{
						goto EXIT;
					}
				} else if (saveDetails_2 == 0) {
					int priceAnotherContract_2;
					cout << "\nWOULD YOU LIKE TO PRICE ANOTHER CONTRACT? (Y=1 | N=0): " << ends;
					cin >> priceAnotherContract_2;
					if (priceAnotherContract_2 == 1) {
						goto LOOP;
					}else{
						goto EXIT;
					}
				}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/************************************************   3. CURRENCY CONTRACT   *************************************************/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}else if (choice == 3) {
		cout << "\nPUT OPTION ON CURRENCY CONTRACT: " << endl;
		int r_f;
		EuropeanOption putOptionCurr;

			cout << "\nPLEASE ENTER THE ASSET VALUE: " << workCurrency << ends;
			cin >> putOptionCurr.S;
			cout << endl;

			while (!cin){
				cout << "MUST BE NUMERIC" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER ASSET PRICE: " << workCurrency << " " << ends;
				cin >> putOptionCurr.S;
			}
			int problem_solver_currS = (putOptionCurr.S > 0);
				if (problem_solver_currS){
					goto CURR_STRIKE;
			}else if(putOptionCurr.S != problem_solver_currS){
				cout << "MUST BE VALID" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER ASSET PRICE: " << workCurrency << " " << ends;
				cin >> putOptionCurr.S;
			}
CURR_STRIKE: 
			cout << "PLEASE ENTER THE STRIKE PRICE: " << workCurrency << ends;
			cin >> putOptionCurr.K;
			cout << endl;

			while (!cin){
				cout << "MUST BE NUMERIC" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER STRIKE PRICE: " << workCurrency << " " << ends;
				cin >> putOptionCurr.K;
			}
			int problem_solver_currK = (putOptionCurr.K > 0);
				if (problem_solver_currK){
					goto CURR_TIME;
			}else if(putOptionCurr.K != problem_solver_currK){
				cout << "MUST BE VALID" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER STRIKE PRICE: " << workCurrency << " " << ends;
				cin >> putOptionCurr.K;
			}
CURR_TIME:
			cout << "PLEASE ENTER THE MATURITY HORIZON TIME: " << ends;
			cin >> putOptionCurr.T;
			cout << endl;

			while (!cin){
				cout << "MUST BE NUMERIC" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER MATURITY HORIZON: " << ends;
				cin >> putOptionCurr.T;
			}
			int problem_solver_currT = (putOptionCurr.T > 0);
				if (problem_solver_currT){
					goto CURR_RF1;
			}else if(putOptionCurr.T != problem_solver_currT){
				cout << "MUST BE VALID" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER MATURITY HORIZON: " << ends;
				cin >> putOptionCurr.T;
			}
CURR_RF1:
			cout << "PLEASE ENTER THE RISK FREE INTEREST RATE: " << ends;
			cin >> putOptionCurr.r;
			cout << endl;

			while (!cin){
				cout << "MUST BE NUMERIC" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER INTEREST RATE: " << ends;
				cin >> putOptionCurr.r;
			}
			int problem_solver_currR = (putOptionCurr.r > 0);
				if (problem_solver_currR){
					goto CURR_VOL;
			}else if(putOptionCurr.r != problem_solver_currT){
				cout << "MUST BE VALID" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER INTEREST RATE: " << ends;
				cin >> putOptionCurr.r;
			}
CURR_VOL:
			cout << "PLEASE ENTER THE VOLATILITY LEVEL: " << ends;
			cin >> putOptionCurr.sig;
			cout << endl;

			while (!cin){
				cout << "MUST BE NUMERIC" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER VOLATILITY LEVEL: " << ends;
				cin >> putOptionCurr.sig;
			}
			int problem_solver_currVOL = (putOptionCurr.sig > 0);
				if (problem_solver_currVOL){
					goto CURR_RF;
			}else if(putOptionCurr.sig != problem_solver_currVOL){
				cout << "MUST BE VALID" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER VOLATILITY LEVEL: " << ends;
				cin >> putOptionCurr.sig;
			}
CURR_RF:
			cout << "PLEASE ENTER THE RISK FREE RETURN (R/F):" << ends;
			cin >> r_f; //the risk free rate is defined as this is a foreign currency bond with interest and there is market interest. The same logic applies to instate this variable.
			cout << endl;

			while (!cin){
				cout << "MUST BE NUMERIC" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER RISK FREE RATE OF RETURN: " << ends;
				cin >> r_f;
			}
			int problem_solver_currRF = (r_f > 0);
				if (problem_solver_currRF){
					goto CURR_PRICE_IT;
			}else if(r_f != problem_solver_currRF){
				cout << "MUST BE VALID" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER RISK FREE RATE OF RETURN: " << ends;
				cin >> r_f;
			}
CURR_PRICE_IT:
			putOptionCurr.b = putOptionCurr.r - r_f;

			if (putOptionCurr.Price() <= 0) {
				cout << "ERROR IN INPUT VALUES!" << endl;
			}else{
				cout << "PRICE: CURRENCY CONTRACT: " << workCurrency << " " << putOptionCurr.Price() << endl;
			}

/**********************************************   Get Time   **********************************************/

			time_t now = time(0); // current date/time based on current system using the class time_t and an object called now
			char* dt_3 = ctime(&now); // convert now to string form. We can now use this as a string. This is char type data.

/***************************************   SAVING CONTRACT DETAILS   ***************************************/

			int saveDetails_3;
			cout << "\n " << endl;
			cout << "WOULD YOU LIKE TO SAVE THE CONTRACT SPECIFICATIONS? (Y=1 | N=0): " << ends;
			cin >> saveDetails_3;
			if (saveDetails_3 == 1) {
				string fileName_3;
				int willWeContinue_3;
				cout << "\nNOTE: YOU SHOULD NOT INCLUDE THE FILE EXTENSION (e.g .txt)." << endl;
				cout << "PLEASE CHOOSE A UNIQUE FILE NAME: " << ends;
				cin >> fileName_3;
				string extension_3 = ".txt";
				string newFileName = fileName_3 + extension_3;
/******************************************   Writing Data To File   ******************************************/
					ofstream myfile;
					myfile.open(fileName_3 + ".txt");
					myfile << "Contract: Currency\n";
					myfile << "Framework: Black-Scholes\n";
					myfile << "Currency Code: " << workCurrency;
					myfile << "\n ";
					myfile << "\nSpecifications:";
					myfile << "\n\tInitial Stock Price: " << workCurrency << " " << putOptionCurr.S;
					myfile << "\n\tStrike Price: " << workCurrency << " " << putOptionCurr.K;
					myfile << "\n\tVolatility Level: " << putOptionCurr.sig << "%";
					myfile << "\n\tMaturity Of Contract: " << putOptionCurr.T << " years";
					myfile << "\n\tRisk Free Interest Rate: " << putOptionCurr.r << "%";
					myfile << "\n\tRisk Free Return Rate: " << r_f << "%" << endl;
					myfile << "\nDate Priced: " << dt_3;
					myfile << "Currency Put Option: " << workCurrency << " " << putOptionCurr.Price() << endl;
					myfile.close();
					cout << "\n " << endl;
					cout << "CONTRACT SPECIFICATIONS HAVE BEEN DOCUMENTED" << endl;
					cout << "LOCATION: DIRECTORY" << endl;
					cout << "FILE NAME: " + fileName_3 << ".txt" << endl;
					
					cout << "\nWOULD YOU LIKE TO PRICE ANOTHER CONTRACT? (Y=1 | N=0): " << ends;
					cin >> willWeContinue_3;
					if (willWeContinue_3 == 1){
						goto LOOP;
					}else{
						goto EXIT;
					}
				} else if (saveDetails_3 == 0) {
					int priceAnotherContract_3;
					cout << "\nWOULD YOU LIKE TO PRICE ANOTHER CONTRACT? (Y=1 | N=0): " << ends;
					cin >> priceAnotherContract_3;
					if (priceAnotherContract_3 == 1) {
						goto LOOP;
					}else{
						goto EXIT;
					}
				}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/************************************************   4. COMMODITY CONTRACT   ************************************************/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	}else if (choice == 4) {
		cout << "\nPUT OPTION ON A COMMONITY CONTRACT: " << endl;
		int storageCost;
		EuropeanOption putOptionComm;


			cout << "\nPLEASE ENTER THE ASSET VALUE: " << workCurrency << ends;
			cin >> putOptionComm.S;
			cout << endl;

			while (!cin){
				cout << "MUST BE NUMERIC" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER ASSET VALUE: " << workCurrency << " " << ends;
				cin >> putOptionComm.S;
			}
			int problem_solver_COMM_S = (putOptionComm.S > 0);
				if (problem_solver_COMM_S){
					goto COMM_STRIKE;
			}else if(putOptionComm.S != problem_solver_COMM_S){
				cout << "MUST BE VALID" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER ASSET VALUE: " << workCurrency << " " << ends;
				cin >> putOptionComm.S;
			}
COMM_STRIKE:
			cout << "PLEASE ENTER THE STRIKE PRICE: " << workCurrency << ends;
			cin >> putOptionComm.K;
			cout << endl;

			while (!cin){
				cout << "MUST BE NUMERIC" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER STRIKE VALUE: " << workCurrency << " " << ends;
				cin >> putOptionComm.K;
			}
			int problem_solver_COMM_K = (putOptionComm.K > 0);
				if (problem_solver_COMM_K){
					goto COMM_M;
			}else if(putOptionComm.K != problem_solver_COMM_K){
				cout << "MUST BE VALID" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER STRIKE VALUE: " << workCurrency << " " << ends;
				cin >> putOptionComm.K;
			}
COMM_M:
			cout << "PLEASE ENTER THE MATURITY HORIZON: " << ends;
			cin >> putOptionComm.T;
			cout << endl;

			while (!cin){
				cout << "MUST BE NUMERIC" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER MATURITY HORIZON: " << ends;
				cin >> putOptionComm.T;
			}
			int problem_solver_COMM_T = (putOptionComm.T > 0);
				if (problem_solver_COMM_T){
					goto COMM_RF;
			}else if(putOptionComm.T != problem_solver_COMM_T){
				cout << "MUST BE VALID" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER MATURITY HORIZON: " << ends;
				cin >> putOptionComm.T;
			}
COMM_RF:
			cout << "PLEASE ENTER THE RISK FREE INTEREST RATE: " << ends;
			cin >> putOptionComm.r;
			cout << endl;

			while (!cin){
				cout << "MUST BE NUMERIC" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER RISK FREE INTEREST RATE: " << ends;
				cin >> putOptionComm.r;
			}
			int problem_solver_COMM_R = (putOptionComm.r > 0);
				if (problem_solver_COMM_R){
					goto COMM_VOLA;
			}else if(putOptionComm.r != problem_solver_COMM_R){
				cout << "MUST BE VALID" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER RISK FREE INTEREST RATE: " << ends;
				cin >> putOptionComm.r;
			}
COMM_VOLA:
			cout << "PLEASE ENTER THE VOLATILITY LEVEL: " << ends;
			cin >> putOptionComm.sig;
			cout << endl;

			while (!cin){
				cout << "MUST BE NUMERIC" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER VOLATILITY LEVEL: " << ends;
				cin >> putOptionComm.sig;
			}
			int problem_solver_COMM_SIG = (putOptionComm.sig > 0);
				if (problem_solver_COMM_SIG){
					goto COMM_STORAGE;
			}else if(putOptionComm.sig != problem_solver_COMM_SIG){
				cout << "MUST BE VALID" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER VOLATILITY LEVEL: " << ends;
				cin >> putOptionComm.sig;
			}
COMM_STORAGE:
			cout << "PLEASE ENTER THE COST OF STORAGE: " << ends;
			cin >> storageCost; //this is a commodity contract so the cost of staorage needs to be taken into account. The same logic is applied as the usual user input.
			cout << endl;

			while (!cin){
				cout << "MUST BE NUMERIC" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER PRICE FOR STORAGE: " << workCurrency << " " << ends;
				cin >> storageCost;
			}
			int problem_solver_COMM_STORE = (storageCost > 0);
				if (problem_solver_COMM_STORE){
					goto COMM_PRICE_IT;
			}else if(storageCost != problem_solver_COMM_STORE){
				cout << "MUST BE VALID" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER PRICE FOR STORAGE: " << workCurrency << " " << ends;
				cin >> storageCost;
			}
COMM_PRICE_IT:
			putOptionComm.b = putOptionComm.r + storageCost; //adding the storage cost to the interest rate allowing the option to account for the the cost of storage in the price.
	
			if (putOptionComm.Price() <= 0) {
				cout << "ERROR IN INPUT VALUES!" << endl;
			}else{
				cout << "PRICE: COMMODITY CONTRACT: " << workCurrency << " "  << putOptionComm.Price() << endl;
			}

/**********************************************   Get Time   **********************************************/

			time_t now = time(0); // current date/time based on current system using the class time_t and an object called now
			char* dt_4 = ctime(&now); // convert now to string form. We can now use this as a string. This is char type data.

/***************************************   SAVING CONTRACT DETAILS   ***************************************/

			int saveDetails_4;
			cout << "\n " << endl;
			cout << "WOULD YOU LIKE TO SAVE THE CONTRACT SPECIFICATIONS? (Y=1 | N=0): " << ends;
			cin >> saveDetails_4;
			if (saveDetails_4 == 1) {
				string fileName_4;
				int willWeContinue_4;
				cout << "\nNOTE: YOU SHOULD NOT INCLUDE THE FILE EXTENSION (e.g .txt)." << endl;
				cout << "PLEASE CHOOSE A UNIQUE FILE NAME: " << ends;
				cin >> fileName_4;
				string extension_4 = ".txt";
				string newFileName = fileName_4 + extension_4;
/******************************************   Writing Data To File   ******************************************/
					ofstream myfile;
					myfile.open(fileName_4 + ".txt");
					myfile << "Contract: Commodity\n";
					myfile << "Framework: Black-Scholes\n";
					myfile << "Currency Code: " << workCurrency;
					myfile << "\n ";
					myfile << "\nSpecifications:";
					myfile << "\n\tInitial Stock Price: " << workCurrency << " " << putOptionComm.S;
					myfile << "\n\tStrike Price: " << workCurrency << " " << putOptionComm.K;
					myfile << "\n\tVolatility Level: " << putOptionComm.sig << "%";
					myfile << "\n\tMaturity Of Contract: " << putOptionComm.T << " years";
					myfile << "\n\tRisk Free Interest Rate: " << putOptionComm.r << "%";
					myfile << "\n\tStorage Costs: " << storageCost << endl; //is this in currency or %??
					myfile << "\nDate Priced: " << dt_4;
					myfile << "Commoidty Put Option: " << workCurrency << " " << putOptionComm.Price() << endl;
					myfile.close();
					cout << "\n " << endl;
					cout << "CONTRACT SPECIFICATIONS HAVE BEEN DOCUMENTED" << endl;
					cout << "LOCATION: DIRECTORY" << endl;
					cout << "FILE NAME: " + fileName_4 << ".txt" << endl;
					
					cout << "\nWOULD YOU LIKE TO PRICE ANOTHER CONTRACT? (Y=1 | N=0): " << ends;
					cin >> willWeContinue_4;
					if (willWeContinue_4 == 1){
						goto LOOP;
					}else{
						goto EXIT;
					}
				} else if (saveDetails_4 == 0) {
					int priceAnotherContract_4;
					cout << "\nWOULD YOU LIKE TO PRICE ANOTHER CONTRACT? (Y=1 | N=0): " << ends;
					cin >> priceAnotherContract_4;
					if (priceAnotherContract_4 == 1) {
						goto LOOP;
					}else{
						goto EXIT;
					}
				}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		
/*************************************************   5. FUTURES CONTRACT   *************************************************/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}else if (choice == 5) {
		cout << "\nCONTRACT: PUT OPTION ON FUTURES: " << endl;
		EuropeanOption putOptionFuture;

			cout << "\nPLEASE ENTER THE ASSET PRICE: " << workCurrency << ends;
			cin >> putOptionFuture.S;
			cout << endl;

			while (!cin){
				cout << "MUST BE NUMERIC" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER ASSET VALUE: " << workCurrency << " " << ends;
				cin >> putOptionFuture.S;
			}
			int problem_solver_FUT_S = (putOptionFuture.S > 0);
				if (problem_solver_FUT_S){
					goto FUT_STRIKE;
			}else if(putOptionFuture.S != problem_solver_FUT_S){
				cout << "MUST BE VALID" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER ASSET VALUE: " << workCurrency << " " << ends;
				cin >> putOptionFuture.S;
			}
FUT_STRIKE:
			cout << "PLEASE ENTER THE STRIKE PRICE: " << workCurrency << ends;
			cin >> putOptionFuture.K;
			cout << endl;

			while (!cin){
				cout << "MUST BE NUMERIC" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER STRIKE PRICE: " << workCurrency << " " << ends;
				cin >> putOptionFuture.K;
			}
			int problem_solver_FUT_K = (putOptionFuture.K > 0);
				if (problem_solver_FUT_K){
					goto FUT_TIME;
			}else if(putOptionFuture.K != problem_solver_FUT_K){
				cout << "MUST BE VALID" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER ASSET VALUE: " << workCurrency << " " << ends;
				cin >> putOptionFuture.K;
			}
FUT_TIME:
			cout << "PLEASE ENTER THE MATURITY: " << ends;
			cin >> putOptionFuture.T;
			cout << endl;

			while (!cin){
				cout << "MUST BE NUMERIC" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER MATURITY HORIZON: " << ends;
				cin >> putOptionFuture.T;
			}
			int problem_solver_FUT_T = (putOptionFuture.T > 0);
				if (problem_solver_FUT_T){
					goto FUT_RFI;
			}else if(putOptionFuture.T != problem_solver_FUT_T){
				cout << "MUST BE VALID" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER MATURITY HORIZON: " << ends;
				cin >> putOptionFuture.T;
			}
FUT_RFI:
			cout << "PLEASE ENTER RISK FREE INTEREST RATE: " << ends;
			cin >> putOptionFuture.r;
			cout << endl;

			while (!cin){
				cout << "MUST BE NUMERIC" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER RISK FREE INTEREST RATE: " << ends;
				cin >> putOptionFuture.r;
			}
			int problem_solver_FUT_R = (putOptionFuture.r > 0);
				if (problem_solver_FUT_R){
					goto FUT_VOLA;
			}else if(putOptionFuture.r != problem_solver_FUT_R){
				cout << "MUST BE VALID" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER RISK FREE INTEREST RATE: " << ends;
				cin >> putOptionFuture.r;
			}
FUT_VOLA:
			cout << "PLEASE ENTER THE VOLATILITY LEVEL: " << ends;
			cin >> putOptionFuture.sig;
			cout << endl;

		while (!cin){
				cout << "MUST BE NUMERIC" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER VOLATILITY LEVEL: " << ends;
				cin >> putOptionFuture.sig;
			}
			int problem_solver_FUT_SIG = (putOptionFuture.sig > 0);
				if (problem_solver_FUT_SIG){
					goto FUT_PRICE_IT;
			}else if(putOptionFuture.sig != problem_solver_FUT_SIG){
				cout << "MUST BE VALID" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				cout << "PLEASE ENTER ANOTHER VOLATILITY LEVEL: " << ends;
				cin >> putOptionFuture.sig;
			}
FUT_PRICE_IT:
			putOptionFuture.b = 0;
	
			if (putOptionFuture.Price() <= 0) {
				cout << "Error in input values!" << endl;
			}else{
				cout << "Futures Price: " << workCurrency << " " << putOptionFuture.Price() << endl;
			}

/**********************************************   Get Time   **********************************************/

			time_t now = time(0); // current date/time based on current system using the class time_t and an object called now
			char* dt_5 = ctime(&now); // convert now to string form. We can now use this as a string. This is char type data.

/***************************************   SAVING CONTRACT DETAILS   ***************************************/

			int saveDetails_5;
			cout << "\n " << endl;
			cout << "WOULD YOU LIKE TO SAVE THE CONTRACT SPECIFICATIONS? (Y=1 | N=0): " << ends;
			cin >> saveDetails_5;
			if (saveDetails_5 == 1) {
				string fileName_5;
				int willWeContinue_5;
				cout << "\nNOTE: YOU SHOULD NOT INCLUDE THE EXTENSION (e.g .txt)." << endl;
				cout << "PLEASE CHOOSE A UNIQUE FILE NAME: " << ends;
				cin >> fileName_5;
				string extension_5 = ".txt";
				string newFileName = fileName_5 + extension_5;
/******************************************   Writing Data To File   ******************************************/
					ofstream myfile;
					myfile.open(fileName_5 + ".txt");
					myfile << "Contract: Futures\n";
					myfile << "Framework: Black-Scholes\n";
					myfile << "Currency Code: " << workCurrency;
					myfile << "\n ";
					myfile << "\nSpecifications:";
					myfile << "\n\tInitial Stock Price: " << workCurrency << " " << putOptionFuture.S;
					myfile << "\n\tStrike Price: " << workCurrency << " " << putOptionFuture.K;
					myfile << "\n\tVolatility Level: " << putOptionFuture.sig << "%";
					myfile << "\n\tMaturity Of Contract: " << putOptionFuture.T << " years";
					myfile << "\n\tRisk Free Interest Rate: " << putOptionFuture.r << "%" << endl;
					myfile << "\nDate Priced: " << dt_5;
					myfile << "Futures Put Option: " << workCurrency << " " << putOptionFuture.Price() << endl;
					myfile.close();
					cout << "\n " << endl;
					cout << "CONTRACT SPECIFICATIONS HAVE BEEN DOCUMENTED" << endl;
					cout << "LOCATION: DIRECTORY" << endl;
					cout << "FILE NAME: " + fileName_5 << ".txt" << endl;
					
					cout << "\nWOULD YOU LIKE TO PRICE ANOTHER CONTRACT? (Y=1 | N=0): " << ends;
					cin >> willWeContinue_5;
					if (willWeContinue_5 == 1){
						goto LOOP;
					}else{
						goto EXIT;
					}
				} else if (saveDetails_5 == 0) {
					int priceAnotherContract_5;
					cout << "\nWOULD YOU LIKE TO PRICE ANOTHER CONTRACT? (Y=1 | N=0): " << ends;
					cin >> priceAnotherContract_5;
					if (priceAnotherContract_5 == 1) {
						goto LOOP; //if they have chosen to price again, go all the way to the top of the programme
					}else{
						goto EXIT; //jump out of the loop and allow the user to exit the pricing logic.
					}
				}

/**********************************************   NO VALID CONTRACT HAS BEEN CHOSEN   **********************************************/
			}
}while (choice = 1 || 2 || 3 || 4 || 5); //this is the final section of the do loop where the loop will only run if the choice is within the specified range
	
EXIT: cout << "\nTHANK YOU FOR USING THIS SYSTEM. PRESS ANY KEY TO EXIT..." << endl;
	system("pause>NULL"); //THE USE OF system("pause), pauses the console, if the following is added there will be no default output telling the user to press any key: >NULL
	return 0; //return zero to let the compilier know the programme has been successfully executed
	}