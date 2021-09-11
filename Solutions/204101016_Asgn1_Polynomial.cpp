/*
------------------------------------------------------
Name : AVIK SAMANTA
Roll no. : 204101016 
Asgn. : Polynomial Class
Environment :-
IDE : Dev C++
Compiler : TDM-GCC 4.9.2 (64 Bits)
Language standard : GNU C++ 11
-----------------------------------------------------
*/

#include<bits/stdc++.h>
using namespace std;
#define coefficient first // as the first element in the pair denotes coefficient
#define exponent second   // as the second element in the pair denotes exponent

/* 
----------------------------------
Poly Class (for the Polynomial)
---------------------------------- 
*/
class Poly{
	private:
		/*
		------------------------------------------------------------------------------------------------------------------------------- 
		Each element of this vector has the data "coefficient and exponent as a pair", each of which represent a term in the polynomial 
		-------------------------------------------------------------------------------------------------------------------------------
		*/
		vector< pair<long double, long double> > Polynomial;
		
	public:
		/* 
		-------------------------------------------------
		constructor without argument, default constructor
		-------------------------------------------------
		*/
		Poly() {}
		
		/* 
	    --------------------------------------------------------------------------------------------------------------------------
		constructor with argument (term) ||
		-> this will take two values as argument and make a (coefficient and exponent pair) and add that to our polynomial vector
		--------------------------------------------------------------------------------------------------------------------------
		*/
		Poly(long double coeff, long double exp){
			if(Polynomial.empty()) Polynomial.push_back(make_pair(coeff, exp));
		}
		
		/* 
		-------------------------------------------------------------------------------------------------------------------------------------------------------------
		overloading the operator + ||
		-> This actually adds two Poly objects (2nd object can also be only a term, which basically is an object with a vector having one pair (term)
		-> and then concatenate the polynomial terms from those two objects, and store in a third object, which we will eventually return
		-> Now while doing this, we tried to maintain the sorted order of exponent, using the "merge" concept (of merge sort algorithm)
		-> as the terms in the polynomial are already sorted (based on the exponent), we compare one element from each of the polynomials (based on exponent)
		-> and put that in the right slot, into the new polynomial (with a little tweak that, is somehow the exponent of two terms match, we add their coefficients) 
		-------------------------------------------------------------------------------------------------------------------------------------------------------------
		*/
		Poly operator + (Poly obj){
			Poly added;
			// Adding all the terms of LHS and RHS polynomial into the new Polymonial (keeping the sorted order of exponents intact)
		    int i = 0, j = 0;
		    while(i < Polynomial.size() and j < obj.Polynomial.size()){
		    	if(Polynomial[i].exponent == obj.Polynomial[j].exponent){
		    		added.Polynomial.push_back(make_pair(Polynomial[i].coefficient + obj.Polynomial[j].coefficient, Polynomial[i].exponent));
		    		i ++; 
					j ++;
				}
				else if(Polynomial[i].exponent > obj.Polynomial[j].exponent){
		    		added.Polynomial.push_back(make_pair(Polynomial[i].coefficient, Polynomial[i].exponent));
		    		i ++;
				}
				else if(Polynomial[i].exponent < obj.Polynomial[j].exponent){
		    		added.Polynomial.push_back(make_pair(obj.Polynomial[j].coefficient, obj.Polynomial[j].exponent));
		    		j ++;
				}
			}
			while(i < Polynomial.size()){
				added.Polynomial.push_back(make_pair(Polynomial[i].coefficient, Polynomial[i].exponent));
		    	i ++;
			}
			while(j < obj.Polynomial.size()){
				added.Polynomial.push_back(make_pair(obj.Polynomial[j].coefficient, obj.Polynomial[j].exponent));
		    	j ++;
			}
		    return added;
		}
		
		/* 
		--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		overloading the operator - ||
		-> This substruct one Poly object from another (2nd object can also be only a term, which basically is an object with a vector having one pair (term)
		-> which means we negate (if (+) then (-), and vice-versa) all the terms's coefficients of the 2nd object and add them normally
		-> and then concatenate the polynomial terms from those two objects, and store in a third object, which we will eventually return
		-> Now while doing this, we tried to maintain the sorted order of exponent, using the "merge" concept (of merge sort algorithm)
		-> as the terms in the polynomial are already sorted (based on the exponent), we compare one element from each of the polynomials (based on exponent)
		-> and put that in the right slot, into the new polynomial (with a little tweak that, is somehow the exponent of two terms match, we substract the 2nd one's coefficient) 
		--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		*/
		Poly operator - (Poly obj){
			Poly substructed;
			// Adding all the terms of LHS and RHS polynomial into the new Polymonial (keeping the sorted order of exponents intact)
			// where we will negate all the terms of the RHS polynomial (means, negating the coefficients)
		    int i = 0, j = 0;
		    while(i < Polynomial.size() and j < obj.Polynomial.size()){
		    	if(Polynomial[i].exponent == obj.Polynomial[j].exponent){
		    		substructed.Polynomial.push_back(make_pair(Polynomial[i].coefficient - obj.Polynomial[j].coefficient, Polynomial[i].exponent));
		    		i ++; 
					j ++;
				}
				else if(Polynomial[i].exponent > obj.Polynomial[j].exponent){
		    		substructed.Polynomial.push_back(make_pair(Polynomial[i].coefficient, Polynomial[i].exponent));
		    		i ++;
				}
				else if(Polynomial[i].exponent < obj.Polynomial[j].exponent){
		    		substructed.Polynomial.push_back(make_pair(-obj.Polynomial[j].coefficient, obj.Polynomial[j].exponent));
		    		j ++;
				}
			}
			while(i < Polynomial.size()){
				substructed.Polynomial.push_back(make_pair(Polynomial[i].coefficient, Polynomial[i].exponent));
		    	i ++;
			}
			while(j < obj.Polynomial.size()){
				substructed.Polynomial.push_back(make_pair(-obj.Polynomial[j].coefficient, obj.Polynomial[j].exponent));
		    	j ++;
			}
		    return substructed;
		}
		
		/*
		-------------------------------------------------------------------------
		Overloading the unary - operator || 
		-> this will negate all the terms (coefficients) there in the polynomial
		-------------------------------------------------------------------------
		*/
		void operator - (){
			for(int i = 0; i < Polynomial.size(); i ++) 
			    Polynomial[i].coefficient = (- Polynomial[i].coefficient);
		}
		
		/* 
		-----------------------------------------------------------------------------------------
		overloading the operator += || 
		-> This works completely the same as + operator, with only the difference that,
		-> we are merging them into the 1st poly object only, and we won't be returning anything
		-----------------------------------------------------------------------------------------
		*/
		void operator += (Poly obj){
		    int i = 0;
		    for(int j = 0; j < Polynomial.size(); j ++){
		    	if(i < obj.Polynomial.size() and obj.Polynomial[i].exponent > Polynomial[j].exponent){
		    		Polynomial.insert(Polynomial.begin() + j, make_pair(obj.Polynomial[i].coefficient, obj.Polynomial[i].exponent));
		    		i ++;
				}
				else if(i < obj.Polynomial.size() and obj.Polynomial[i].exponent == Polynomial[j].exponent){
		    		Polynomial[j] = make_pair(obj.Polynomial[i].coefficient + Polynomial[j].coefficient, obj.Polynomial[i].exponent);
		    		i ++;
				}
			}
			while(i < obj.Polynomial.size()){
				Polynomial.push_back(make_pair(obj.Polynomial[i].coefficient, obj.Polynomial[i].exponent));
		    	i ++;
			}
		}
		
		/* 
		-------------------------------------------------------------------------------------------------------------------------------------------
		overloading the operator -= || 
		-> This is almost the same as - operator with a little difference, it won't return anything and
		-> we add all the terms of RHS (2 nd) object into the LHS (1 st) object itself, after negeting the coeffiecient of the terms of 2nd object
		-------------------------------------------------------------------------------------------------------------------------------------------
		*/
		void operator -= (Poly obj){
		    int i = 0;
		    for(int j = 0; j < Polynomial.size(); j ++){
		    	if(i < obj.Polynomial.size() and obj.Polynomial[i].exponent > Polynomial[j].exponent){
		    		Polynomial.insert(Polynomial.begin() + j, make_pair(-obj.Polynomial[i].coefficient, obj.Polynomial[i].exponent));
		    		i ++;
				}
				else if(i < obj.Polynomial.size() and obj.Polynomial[i].exponent == Polynomial[j].exponent){
		    		Polynomial[j] = make_pair(-obj.Polynomial[i].coefficient + Polynomial[j].coefficient, obj.Polynomial[i].exponent);
		    		i ++;
				}
			}
			while(i < obj.Polynomial.size()){
				Polynomial.push_back(make_pair(-obj.Polynomial[i].coefficient, obj.Polynomial[i].exponent));
		    	i ++;
			}
		}
		
		/* 
		------------------------------------------------------------------------------------------------------
		overloading the operator *= || 
		-> we will multiply each coefficient with the constant passed as argument
		------------------------------------------------------------------------------------------------------
		*/
		void operator *= (long double mul){
		    for(int i = 0; i < Polynomial.size(); i ++){
		    	Polynomial[i].coefficient *= mul;
			}
		}
		
		/*
		---------------------------------------------------------------------------------------
		Implementing "at" function, which for a given "x", gives us the value of the polynomial
		---------------------------------------------------------------------------------------
		*/
		long double at(long double x){
			double value_at = 0.0;
			for(int i = 0; i < Polynomial.size(); i ++){
				value_at += (Polynomial[i].coefficient * pow(x, Polynomial[i].exponent));
			}
			return value_at;
		}
		
		/*
		---------------------------------------------
		Print : Showing how our polynomial looks like
		---------------------------------------------
		*/
		void print(){
			cout << "y =";
			for(int i = 0; i < Polynomial.size(); i ++){
				if(Polynomial[i].coefficient == 0.0){
				    Polynomial.erase(Polynomial.begin() + i);
				    i --;
				}
				else{
					if(Polynomial[i].coefficient < 0){
				        if(!Polynomial[i].exponent) cout << " - " << abs(Polynomial[i].coefficient);
						else if(Polynomial[i].exponent == 1) cout << " - " << abs(Polynomial[i].coefficient) << "*x";
				        else cout << " - " << abs(Polynomial[i].coefficient) << "*x^" << (int)Polynomial[i].exponent;
				    }
				    else{
				    	if(!i){
						    if(!Polynomial[i].exponent) cout << " " << Polynomial[i].coefficient;
							else if(Polynomial[i].exponent == 1) cout << " " << Polynomial[i].coefficient << "*x";
						    else cout << " " << Polynomial[i].coefficient << "*x^" << (int)Polynomial[i].exponent;
						}
				    	else{
				    		if(!Polynomial[i].exponent) cout << " + " << Polynomial[i].coefficient;
							else if(Polynomial[i].exponent == 1) cout << " + " << Polynomial[i].coefficient << "*x";
				            else cout << " + " << Polynomial[i].coefficient << "*x^" << (int)Polynomial[i].exponent;
						}
					}
				}
			}
			cout << endl;
		}
		
		/*
		-----------------------------------
		Destructor : Clear the terms vector
		-----------------------------------
		*/
		~Poly(){
			Polynomial.clear();
		}
};

/*
---------------------------------------------------------------------------
This is to give some basic information about the student and the assignment
---------------------------------------------------------------------------
*/
void info(){
	cout << "--------------------------------------------------------------\n";
	cout << "Hii !! This is Avik Samanta...\n";
	cout << "M.Tech.(1st Year) : 204101016\n";
	cout << "This is the solution for the 1st Assignment : \"Polynomial\" !!\n";
	cout << "--------------------------------------------------------------\n\n";
}

/*
------------------------------------------------------------------------------------
This is a helper function to create a polynomial, with the data provided by the user
------------------------------------------------------------------------------------
*/
void createPoly(Poly &testPoly){
	int terms;
	long double exp, coeff;
	cout << "i.e. Polynomial (-3*x^3 + 5*x - 1) has three terms in it;\n";
	cout << "Enter how many terms will be there in your polynomial : ";
	do{
	    cin >> terms;
	    if(terms <= 0)
	        cout << "Invalid entry! Your polynomial must have at least one element.\nEnter the no. of terms again : ";
	}while(terms <= 0);
	for(int i = 1; i <= terms; i ++){
		string th;
		if(i == 1) th = "st";
		else if(i == 2) th = "nd";
		else if(i == 3) th = "rd";
		else th = "th";
	    cout << "Enter the "  << i << th << " term :-\n";
	    cout << "Coefficient : "; cin >> coeff;
	    cout << "Exponent : "; cin >> exp;
	    if(exp < 0){
		    cout << "Invalid Entry! A polynomial term can't have negetive exponent...\n";
		    i --;   
		}
		else if(coeff) testPoly += Poly(coeff, exp);
	}
}

/*
---------------------------------------------------------------------------------------
This is a helper function, to evaluate the polynomial, asking user to enter the x value
---------------------------------------------------------------------------------------
*/
void evaluate(Poly &testPoly){
	long double x;
	cout << "Enter the value of x : ";
	cin >> x;
	cout << "The value of the polynomial at x = " << x << " is : " << testPoly.at(x) << "\n\n";
}

/*
----------------------------------------------------------------------
This is the main function; tried to make it as interracive as possible
----------------------------------------------------------------------
*/
int main(){
	info();
	cout << "Okay! Let's first create a polynomial for ourselves!\n";
	Poly ourPoly;
	createPoly(ourPoly);
	cout << "So, this is our polynomial : ";
	ourPoly.print(); cout << "\n";
	
	cout << "Here are some options to play around :\n";
	cout << "1. Find the value of the polynomial at some x\n";
	cout << "2. Add a term to our Polynomial(overloading + operator)\n";
	cout << "3. Add a new polynomial to the current one(overloading + operator)\n";
	cout << "4. Substruct a term from our polynomial(overloading - operator)\n";
	cout << "5. Substruct a new polynomial from the current one(overloading - operator)\n";
	cout << "6. Use of \"unary -\" overloaded operator (to negate the terms of our polynomial)\n";
	cout << "7. Add one term to our polynomial(overloading += operator)\n";
	cout << "8. Substruct one term from our polynomial(overloading -= operator)\n";
	cout << "9. Multiply our polynomial with a constant\n";
	cout << "10. Self made example walk through\n";
	cout << "11. Enter 11 to exit\n\n";
	
	while(true){
	    int choice;
		cout << "Enter your choice (1-10 to go on / 11 to exit) : ";
		cin >> choice; 
		switch(choice){
			case 1:{
				cout << "This is our current polynomial : ";
				ourPoly.print();
				evaluate(ourPoly);
				break;
			}
			case 2:{
				long double coeff, exp;
				char do_you_want;
				cout << "This is to add a term (i.e. 3*x^2 or 5*x etc) to a polynomial;\n";
				cout << "Our current polynomial is : ";
				ourPoly.print();
				cout << "Now enter the detail of the term to be added :\n";
				cout << "Enter the coefficient : "; cin >> coeff;
				cout << "Enter the exponent : "; cin >> exp;
				ourPoly = ourPoly + Poly(coeff, exp);
				cout << "Now this is our updated polynomial : ";
				ourPoly.print();
				cout << "Are you interested to find the value? (Enter : Y/N) : ";
				cin >> do_you_want;
				if(do_you_want == 'Y' or do_you_want == 'y') evaluate(ourPoly);
				else cout << "\n"; 
				break;
			}
			case 3:{
				Poly testPoly;
				cout << "This is our current polynomial : ";
				ourPoly.print();
				cout << "Let's create a polynomial which we want to add..\n";
				createPoly(testPoly);
				cout << "This is the new polynomial to be added : ";
				testPoly.print();
				ourPoly = ourPoly + testPoly;
				cout << "Okay! our polynomial now looks like this : ";
				ourPoly.print();
				cout << "Are you interested to find the value? (Enter : Y/N) : ";
				char do_you_want;
				cin >> do_you_want;
				if(do_you_want == 'Y' or do_you_want == 'y') evaluate(ourPoly);
				else cout << "\n";
				break;
			}
			case 4:{
				long double exp, coeff;
				cout << "This is our current polynomial : ";
				ourPoly.print();
				cout << "Enter the details of the term you want to substruct;\n";
				cout << "Enter the coefficient : "; cin >> coeff;
				cout << "Enter the exponent : "; cin >> exp;
				ourPoly = ourPoly - Poly(coeff, exp);
				cout << "This is our updated polynomial : ";
				ourPoly.print();
				cout << "Are you interested to find the value? (Enter : Y/N) : ";
				char do_you_want;
				cin >> do_you_want;
				if(do_you_want == 'Y' or do_you_want == 'y') evaluate(ourPoly);
				cout << "\n";
				break;
			}
			case 5:{
				Poly testPoly;
				cout << "This is our current polynomial : ";
				ourPoly.print();
				cout << "Let's create a polynomial which we want to substruct\n";
				createPoly(testPoly);
				cout << "This is the new polynomial to be substructed : ";
				testPoly.print();
				ourPoly = ourPoly - testPoly;
				cout << "Okay! our polynomial now looks like this : ";
				ourPoly.print();
				cout << "Are you interested to find the value? (Enter : Y/N) : ";
				char do_you_want;
				cin >> do_you_want;
				if(do_you_want == 'Y' or do_you_want == 'y') evaluate(ourPoly);
				else cout << "\n";
				break;
			}
			case 6:{
				cout << "This is our current polynomial : ";
				ourPoly.print();
				cout << "Let's negate all the terms (using the unary - operator) :-\n";
				- ourPoly;
				cout << "Now this is the updated polynomial : ";
				ourPoly.print();
				cout << "Are you interested to find the value? (Enter : Y/N) : ";
				char do_you_want;
				cin >> do_you_want;
				if(do_you_want == 'Y' or do_you_want == 'y') evaluate(ourPoly);
				else cout << "\n";
				break;
			}
			case 7:{
				long double coeff, exp;
				cout << "This is the our current polynomial : ";
				ourPoly.print();
				cout << "So what's the term you want to add?\n";
				cout << "Enter the coefficient : "; cin >> coeff;
				cout << "Enter the exponent : "; cin >> exp;
				ourPoly += Poly(coeff, exp);
				cout << "Okay! This is how our polynomial looks now : ";
				ourPoly.print();
				cout << "Are you interested to find the value? (Enter : Y/N) : ";
				char do_you_want;
				cin >> do_you_want;
				if(do_you_want == 'Y' or do_you_want == 'y') evaluate(ourPoly);
				else cout << "\n";
				break;
			}
			case 8:{
				long double coeff, exp;
				cout << "This is our current polynomial : ";
				ourPoly.print();
				cout << "What's the term you want to substruct?\n";
				cout << "Enter the coefficient : "; cin >> coeff;
				cout << "Enter the exponent : "; cin >> exp;
				ourPoly -= Poly(coeff, exp);
				cout << "Okay! this is how our polynomial looks now : ";
				ourPoly.print();
				cout << "Are you interested to find the value? (Enter : Y/N) : ";
				char do_you_want;
				cin >> do_you_want;
				if(do_you_want == 'Y' or do_you_want == 'y') evaluate(ourPoly);
				else cout << "\n"; 
				break;
			}
			case 9:{
				long double mul;
				char do_you_want;
				cout << "Our current polynomial is : ";
				ourPoly.print();
				cout << "Now enter the constant you want to multiply : ";
				cin >> mul;
				ourPoly *= mul;
				cout << "Now this is the modified polynomial : ";
				ourPoly.print();
				cout << "Are you interested to find the value? (Enter : Y/N) : ";
				cin >> do_you_want;
				if(do_you_want == 'Y' or do_you_want == 'y') evaluate(ourPoly);
				else cout << "\n"; 
				break;
			}
			case 10:{
				cout << "This is to give you a simple example :-\n";
				cout << "Let's create the Polynomial : 4*x^3 - 3*x + 5\n";
				cout << "The instruction looks something like this :-\n";
				cout << "Poly myPoly = Poly(4, 3) + Poly(-3, 1) + Poly(5, 0);\n";
				cout << "There is also an alternative way of doing this :-\n";
				cout << "Poly myPoly = Poly(4, 3) - Poly(3, 1) + Poly(5, 0);\n";
				cout << "Also can be done by the following instructions :-\nPoly myPoly;\nmyPoly += Poly(4, 3);\nmyPoly += Poly(-3, 1);\nmyPoly += Poly(5, 0)\n\n";
				Poly myPoly = Poly(4, 3) - Poly(3, 1) + Poly(5, 0);
				cout << "Okay! time to evaluate this..\n";
				evaluate(myPoly);
				cout << "Now let's add a term to our Polynomial, i.e. 2*x^2..\n";
				cout << "Instruction will be like :-\nmyPoly += Poly(2, 2);\n";
				myPoly += Poly(2, 2);
				cout << "Now this is our current polynomial : ";
				myPoly.print(); cout << endl;
				cout << "Now let's multiply it with some constant, i.e. -3..\n";
				cout << "Instruction will be like :-\nmyPoly *= -3;\n";
				myPoly *= -3;
				cout << "Now this is our current polynomial : ";
				myPoly.print(); cout << endl;
				cout << "Now let's evaluate for a final time..\n";
				evaluate(myPoly);
				break;
			}
			case 11:{
				cout << "Thank you!! It was a lot of fun..\n";
			    exit(0);
			}
			default:
				cout << "Invalid Entry, Try Again!!\n\n";
				break;
		}
	}
	return 0;
}
