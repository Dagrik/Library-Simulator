//Joshua Sears
//13 Mar 15
//CS161-405
//This project contains a library simulator program which allows the user to add a book or patron, increment the day, pay fines, return or request a book, and view patron or book data.  The program will include the Library, Book, and Patron class types.

#include <iostream>
#include <string>
using namespace std;

#include "Library.hpp"
#include "Book.hpp"
#include "Patron.hpp"

int main(){
    int choice=0;
    string patronID="";
    string bookID="";
    Library lib;
    double amount =0;
    
    while(choice!=10){
        
        cout <<  endl << "Welcome to the Library Simulator!" << endl;
        cout << "Please choose from the following options: " << endl;
        cout << "1.  Add a new book to the library" << endl;
        cout << "2.  Add a new member to the library" << endl;
        cout << "3.  Have a member check out a book" << endl;
        cout << "4.  Return a book" << endl;
        cout << "5.  Have a patron request a book" << endl;
        cout << "6.  Increment the current date" << endl;
        cout << "7.  Pay a member's fine" << endl;
        cout << "8.  View a member's information" << endl;
        cout << "9.  View a book's information" << endl;
        cout << "10. Exit the program" << endl;
        cout << "Please enter a choice: ";
        cin >> choice;
        cin.ignore();
        cout << endl;
       
    
        switch (choice){
            case 1: 
                lib.addBook();
                break;
            case 2:  lib.addMember();
                break;
            case 3: cout << "Which patron ID would you like to choose: ";
                getline(cin, patronID);
               
                cout << endl << "What is the ID of the book being checked out?";
                getline(cin, bookID);
                
                lib.checkOutBook(patronID, bookID);
                break;
            case 4:  cout << "What is the book ID to return? ";
                getline(cin, bookID);
                lib.returnBook(bookID);
                break;
            case 5:  cout << "What is the patron ID? ";
                getline(cin, patronID);
                cout << endl << "What is the ID of the book being requested?";
                getline(cin, bookID);
                lib.requestBook(patronID, bookID);
                break;
            case 6: lib.incrementCurrentDate();
                break;
            case 7: cout << "What is the patron ID? ";
                getline(cin, patronID);
                cout << "How much are they paying?";
                cin >> amount;
                lib.payFine(patronID, amount);
                break;
            case 8: cout << "What is the patron ID? ";
                getline(cin, patronID);
                lib.viewPatronInfo(patronID);
                break;
            case 9: cout << "What is the book ID? ";
                getline(cin, bookID);
                lib.viewBookInfo(bookID);
                break;
            case 10: return 0;
            default: cout << "Invalid choice!  Please choose again" << endl;
        }
        
    }
}