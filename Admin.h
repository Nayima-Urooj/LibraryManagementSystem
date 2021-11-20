#ifndef ADMIN_H
#define ADMIN_H
using namespace std;
#include <string.h>
#include <string>
#include "Books.h"
#include "Display.h"

class Admin : public Books          //...Inherting the Books class (Multiple inheritance)
{
public:
	Admin() {};
	~Admin();
	Admin(string a, string b, string c, int d, int e, int f) : Books(a, b, c, d, e,f) {};//...constructor to define attribut

	void login() override; //...override because it's a pure virtual function in Books class
	int Main_menu() override; //...override because it's a virtual function in Display class
	void Edit_book();
	void Add_book();
	void Delete_book();
	void Search_book();
	void Delete_book(string name);
	void Add_book(string a, string b, string c, string d, string e, string f);

	
};
#endif // !ADMIN_H

