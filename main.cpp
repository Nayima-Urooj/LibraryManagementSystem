#include <iostream>
#include <chrono>
#include <thread>
#include "Books.h"
#include "User.h"
#include "Admin.h"
#include "Display.h"
using namespace std;

int main()
{
    Books* book;                    
    Display* display = new Display(); //..calling the first display of console screen
    while(1)
    {
    int number = display->Main_menu();  //..calls the mainmenu function to check how user wants to enter in database
    char ch;

        try {                      //...making sure that user selects one of the given numbers
            if (number < 3 && number > 0)
            {
                if (number == 1)
                {
                    try {
                        book = new User(); //...dynamically creates the object
                    }
                    catch (bad_alloc&)
                    {
                        cout << "Memory allocation exception." << endl;
                        exit(1);             //...closes the program in case of bad memory allocation
                    }
                    book->login();
                    delete book;   //...avoiding memory leak/waste
                    break;
                }
                else
                {
                    try {
                        book = new Admin();
                    }
                    catch (bad_alloc&) //catches the exception if the memory was not assigned to avoid misbehave 
                    {
                        cout << "Memory allocation exception." << endl;
                        exit(1);
                    }
                    book->login();
                    delete book; //frees the memory garbage in the end
                    break;
                }
            }
            else
                throw number;
        }

        catch (int)
        {
            cout << "Oops! Wrong choice. Please select one of the above panels." << endl;
            system("pause");
            cin.get();
            continue; //...goes to the input menu again
        }
    }
    delete display;  //..freeing memory garbage
    return 0;
}