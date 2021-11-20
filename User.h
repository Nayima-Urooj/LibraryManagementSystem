#ifndef USER_H
#define USER_H
using namespace std;
#include <string.h>
#include <string>
//#include "Library.h"
//#include "Display.h"

class User : public Books   //...Inherting the Books class (Multiple inheritance)
{
public:
	User() {};
	~User();
	User(string a, string b, string c, int d, int e, int f) : Books(a, b, c, d, e,f) {}; //..constructor to define attribute
	void login()override;  //...override because it's a pure virtual function in Books class
	int Main_menu()override;  //...override because it's a virtual function in Display class
	void Issue_book();
	void Return_book();
	void Compare_book();
	void Issued_book();
	void Sum_book();
};

#endif // USER_H
