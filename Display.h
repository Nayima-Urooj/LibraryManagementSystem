#ifndef DISPLAY_H
#define DISPLAY_H
using namespace std;
#include <string.h>
#include <string>
#include <exception>

class Display  //...base class 
{
public:
	virtual int Main_menu();  //...has different definations for different classes
	const void Title() const;  
	const void Exit() const;
	void List_book();
};

#endif // !DISPLAY_H