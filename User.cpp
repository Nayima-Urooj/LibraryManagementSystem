#include <string.h>
#include <string>
#include <fstream>
#include <conio.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <chrono>
#include "Books.h"
#include "User.h"
#include "Display.h"
#include "Admin.h"
using namespace std;

User::~User()  //...Default destructor
{
}

void User::login()      //...asks the user to enter the login details for user
{
    system("cls");
    char* name = new char[10];
    char* password = new char[10];
    cout << "\n\n";
    cout << "\t_____________________________________________________\n";
    cout << "\t*                                                   *\n";
    cout << "\t*   Please enter the login details to continue      *\n";
    cout << "\t_____________________________________________________\n" << endl;
    
    while (true)
    {
        try
        {
            cout << "-> Please enter the Username: ";
            cin >> name;
            cout << "-> Please enter the Password: ";
            cin >> password;

            if (strcmp(name, "User") == 0 && strcmp(password, "1234") == 0) //..checks if the credentials are right
            {
                break;  //...goes to the main menu
            }
            else
                throw 1;       //...throwing exception if not correct
        }
        catch (int)
        {
            cout << "\nOops!! You entered the wrong inputs, try again!!\n" << endl;
            continue;
        }
    }
    delete[] name;
    delete[] password;
    system("cls");
    this->Main_menu();
}

int User::Main_menu()  //..main menu function to display the tasks of user 
{
    system("cls");
    int number;
    cout << "\n\n";
    cout << "       _____________________________________________________\n";
    cout << "                         CHOOSE YOUR COMMAND                \n";
    cout << "                                                            \n";
    cout << "       *                                                   *\n";
    cout << "       *   >> Please choose one of the following options:  *\n";
    cout << "       *                                                   *\n";
    cout << "       *  1. List all the books                            *\n";
    cout << "       *  2. Issue an added book                           *\n";
    cout << "       *  3. Count all the price of issued books           *\n";
    cout << "       *  4. Compare the entries of books                  *\n";
    cout << "       *  5. Return an issued book                         *\n";
    cout << "       *  6. List all the issued books                     *\n";
    cout << "       *  7. Exit                                          *\n\n";
    cout << "       _____________________________________________________\n";
    cout << "            \nPlease select your desired operation: " << endl;

    try
    {
        cin >> number;
        if (number < 8 && number >= 0)
        {
            switch (number)        //..switch statement to handle all the cases 
            {
            case 0:
                system("cls");          //...clearing console screen for clean output display
                Display::Main_menu();
                break;
            case 1:
                system("cls");
                List_book();
                break;
            case 2:
                system("cls");
                Issue_book();
                break;
            case 3:
                system("cls");
                Sum_book();
                break;
            case 4:
                system("cls");
                Compare_book();
                break;
            case 5:
                system("cls");
                Return_book();
                break;
            case 6:
                system("cls");
                Issued_book();
                break;
            case 7:
                system("cls");
                Exit();
                break;
            }
        }
        else
            throw number;

     }
        catch (int)
        {
            cout << "\nOops! You entered the wrong number." << endl;
            for (int i = 3; i >= 1; --i)
            {
                cout << "Reloading in [ " << i << " ] seconds" << endl;  //... a kind of "effect" for loading

                this_thread::sleep_for(chrono::seconds(1));
            }

            system("cls");
            int n = Main_menu();
        }
        return 0;
    
}

void User::Issue_book()
{
    int day, month, year;
    cout << "\n\n";
    cout << "\t_____________________________________________________\n";
    cout << "\t*                                                   *\n";
    cout << "\t*            ISSUING BOOKS FROM DATABSE             *\n";
    cout << "\t_____________________________________________________\n" << endl;

    string name;
    try                         //...exception handling to check if the file was opened or not
    {
        ifstream inFile;         
        inFile.open("Data.txt");

        if (inFile.fail())          //...if file wasn't already created
            throw "err";

        string sName;
        cout << "Please enter the name of book that you want to issue" << endl;
        cin >> sName;
        cout << "Please enter the date in (DD/MM/YYYY) format" << endl;
        cin >> day >> month >> year;

        ofstream newFile;
        newFile.open("Issued_books.txt", ios::app);     //...opening file in append mode to write into it, creates file if                                                not already present

        if (newFile.fail())
            throw "err";                           //...throws the same exception

        int check = 0;

        while (!inFile.eof())        //...checking the end of file
        {
            string read;
            (getline(inFile, read));
            istringstream iss(read);

            if (iss >> name)         //...reading file as long as it can see characters, mainly to prevent error of EOF
            {
                if (name == sName)
                {
                    newFile << day << "/" << month << "/" << year;           //...writing into the new file
                    newFile << '\t' << read << endl;         
                    check = 1;                             //...ensures that the name was found 

                }
            }
        }


        inFile.close();
        newFile.close();             //...closing both files in the end

        if (check == 1)
        {
            cout << "The book [ " << sName << " ] has been successfully issued" << endl;
        }
        else
        {
            cout << "Error! No such book is found in the directory.";
        }
    }
    catch ( const char*)        //...exception catching
    {
        cout << "\nError, cannot open the file as no such file exists.";
    }

    cout << "\n\n";
    system("pause");
    cin.get();
    this->Main_menu();
}

void User::Sum_book()   //...checks the total price of books that are being issued to the user
{
    cout << "\n\n";
    cout << "\t_____________________________________________________\n";
    cout << "\t*                                                   *\n";
    cout << "\t*      TOTAL PRICE OF BOOKS IN DATABASE          *\n";
    cout << "\t_____________________________________________________\n\n" << endl;

    string date;
    string name;
    string author;
    string catogery;
    string ID;
    string price;
    string quantity; 

    int sum = 0;

    try              //...exception handling for file openeing disasters
    {
        ifstream inFile;
        inFile.open("Issued_books.txt");       //...opening the file

        if (inFile.fail())
            throw "err";

        while (!inFile.eof())
        {
            string read;                        //string to read the file content
            (getline(inFile, read));
            istringstream iss(read);
            if (iss >> date)                   //...getting the date to avoid it's parsing while calculating price and                                             making sure that file is being read till end
            {
                iss >> name >> author >> catogery >> ID >> price >> quantity;
                if (inFile.eof())
                    break;
                sum += stoi(price);    //...integer conversion from string parsing
            }
        }

        cout << "The total price of Issued books in the directory is [ " << sum << " ]";  //...displaying sum to screen
        inFile.close();
    }

    catch (const char* )
    {
        cout << "\nError, cannot open the file as no such file exists.";
    }

    cout << "\n\n";
    system("pause");        //...waits for input from user
    cin.get();
    this->Main_menu();

}

void User::Issued_book()    //...checking the list of all the issued books
{
    cout << "\n\n";
    cout << "\t_____________________________________________________\n";
    cout << "\t*                                                   *\n";
    cout << "\t*            CHECK ALL THE ISSUED BOOKS             *\n";
    cout << "\t_____________________________________________________\n" << endl;

    string* books_data;    //char array to read the content of file
    int count = 0;
    int i = 0;

    try
    {
        string read;
        fstream inFile;

        inFile.open("Issued_books.txt", ios::in);
        while (getline(inFile, read))
        {
            count++;   //...counting the file content
        }
        inFile.close();
        books_data = new string[count];     //...dyanmic array of size of the content of file

        inFile.open("Issued_books.txt", ios::in);
        while (getline(inFile, read))
        {
            books_data[i] = read;        //...copying all the data to the dynamic array
            i++;
        }

        inFile.close();
        
        cout << "Date" << '\t'<<'\t' << "Name" << '\t' << "Author" << '\t' << "Category" << '\t' << "ID " << '\t' << "Price" << '\t' << "Quantity\n\n" << endl;

        for (int i = 0; i < count; i++)
        {
            cout << books_data[i] << endl;
        }

        delete[] books_data;        //...deleting the dynamically array
    }

    catch (const char*)
    {
        cout << "\nError, cannot open the file as no such file exists.";
    }

    cout << "\n\n";
    system("pause");
    cin.get();
    this->Main_menu();
}

void User::Compare_book()   //...compares the price of books
{
    cout << "\n\n";
    cout << "\t_____________________________________________________\n";
    cout << "\t*                                                   *\n";
    cout << "\t*         MOST EXPENSIVE BOOK FROM DATABSE          *\n";
    cout << "\t_____________________________________________________\n" << endl;


    string name, mname;
    string author, mauthor;
    string catogery, mcatogery;
    string ID, mID;
    string price, mprice;
    string quantity, mquantity;
    string date;

    int max = 0;
    try
    {
        ifstream inFile;
        inFile.open("Issued_books.txt");

        if (inFile.fail())
            throw "err";

        Title();   //...menu before listing the entries to the screen

        while (!inFile.eof())
        {
            string read;
            (getline(inFile, read));
            istringstream iss(read);
            if (iss >> date)
            {
                iss >> name >> author >> catogery >> ID >> price >> quantity;  //...parsing strings from file
                if (inFile.eof())
                    break;

                if (stoi(price) > max)     //...comparing the price with the max = 0 for first iteration
                {
                    mname = name;
                    mauthor = author;          //...updating the credentials to the one of maximum price 
                    mcatogery = catogery;
                    mID = ID;
                    mprice = price;
                    mquantity = quantity;

                    max = stoi(price);      //changes the value of max to current max
                }
            }
        }
                
        cout << mname << '\t' << mauthor << '\t' << mcatogery << '\t' << '\t' << mID << '\t' << mprice << '\t' << mquantity << '\t' << endl;
         
        
        inFile.close();
    }
    catch (const char*)
    {
        cout << "Error, no such file is created yet.";        //...exception thrown
    }
    cout << "\n\n";
    system("pause");
    cin.get();
    this->Main_menu();

}

void User::Return_book()  //...removes entry from the issued_books.txt file
{

    cout << "\n\n";
    cout << "\t_____________________________________________________\n";
    cout << "\t*                                                   *\n";
    cout << "\t*            RETURNING BOOKS TO DATABSE             *\n";
    cout << "\t_____________________________________________________\n" << endl;

    string name, date;

    ifstream inFile;
    inFile.open("Issued_books.txt");

    string sName;
    cout << "Please enter the name of book that you want to return" << endl;
    cin >> sName;                

    ofstream temp_inFile;              //...creating a file to copy the content of original file
    temp_inFile.open("temp_Data.txt", ios::app);

    int check = 0;

    while (!inFile.eof())
    {
        string read;
        (getline(inFile, read));
        istringstream iss(read);

        if (iss >> date)  //...ensuring the end of file
        {
            iss >> name;

            if (name != sName)  //...if the name is found, do not copy that line
            {
                temp_inFile << read << endl;         //...copying the rest of the data to the file
            }
            else
            {
                check = 1;
            }
        }
    }

    inFile.close();
    temp_inFile.close();
    remove("Issued_books.txt");  //..deleting the original file
    int n = rename("temp_Data.txt", "Issued_books.txt");  //..renaming old file to the new one with updated data

    if (check == 1)
    {
        cout << "The given entry [ " << sName << " ] has been successfully removed from the issued list." << endl;
    }
    else
    {
        cout << "Error! No such book was issued from the directory.";
    }

    cout << "\n\n";
    system("pause");
    cin.get();
    this->Main_menu();
}


