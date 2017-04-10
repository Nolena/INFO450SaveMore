// Info450_Assignment 3.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime> //Extra Credit

using namespace std;

class Accounts 
{

protected:
	int acctNum;
	float intRate;
	float balance;
	time_t now = time(0); //Extra Credit
	char* opendate = ctime(&now); //Extra Credit
	tm *ltm = localtime(&now);  //Extra Credit
	
public:
	Accounts() {};
	Accounts(int aNum, float bal, float i, char* date) //Extra Credit
	{
		acctNum = aNum;  balance = bal; intRate = i; opendate = date; //Extra Credit

		opendate = asctime(ltm); //Extra Credit
	}
	virtual void Display()=0;
	virtual float Deposite(float dep)=0;
	virtual float Withdrawl(float with)=0;
	virtual float OrderChecks()=0;
	virtual float MonthlyInt()=0;
};

class Savings : public Accounts 
{

public:
	Savings(int aNum, float bal, float i, char* date) : Accounts (aNum, bal, i, date){}
	float Withdrawl(float with);
	float Deposite(float dep);
	float MonthlyInt();
	void Display();
	float OrderChecks();
};

float Savings::Deposite(float dep) 
{
	balance += dep;
	return 0;
}

float Savings::Withdrawl(float with) 
{
	if (balance - with - 2 < 0)
	{
		cout << "Insufficent Funds!" << endl;
		return -1;
	}
	else 
	{
		balance -= (with + 2);
		return 0;
	}
}

float Savings::MonthlyInt()
{
	if (balance >= 10000)
	{

		intRate = (balance *.02) / 12;
	}
	else
	{
		intRate = (balance *.01) / 12;
	}

	return intRate;
}

float Savings::OrderChecks() 
{
	return 0;
}

void Savings::Display() 
{
	cout << "Savings Account: " << acctNum << endl;
	cout << "Interest: " << intRate << endl;
	cout << "Balance: " << balance << endl;
	cout << "Date: " << opendate << endl;
}

class Checking : public Accounts
{

public:
	Checking(int aNum, float bal, float i, char* date) : Accounts (aNum, bal, i, date)
	{
		if (balance < 500)
			balance -= 5;
	}
	float Withdrawl(float with);
	float Deposite(float dep);
	float OrderChecks();
	float MonthlyInt();
	void Display();
};

float Checking::Deposite(float dep) 
{
	balance += dep;
	return 0;
}

float Checking::Withdrawl(float with) 
{
	if (balance - with < 0) 
	{
		cout << "Insufficent funds!" << endl;
		return -1;
	}
	else 
	{
		balance -= with;
		return 0;
	}
}

float Checking::OrderChecks() 
{
		balance -= 15;
		return balance;
}

float Checking::MonthlyInt() 
{
	return intRate;
}

void Checking::Display()
{
	cout << "Checking Account: " << acctNum << endl;
	cout << "Balance: " << balance << endl;
	cout << "Date: " << opendate << endl;
}

class CertificateOfDeposite : public Accounts
{
	int term;

public:
	CertificateOfDeposite() {};
	CertificateOfDeposite(int aNum, float bal, float i, int t, char* date) : Accounts(aNum, bal, i, date)
	{
		term = t;
	}
	float Withdrawl(float with);
	float Deposite(float dep);
	float MonthlyInt();
	float OrderChecks();
	void Display();

};

float CertificateOfDeposite::Deposite(float dep) 
{
	balance += dep;
	return 0;
}

float CertificateOfDeposite::Withdrawl(float with) 
{
	if (balance - with < 0) 
	{
		cout << "Insuffiecent Funds!" << endl;
		return -1;
	}
	else 
	{
		float fee = balance *.1;
		balance -= fee + with;
		return 0;
	}

}

float CertificateOfDeposite::MonthlyInt() 
{
	if (term >= 5)
	{
		intRate = (balance * .1)/12;
	}
	else
	{
		intRate = (balance * .05)/12;
	}

	return intRate;
}

float CertificateOfDeposite::OrderChecks() 
{
	return 0;
}

void CertificateOfDeposite::Display()
{
	cout << "Certificate of Deposite: " << acctNum << endl;
	cout << "Monthly Interest: " << intRate << endl;
	cout << "Balance: " << balance << endl;
	cout << "date: " << opendate << endl;
}

int main()
{
	Accounts** myAccounts = new Accounts*[10];
	myAccounts[0] = new Savings(11111, 0, 0, 0);
	myAccounts[1] = new Checking(11112, 0, 0, 0);
	myAccounts[2] = new CertificateOfDeposite(11113, 0, 0, 3, 0);

	cout << "Welcome to Save-More Bank! Press Enter to progress." << endl;
	cin.ignore();

	cout << "Creating a Savings Account" << endl;
	myAccounts[0]->Deposite(10000);
	myAccounts[0]->Display();
	cin.ignore();

	cout << "Creating a Checking Account" << endl;
	myAccounts[1]->Deposite(600);
	myAccounts[1]->Display();
	cin.ignore();

	cout << "Creating a Certificate of Deposite" << endl;
	myAccounts[2]->Deposite(10000);
	myAccounts[2]->Display();
	cin.ignore();

	cout << "What is the Monthly Interest of Interest bearing accounts?" << endl;
	cin.ignore();

	cout << "Savings Account: 11111" << endl;
	cout << "----------------------" << endl;
	cout << "Monthly Interest Rate: ";
	cout << myAccounts[0]->MonthlyInt() << endl;
	cin.ignore();

	cout << "Certificate of Deposite: 11113" << endl;
	cout << "------------------------------" << endl;
	cout << "Monthly Interest Rate: ";
	cout << myAccounts[2]->MonthlyInt() << endl;
	cin.ignore();

	cout << "Current active accounts" << endl;
	cout << "=======================" << endl;
	myAccounts[0]->Display();
	cout << "---------------------" << endl;
	myAccounts[1]->Display();
	cout << "---------------------" << endl;
	myAccounts[2]->Display();
	cout << "---------------------" << endl;
	cin.ignore();

	cout << "Press enter to order checks." << endl;
	cin.ignore();
	myAccounts[1]->OrderChecks();
	myAccounts[1]->Display();
	cin.ignore();

	cout << "Withdraw $200 from Checking account 11112" << endl;
	myAccounts[1]->Withdrawl(200);
	myAccounts[1]->Display();
	cin.ignore();

	cout << "Withdraw $1000 from checking account 11111" << endl;
	myAccounts[0]->Withdrawl(1000);
	myAccounts[0]->Display();
	cin.ignore();

	cout << "Early Withdrawl from Certificate of Deposite 11113 of $2000" << endl;
	myAccounts[2]->Withdrawl(2000);
	myAccounts[2]->Display();
	cin.ignore();

	cout << "Current active accounts" << endl;
	cout << "=======================" << endl;
	myAccounts[0]->Display();
	cout << "---------------------" << endl;
	myAccounts[1]->Display();
	cout << "---------------------" << endl;
	myAccounts[2]->Display();
	cout << "---------------------" << endl;

	return 0;
}

