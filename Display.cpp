#include <iostream>
#include <Windows.h>
#include <thread>
#include <chrono>
#include <fstream>
#include "Display.h"
using namespace std;

int Display::Main_menu()  //..initial display screen to ask user to select the mode of entrance in database
{
    system("cls");
    int number;
    cout << "\n\n";
    cout << "\t\t_____________________________________________________\n";
    cout << "\t\t        PLEASE WAIT WHILE THE SYSTEM LOADS           \n";
    cout << "\t\t_____________________________________________________\n";

    system("color 0a");                            //..green color to screen
    cout << "\n\n\n" << endl;
    char a = 177, b = 219;
    cout << "\t\t\t\t";                            //..creating a loading menu on the screen
    for (int i = 0; i <= 5; i++)
        cout << a;                                 //..a block of 10 segments
    cout << "\r";
    cout << "\t\t\t\t";
    for (int i = 0; i <= 5; i++)
    {
        cout << b;
        this_thread::sleep_for(chrono::seconds(1));    //...found this technique online...
                                                      //Source : https://en.cppreference.com/w/cpp/thread/sleep_for
    }

    system("cls");

    HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);          //...defining the "colour"
    SetConsoleTextAttribute(colour, 15);                     //..setting a single color (white) for display
  
    cout << "\n\n";
    cout << "       _____________________________________________________\n";
    cout << "             WELCOME TO THE LIBRARY MANAGEMENT SYSTEM       \n";
    cout << "       *                                                   *\n";
    cout << "       *   >> How do you want to enter in the database?    *\n";
    cout << "       *                                                   *\n";
    cout << "       *  1. As a User                                     *\n";
    cout << "       *  2. As an Admin                                   *\n";
    cout << "       _____________________________________________________\n";
    cout << "            \nPlease select your desired operation: " << endl;
    cin >> number;
    return number;
}

const void Display::Title() const              //...Creates a display screen while listing entries of database
{
    cout << "\n\n";
    cout << "\t _____________________________________________________\n";
    cout << "\t         DATA OF THE BOOKS STORED IN DIRECTORY         \n";
    cout << "\t _____________________________________________________\n\n";

    cout << "Book" << '\t' << "Author" << '\t' << "Catogery" << '\t' << "ID" << '\t' << "Price" << '\t' << "Quantity\n\n\n" << endl;
}

const void Display::Exit() const  //..exits the program 
{
    cout << "\n\n";
    cout << "\t_____________________________________________________\n";
    cout << "\t*                                                   *\n";
    cout << "\t*               EXITING THE DATABASE                *\n";
    cout << "\t_____________________________________________________\n\n" << endl;

    for (int i = 2; i >= 1; --i)
    {
        cout << "\t\tClosing in [ " << i << " ] seconds" << endl;

        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << "\n\t|| Thank you for using this books management system. Bye-Bye! ||\n\n" << endl;
}

void Display::List_book()         //lists all the entries of the books that are stored in a file
{
    cout << "\n\n";
    cout << "\t_____________________________________________________\n";
    cout << "\t*                                                   *\n";
    cout << "\t*         LIST ALL THE BOOKS OF DATABASE            *\n";
    cout << "\t_____________________________________________________\n" << endl;

    string* books_data;
    int count = 0;
    int i = 0;

    try
    {
        string read;
        fstream inFile;

        inFile.open("Data.txt", ios::in);             //..input mode for reading operation
        while (getline(inFile, read))                //...reading data till the end of file
        {
            count++;                                //..stores the total number of lines
        }
        inFile.close();
        books_data = new string[count];           //dynamic string to hold all the data of file

        inFile.open("Data.txt", ios::in);
        while (getline(inFile, read))
        { 
            books_data[i] = read;                 //...storing all the data of file to the dynamic array
            i++;
        }

        inFile.close();                          //..closing file after being read
        
        cout <<  "Name" << '\t' << "Author" << '\t' << "Category" << '\t' << '\t' << "ID " << '\t' << "Price" << '\t' << "Quantity" << endl;

        for (int i = 0; i < count; i++)
        {
            cout << books_data[i] << endl;      //...output the entries of the file to screen 
        }

        delete[] books_data;                //...freeing the memory in the end
    }

    catch (const char*)           //...catching exception
    {
        cout << "\nError, cannot open the file as no such file exists.";
    }

    cout << "\n\n";
    system("pause");
    cin.get();
    this->Main_menu();               //...calling the maimmenu function to perform another operation

}