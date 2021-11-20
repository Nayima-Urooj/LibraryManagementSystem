#ifndef BOOKS_H
#define BOOKS_H
using namespace std;
#include <string>
#include <string.h>
#include "Display.h"

class Books : public Display     //...inheritign Display class
{
protected:
	string name;
	string author;
	string catogery;
	int ID;
	int price;
	int quantity;
	
public:
	Books(string a="check", string b="check", string c="check", int d=0, int e=0, int f=0) : name(a), author(b), catogery(c), ID(d), price(e), quantity(f) {};  //...constructor to initialized all the attributes
	virtual void login() = 0;       //...pure virtual function
};


#endif // !BOOKS_H





