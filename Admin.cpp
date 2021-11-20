#include <string.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <exception>
#include <chrono>
#include "Admin.h"
#include "User.h"
#include "Display.h"
#include "Books.h"

using namespace std;

Admin::~Admin()   //...default destructor
{
}

void Admin::login()    //...login function to enter the credentials of administrator
{
    system("cls");
    cout << "\n\n";
    cout << "\t_____________________________________________________\n";
    cout << "\t*                                                   *\n";
    cout << "\t*    Please enter the login details to continue     *\n";
    cout << "\t_____________________________________________________\n" << endl;

    char* name = new char[10];
    char *password = new char[10];             //dynamic array to store the characters
    cout << "\n\n";

    while (true)                  //...breaks if the user entered the right credentials
    {
        try
        {
            cout << "-> Please enter the Username: ";
            cin >> name;
            cout << "-> Please enter the Password: ";
            cin >> password;

            if (strcmp(name, "Admin") == 0 && strcmp(password, "1234") == 0)       //...checks the right credentials
            {
                break;            //...breaks, goes to mainmenu upon succeess
            }
            else
                throw 1;                 //...exception thrown
        }
        catch (int)       //...exception caught
        {
            cout << "\nOops!! You entered the wrong inputs, try again!!\n" << endl;
            continue;
        }
    }

    system("cls");
    this->Main_menu();
}

int Admin::Main_menu()
{
    system("cls");
    int number, n;
    cout << "\n\n";
    cout << "       _____________________________________________________\n";
    cout << "                         CHOOSE YOUR COMMAND                \n";
    cout << "                                                            \n";
    cout << "       *                                                   *\n";
    cout << "       *   >> Please choose one of the following options:  *\n";
    cout << "       *                                                   *\n";
    cout << "       *  1. Add an entry to books                         *\n";
    cout << "       *  2. Delete an entry from books                    *\n";
    cout << "       *  3. Search enteries by book name                  *\n";
    cout << "       *  4. Edit the entries of book                      *\n";
    cout << "       *  5. List all the stored books                     *\n";
    cout << "       *  6. Exit                                          *\n\n";
    cout << "       _____________________________________________________\n";
    cout << "            \nPlease select your desired operation: " << endl;

    try
    {
        cin >> number;
        if (number < 7 && number > 0)
        {
            switch (number)
            {
            case 0:
                system("cls");
                Display::Main_menu();
                break;
            case 1:
                system("cls");
                do
                {
                    system("cls");
                    Add_book();
                    cout << "\n\nIf you want to add more books, press 1." << endl;
                    cout << "\nTo go back to Mainmenu, press any other number";
                    cin >> n;
                } while (n == 1);
                if (n != 1)
                    this->Main_menu();
                break;
            case 2:
                system("cls");
                Delete_book();
                break;
            case 3:
                system("cls");
                Search_book();
                break;
            case 4:
                system("cls");
                Edit_book();
                break;
            case 5:
                system("cls");
                List_book();
                break;
            case 6:
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
            cout << "Reloading in [ " << i << " ] seconds" << endl;

            this_thread::sleep_for(chrono::seconds(1));
        }

        system("cls");
        int n = Main_menu();
    }
    return 0;
}

void Admin::Edit_book()   //...modifies the entries of file 
{
    cout << "\n\n";
    cout << "\t_____________________________________________________\n";
    cout << "\t*                                                   *\n";
    cout << "\t*            EDITING BOOKS IN THE DATABASE           *\n";
    cout << "\t_____________________________________________________\n" << endl;

    string name, new_name;
    string author, new_author;
    string catogery, new_catogery;
    string ID, new_ID;
    string price, new_price;
    string quantity, new_quantity;

    int check = 0;

    try         //...exception handling to check if the file was opened or not
    {
        ifstream inFile;
        inFile.open("Data.txt", ios::in);      //...opening file in the input
        if (inFile.fail())
            throw "err";     

        string sName;
        cout << "Please enter the name of book that you want to modify" << endl;
        cin >> sName;

        char ch;

        if (!inFile.eof())     //...reading content till the end of file
        {
            string read;
            while (getline(inFile, read))
            {
                istringstream iss(read);     //...istringstream to parse the strings from file
                iss >> name;

                if (name == sName)
                {
                    istringstream iss(read);
                    iss >> author >> catogery >> ID >> price >> quantity;  //...reading the content from file
                    new_name = name;
                    new_author = author;
                    new_catogery = catogery;
                    new_ID = ID;
                    new_price = price;
                    new_quantity = quantity;         //...updating the new attributes to store next

                    cout << "\n\t| Great! Book with these credentials was found. |\n" << endl;

                    if (inFile.eof())
                        break; //...double check to ensure EOF fault
                    cout << "Book" << '\t' << "Author" << '\t' << "Catogery" << '\t' << "ID" << '\t' << "Price" << '\t' << "Quantity\n" << endl;
                    cout << name << '\t' << author << '\t' << catogery << '\t' << ID << '\t' << price << '\t' << quantity << endl;

                    cout << "\n\tDo you want to really want to change the data of book? (Y/N)" << endl;
                    getchar();
                    if (getchar() == 'y' || getchar() == 'Y')
                    {
                        system("cls");

                        cout << "Write the name of book: ";
                        cin >> name;
                        new_name = name;
                        cout << "Write the author name: ";
                        cin >> author;
                        new_author = author;
                        cout << "Write the catogery of book: ";
                        cin >> catogery;
                        new_catogery = catogery;
                        cout << "Write the ID of book: ";
                        cin >> ID;
                        new_ID = ID;
                        cout << "Write the price of book: ";
                        cin >> price;
                        new_price = price;
                        cout << "Write the quantity of book: ";
                        cin >> quantity;
                        new_quantity = quantity;
                        check = 1;

                        Delete_book(name); //...calling the function to delete the old entry (the one that user modfied)
                        Add_book(new_name, new_author, new_catogery, new_ID, new_price, new_quantity); //...adding the newly                                                                        added entry to the file
                    }
                    else
                        goto End;  //...going out of the loop if the user changes his mind
                }
            }

        }
    }
    catch (const char* )
    {
        cout << "\nError, cannot open the file as no such file exists.";
    }
    if (check == 1)
    {
        cout << "\n\nCongratulations! Your entry is successfully modified" << endl;
    }
    else
    {
        cout << "\n\nOoops!!No such book was found in the directory" << endl;
    }
    End:          //...label : in case user doesn't want to modify the data
    cout << "\n\n";
    system("pause");
    cin.get();
    this->Main_menu();
}

void Admin::Add_book()    //...Adding a new entry to the file, key function to start everything
{
    cout << "\n\n";
    cout << "\t_____________________________________________________\n";
    cout << "\t*                                                   *\n";
    cout << "\t*            ADDING BOOKS IN THE DATABASE           *\n";
    cout << "\t_____________________________________________________\n" << endl;

    ofstream outFile;
    try         //...exception handling to ensure the safe opening of file
    {
        outFile.open("Data.txt", ios::app);     //...openeing file in the append mode, creates one if not already present
        cin.ignore();

        if (outFile.fail())
            throw "err";            //...throws exception if not opeened due to some reasons

        cout << "\n\n";
        cout << "Please enter the Book name: ";
        getline(cin, name);             //...getting input from user
        outFile << name << "\t";        //...writing the user entered entry into the file

        cout << "Please enter the Book author: ";
        getline(cin, author);
        outFile << author << "\t";

        cout << "Please enter the Book catogery: ";
        getline(cin, catogery);
        outFile << catogery << "\t";

        cout << "Please enter the Book ID: ";
        cin >> ID;

        while (cin.fail())     //...checking that the user cannot enter string to the int data type to prevent error
        {
            cout << "Error! Please enter an integer value" << endl;
            cin.clear();
            cin.ignore(256, '\n');             //...clearing the input console
            cin >> ID;
        }

        outFile << ID << "\t";

        fflush(stdin);               //...clearing the input buffer

        cout << "Please enter the Book price: ";
        cin >> price;

        while (cin.fail())
        {
            cout << "Error! Please enter an integer value" << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cin >> price;
        }
        outFile << price << "\t";

        cout << "Please enter the quantity of books: ";
        cin >> quantity;

        while (cin.fail())
        {
            cout << "Error! Please enter an integer value";
            cin.clear();
            cin.ignore(256, '\n');
            cin >> quantity;
        }
        outFile << quantity << endl;

    }

    catch (const char*)              //...catching the exception for safe use
    {
        cout << "\nError, cannot open the file as no such file exists.";
    }

    outFile.close();        //...closing file in the end
}

void Admin::Search_book()     //...Searching the entries of the book from the database
{
    cout << "\n\n";
    cout << "\t_____________________________________________________\n";
    cout << "\t*                                                   *\n";
    cout << "\t*            SEARCHING BOOKS FROM DATABSE           *\n";
    cout << "\t_____________________________________________________\n" << endl;

    try
    {
        string name;
        string author;
        string catogery;
        string ID;
        string price;
        string quantity;

        ifstream inFile;      
        inFile.open("Data.txt", ios::in);           //...openeing the file in input mode for reading 

        if (inFile.fail())
            throw "err";          //...throws exception in case the file doesn't open

        string sName;
        cout << "Please enter the name of book" << endl;
        cin >> sName;

        system("cls");
        int check = 0;
        Title();          //...menu display for lisitng an entry of file

        while (inFile.good())           //...read till the end of file
        {
            string read;
            getline(inFile, read);

            istringstream iss(read);

            if (iss >> name)    //...another check point to ensure the end of file (prevent eof error)
            {
                if (name == sName)
                {
                    istringstream iss(read);
                    iss >> author >> catogery >> ID >> price >> quantity;   //...parsing the strings to the file
                    cout << name << '\t' << author << '\t' << catogery << '\t' << '\t' << ID << '\t' << price << '\t' << quantity << endl;
                    check = 1;
                }
            }
        }

        if (check == 0)
            cout << "No such book is found in the directory!!" << endl;
    }
    catch (const char* )        //...exception caught
    {
        cout << "\nError, cannot open the file as no such file exists.";
    }
    cout << "\n\n";
    system("pause");
    cin.get();
    this->Main_menu();
}

void Admin::Delete_book()   //...deleting an entry from the database
{

    cout << "\n\n";
    cout << "\t_____________________________________________________\n";
    cout << "\t*                                                   *\n";
    cout << "\t*            DELETING BOOKS FROM DATABSE             *\n";
    cout << "\t_____________________________________________________\n" << endl;

    string name;
    try
    {
        ifstream inFile;
        inFile.open("Data.txt");   //...opening the original file

        if (inFile.fail())
            throw "err";              //...exception is thrown in case of file not being opened

        string sName;
        cout << "Please enter the name of book that you want to delete" << endl;
        cin >> sName;

        ofstream temp_inFile;        
        temp_inFile.open("temp_Data.txt", ios::app);  //creating a file in append mode, creating and writing a temp file

        if (temp_inFile.fail())
            throw "err";                   //...throws the same exception

        int check = 0;                     //...variable to ensure that the data has been deleted 

        while (!inFile.eof())
        {
            string read;
            (getline(inFile, read));
            istringstream iss(read);        //...parsing the strings from file
            iss >> name; 

            if (name != sName)
            {
                temp_inFile << read << endl; //...writing in the file iff the name wasn't meant to be deleted
            }
            else
            {
                check = 1;
            }
        }


        inFile.close();
        temp_inFile.close();        //...closing both the files
        remove("Data.txt");         //...deleting the old file
        int n = rename("temp_Data.txt", "Data.txt");    //...renaming the updated file to old one

        if (check == 1)
        {
            cout << "The given entry [ " << sName << " ] has been successfully deleted from the directory." << endl;
        }
        else
        {
            cout << "Error! No such book is found in the directory.";
        }
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

void Admin::Delete_book(string sName)    //...makes use in Edit_book() function to delete old entry
{
    try
    {
        string name;

        ifstream inFile;
        inFile.open("Data.txt");       //...openeing the file

        ofstream temp_inFile;
        temp_inFile.open("temp_Data.txt", ios::app);        //...append mode (create + write)
        if (temp_inFile.fail())
            throw "err";           //...exception thrown

        while (!inFile.eof())      //...reading till the end of file
        {
            string read;
            (getline(inFile, read));
            istringstream iss(read);
            iss >> name;

            if (name != sName)
            {
                temp_inFile << read << endl;    //...writing in the new file except the name parameter line
            }
        }

        inFile.close();
        temp_inFile.close();
        remove("Data.txt");         //...removing old file
        int n = rename("temp_Data.txt", "Data.txt");  //...renaming new updated file to the old one....
    }
    catch (const char* str)
    {
        cout << "Error, no file exists" << endl;
    }
}

void Admin::Add_book(string nname, string nauthor, string ncatogery, string nID, string nprice, string nquantity) 
{                                                  //...makes use in the Edit_book(), adds the modifed entry to the file
    try 
    {
       ofstream inFile;
       inFile.open("Data.txt");          //...openeing the file to write into it
       if (inFile.fail())
           throw "err";                    //...exception thrown
       inFile << nname << '\t' << nauthor << '\t' << ncatogery << '\t' << nID << '\t' << nprice << '\t' << nquantity << endl;       //...writing everything to the file
       inFile.close();          //...closing the file in the end
    }
    catch (const char* str)
    {                                            //...exception is caught
        cout << "Error, no file exists";
    }

}

