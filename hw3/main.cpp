#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
//DISPLAY 11.3 Money ClassVersion 1
//Program to demonstrate the class Money.
#include <iostream>
#include <cstdlib>
#include <cctype>
using namespace std;

//Class for amounts of money in U.S. currency.
class Money
{
public:
    friend Money add(Money amount1, Money amount2);
    //Precondition: amount1 and amount2 have been given values.
    //Returns the sum of the values of amount1 and amount2.

    friend bool equal(Money amount1, Money amount2);
    //Precondition: amount1 and amount2 have been given values.
    //Returns true if the amount1 and amount2 have the same value;
    //otherwise, returns false.

    Money(long dollars, int cents);
    //Initializes the object so its value represents an amount with the
    //dollars and cents given by the arguments. If the amount is negative,
    //then both dollars and cents must be negative.

    Money(long dollars);
    //Initializes the object so its value represents $dollars.00.

    Money( );
    //Initializes the object so its value represents $0.00.

    double getValue( );
    //Precondition: The calling object has been given a value.
    //Returns the amount of money recorded in the data of the calling object.

    void input(istream& ins);
    //Precondition: If ins is a file input stream, then ins has already been
    //connected to a file. An amount of money, including a dollar sign, has been
    //entered in the input stream ins. Notation for negative amounts is -$100.00.
    //Postcondition: The value of the calling object has been set to
    //the amount of money read from the input stream ins.

    void output(ostream& outs);
    //Precondition: If outs is a file output stream, then outs has already been
    //connected to a file.
    //Postcondition: A dollar sign and the amount of money recorded
    //in the calling object have been sent to the output stream outs.
private:
    long allCents;
};



int digitToInt(char c);
//Function declaration for function used in the definition of Money::input:
//Precondition: c is one of the digits '0' through '9'.
//Returns the integer for the digit; for example, digitToInt('3') returns 3.


Money add(Money amount1, Money amount2)
{
    Money temp;

    temp.allCents = amount1.allCents + amount2.allCents;
    return temp;
}

bool equal(Money amount1, Money amount2)
{
    return (amount1.allCents == amount2.allCents);
}

Money::Money(long dollars, int cents)
{
    if(dollars*cents < 0) //If one is negative and one is positive


    {
        cout << "Illegal values for dollars and cents.\n";
        exit(1);
    }
    allCents = dollars*100 + cents;
}

Money::Money(long dollars) : allCents(dollars*100)
{
    //Body intentionally blank.
}

Money::Money( ) : allCents(0)
{
    //Body intentionally blank.
}

double Money::getValue( )
{
    return (allCents * 0.01);
}
//Uses iostream, cctype, cstdlib:
void Money::input(istream& ins)
{
    char oneChar, decimalPoint,
            digit1, digit2; //digits for the amount of cents
    long dollars;
    int cents;
    bool negative;//set to true if input is negative.

    ins >> oneChar;
    if (oneChar == '-')
    {
        negative = true;
        ins >> oneChar; //read '$'
    }
    else
        negative = false;
    //if input is legal, then oneChar == '$'

    ins >> dollars >> decimalPoint >> digit1 >> digit2;

    if ( oneChar != '$' || decimalPoint != '.'
         || !isdigit(digit1) || !isdigit(digit2) )


    {
        cout << "Error illegal form for money input\n";
        exit(1);
    }
    cents = digitToInt(digit1)*10 + digitToInt(digit2);

    allCents = dollars*100 + cents;
    if (negative)
        allCents = -allCents;
}

//Uses cstdlib and iostream:
void Money::output(ostream& outs)
{
    long positiveCents, dollars, cents;
    positiveCents = labs(allCents);
    dollars = positiveCents/100;
    cents = positiveCents%100;

    if (allCents < 0)
        outs << "-$" << dollars << '.';
    else
        outs << "$" << dollars << '.';

    if (cents < 10)
        outs << '0';
    outs << cents;
}

int digitToInt(char c)
{
    return (static_cast<int>(c) - static_cast<int>('0') );
}






class Check
{
    int checkNumber;
    Money checkAmount;
    bool checkCashed;
public:
    Check (int checkNumber,Money checkAmount, bool checkCashed ): checkNumber(checkNumber), checkAmount(checkAmount), checkCashed(checkCashed){}
    int get_checkNumber() const{return checkNumber;}
    Money get_checkAmount() const{return checkAmount;}
    bool get_checkCashed() const{return checkCashed;}
    void set_checkNumber(int checknum) {checkNumber = checknum; }
    void set_checkAmount ( Money checkamt) {checkAmount = checkamt;}
    void set_checkCashed (bool checkC) {checkCashed = checkC;}

};
//class CheckBook



int main()
    {
        Money initial, expected, amount;
        int checknum = 0;
        bool cashed_yn = false;
        vector<Check> checks;
        vector<Money> money;

        cout << "Enter old bank balance in Money format: ";
        initial.input(cin);
        cout << "Enter new bank balance in Money format: ";
        expected.input(cin);

        while (checknum >= 0)
        {
            cout << "Enter the check number, or negative number to end: ";
            cin >> checknum; //overwriting check num

            if (checknum >= 0)
            {
                cout << "Enter amount of check in Money format: ";
                amount.input(cin);
                cout << "Enter (1) if cashed (0) if uncashed: ";
                cin >> cashed_yn;
                checks.push_back(Check(checknum, amount, cashed_yn));
            }
        }

        while (amount.getValue() >= 0)
        {
            cout << "Enter the deposit amount in Money format, or a negative Money amount to end: ";
            amount.input(cin);
            if (amount.getValue() >= 0)
                money.push_back(amount); //amount is already of type money
        }

        double total_deposits = 0.0, total_checks_cashed = 0.0, total_checks_uncashed = 0.0;
        double difference, acc_tot;

        for (Money i : money)
            total_deposits += i.getValue();
        cout << "Total deposits: $" << total_deposits << endl;

        for (Check i : checks)
        {
            if (i.get_checkCashed())
                total_checks_cashed += i.get_checkAmount().getValue();
            else
                total_checks_uncashed += i.get_checkAmount().getValue();
        }
        cout << "Total checks cashed: $" << total_checks_cashed << endl;
        cout << "Total checks uncashed: $" << total_checks_uncashed << endl;

        acc_tot = initial.getValue() + total_deposits - total_checks_cashed;
        difference = expected.getValue() - acc_tot;

        cout << "Difference between expected bank balance and actual balance: $" << difference << endl;

        cout << "List of all cashed checks: " << endl;
        for (Check i : checks)
            if (i.get_checkCashed())
                cout << i.get_checkNumber() << endl;

        cout << "List of all uncashed checks: " << endl;
        for (Check i : checks)
            if (!i.get_checkCashed())
                cout << i.get_checkNumber() << endl;

        return 0;
    }



}