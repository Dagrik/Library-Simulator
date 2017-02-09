//Joshua Sears
//13 Mar 15
//CS161-405
//This file contains the class definitions of the Library class

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

#include "Library.hpp"
#include "Patron.hpp"
#include "Book.hpp"

//Default constructor
Library::Library(){
    holdings.reserve(100);
    members.reserve(100);
    currentDate=0;
}

/**********************
 Program: This program adds a book to the library
 Parameters: None
 *********************/
void Library::addBook(){
    string newID="";
    string newTitle="";
    string newAuth="";
    int test=0;
    
    
    //Get new book information from user
    cout << "What is the id number for the book? :";
    getline(cin, newID);
   
    cout << "What is the title of the new book? :";
    getline(cin, newTitle);
   
    cout << "Who is the author of the new book? :";
    getline(cin, newAuth);
    
    //Get book place
    test=testBookId(newID);
    
    //Display error if book id already exists
    while (test!=-1 && !(holdings.empty())){
        cout << endl << "ID number already taken." << endl;
        return;
    }
    
    //Create new book object
    Book newBook(newID, newTitle, newAuth);
    
    //add to holdings array
    holdings.push_back(newBook);

    return;
}

/**********************
 Program: This program adds a Patron to the library
 Parameters: None
 *********************/
void Library::addMember(){
    string newID="";
    string newName="";
    int test = 0;
    
    //Get new Patron info from user
    cout << "What is the id number patron? :";
    getline(cin, newID);
    
    cout << "What is the name of the patron? :";
    getline(cin, newName);
   
    //Get patron array location
    test = testPatronId(newID);
    
    //Error if patron ID used
    while (test!=-1){
        cout << endl << "ID number already taken." << endl;
        return;
    }
    
    //create new Patron object
    Patron newPatron(newID, newName);
    
    //Add to members array
    members.push_back(newPatron);
    
    return;
    
}
/**********************
 Program: This program checks out a book to a patron, or says its unavailable
 Parameters: a Book ID code and a Patron ID num
 *********************/
void Library::checkOutBook(string patronID, string bookID){
    int pPlace=0, bPlace=0;
    
    //Find location of patron
    pPlace=testPatronId(patronID);
   
    //Error if patron doesn't exist
    while (pPlace==-1){
        cout << "The patron ID you provided is invalid." << endl;
        return;
        
    }
    
    //Find book location in holdings
    bPlace = testBookId(bookID);
    
    //Error if book doesn't exist
    while (bPlace==-1){
        cout << "The book ID you provided is invalid." << endl;
        return;
    }
    
    //Checks for book availability
    for(int count=0; count < holdings.size();count++){
        if(bookID==holdings[count].getIdCode()){
            if(holdings[count].getLocation()==2){
                cout << "Book is currently checked out." << endl;
                return;
            }
            if(holdings[count].getLocation()==1 && patronID!=(holdings[count].getRequestedBy()->getIdNum())){
                cout << "Book was requested by someone else." << endl;
                return;
            }
        }
    
    }
    
    //Sets checkoutby in book object
    holdings[bPlace].setCheckedOutBy(&members[pPlace]);
  
    //gives book to patron object
    members[pPlace].addBook(&holdings[bPlace]);
    
    //sets book location
    holdings[bPlace].setLocation(CHECKED_OUT);
    
    //outputs the result
    cout << members[pPlace].getName() << " has checked out "<< holdings[bPlace].getTitle() << "."<< endl;
    
    //Clears setRequestedBy
    holdings[bPlace].setRequestedBy(NULL);
    //Sets date of checked out
    holdings[bPlace].setDateCheckedOut(currentDate);
}

/**********************
 Program: This program returns a checked out book, or displays error if cannot
 Parameters: a Book ID code
 *********************/
void Library::returnBook(string bookID){
    int bPlace=0, pPlace = 0;
    string pat;
    
    //Get holdings vector location
    bPlace = testBookId(bookID);
    
    //Error if book doesn't exist
    if(bPlace==-1){
        cout << "The book ID you provided is invalid." << endl;
        return;
    }
    
    //Checks if book is checked out
    if(holdings[bPlace].getLocation()!=2){
        cout << "That book is not checked out." << endl;
        return;
    }
    
    //Checks if book is requested to know where to return book.
    if(holdings[bPlace].getRequestedBy() ==0)
        holdings[bPlace].setLocation(ON_SHELF);
    else
        holdings[bPlace].setLocation(ON_HOLD_SHELF);

    pat=holdings[bPlace].getCheckedOutBy()->getIdNum();
    
    //Gets location of patron in member array
    pPlace = testPatronId(pat);
    
    //Removes book from the patron
    members[pPlace].removeBook(&holdings[bPlace]);
    
    //Displays result
    cout << holdings[bPlace].getTitle() << " has been returned." << endl;
    
    return;
}

/**********************
 Program: This program allows a patron to place a hold on a book, or an error
 Parameters: a Book ID code and a Patron ID num
 *********************/
void Library::requestBook(string patronID, string bookID){
    
    //Gets book and patron locations
    int bPlace = testBookId(bookID);
    int pPlace = testPatronId(patronID);
    
    if(holdings[bPlace].getCheckedOutBy()->getIdNum()==patronID){
        cout << "You have already got the book!" << endl;
        return;
    }
    
    //Checks if book has already been requested, then sets shelf
    if(holdings[bPlace].getRequestedBy()==0){
        holdings[bPlace].setRequestedBy(&members[pPlace]);
        if(holdings[bPlace].getLocation()==0)
            holdings[bPlace].setLocation(ON_HOLD_SHELF);
            cout << holdings[bPlace].getTitle() << " has been requested by "
        << members[pPlace].getName() << "." << endl;
            return;
    }else{
        cout << "That book has already been requested!";
        return;
    }
    
    
    
}
/**********************
 Program: This program increments current date; increase each Patron's fines by 10 cents for each overdue Book they have checked out (using amendFine)
 Parameters: none
 *********************/
void Library::incrementCurrentDate(){
   
    //increment current date
    currentDate++;
    
    int daysOut=0;
    
    //Adds overdue fees to each patron for each book they have overdue
    for(int count=0;count<members.size();count++){
        Patron* pPtr = &members[count];
        for(int books=0;books<pPtr->getCheckedOutBooks().size(); books++){
            vector<Book*> bList=pPtr->getCheckedOutBooks();
            daysOut=currentDate - bList[books]->getDateCheckedOut();
            if(daysOut>21){
                members[count].amendFine(.10);
            }
        }
    }
    
}

/**********************
 Program: uses amendFine to update the Patron's fine; print out that the fines for Patron name are now Patron fineAmount
 Parameters: a Patron IDnum and payment amount
 *********************/
void Library::payFine(string patronID, double payment){
    int pPlace = testPatronId(patronID);
    if(payment > members[pPlace].getFineAmount()){
        cout << "That patron doesn't owe that much!" << endl;
    return;
    }else{
        members[pPlace].amendFine(-payment);
        cout << "This patron now owes " << members[pPlace].getFineAmount() << endl;
        return;
    }
        
}

/**********************
 Program: prints the Patron's ID, name, the titles of any checked out Books, and their current fines or displays an error
 Parameters: a Patron IDnum
 *********************/
void Library::viewPatronInfo(string patronID){
    int pPlace=testPatronId(patronID);
    
    if (pPlace==-1){
        cout << "That patron ID does not exist." << endl;
        return;
    }
    
    Patron* ptr=&members[pPlace];
    
    
    cout << "Patron ID: " << ptr->getIdNum() << endl;
    cout << "Patron Name: " << ptr->getName() << endl;
    cout << "Checked Out Books:" << endl;
    for(int count=0;count< ptr->getCheckedOutBooks().size();count++){
        Book* bookPtr = ptr->getCheckedOutBooks()[count];
        cout << "     Book ID: " << bookPtr->getIdCode() << endl;
        cout << "     Book Name: " << bookPtr->getTitle() << endl;
        cout << "     Book Author: "<< bookPtr->getAuthor() << endl;
        cout << "     Date Checked Out: " << bookPtr->getDateCheckedOut()<< endl << endl;
    }
    cout << "Total Fines Due: " << fixed << setprecision(2) << "$" << ptr->getFineAmount() << endl;
}

/**********************
 Program: print the Book's ID, title, author and location; the name of the Patron whom it's requested by (if any); the name of the Patron whom it's checked out by (if any), and the number of days left till it's due (or the word "overdue").
 Parameters: a Book ID code
 *********************/
void Library::viewBookInfo(string bookID){
    int bPlace=testBookId(bookID);
    int loc=0;
    if (bPlace==-1){
        cout << "That book ID does not exist." << endl;
        return;
    }
    cout << "Book ID: " << holdings[bPlace].getIdCode() << endl;
    cout << "Book Name: " << holdings[bPlace].getTitle() << endl;
    cout << "Book Author: "<< holdings[bPlace].getAuthor() << endl;
    cout << "Current Location: " ;
    loc=holdings[bPlace].getLocation();
    switch(loc){
        case 0: cout << "On shelf" << endl;
            break;
        case 1: cout << "On hold" << endl;
            break;
        case 2: cout << "Checked out" << endl;
    }
   
    if(loc==2){
        cout << "Checked Out By: " << holdings[bPlace].getCheckedOutBy()->getName() << endl;
        cout << "Book Checked Out On: " << holdings[bPlace].getDateCheckedOut() << endl;
    }
    if(holdings[bPlace].getRequestedBy()!=NULL){
        
        cout << "Requested By: " << holdings[bPlace].getRequestedBy()->getName()
             << endl;
        cout << endl;
    }
    
    if(holdings[bPlace].getLocation()==2){
    cout << "Days left until due: ";
    if((21+(holdings[bPlace].getDateCheckedOut())-currentDate)<0){
        cout << "Overdue" << endl;
    }else
        cout << 21+(holdings[bPlace].getDateCheckedOut())-currentDate << endl;
    }}

/**********************
 Program: tests and returns where the book is in the library holdings array, or a -1 if it doesn't exist
 Parameters: a Book ID code
 *********************/
int Library::testBookId(string id){
    for(int count=0; count<holdings.size(); count++){
        
        if(id==holdings[count].getIdCode()){
            
            return count;
        }
    }
            return -1;
}

/**********************
 Program: tests and returns where the patron is in the library members array, or a -1 if it doesn't exist
 Parameters: a patron ID number
 *********************/
int Library::testPatronId(string id){
    for(int count=0; count<members.size(); count++){
        if(id==members[count].getIdNum())
            return count;
    }
            return -1;
}
