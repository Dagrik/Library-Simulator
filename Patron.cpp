//
//  Joshua Sears
//  10 Mar 15
//  CS 161-405
//  Final Project
//  This file contains the member functions for the Patron class.
//

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;
#include "Patron.hpp"
#include "Book.hpp"
//Default constructor
Patron::Patron(){
    setIdNum("");
    setName("");
    checkedOutBooks.empty();
    setFineAmount(0.0);
}

//Constructor
Patron::Patron(string idn, string n){
    setIdNum(idn);
    setName(n);
}

//Returns patron's ID number
string Patron::getIdNum(){
    return idNum;
}

//Returns patron's name
string Patron::getName(){
    return name;
}

//Returns list of checked out books
vector<Book*> Patron:: getCheckedOutBooks(){
    return checkedOutBooks;
}

//Adds book to checked out list
void Patron::addBook(Book* b){
    checkedOutBooks.push_back(b);
}

//Removes checked out book from list
void Patron::removeBook(Book* b){
    string test;
    for(int count = 0;count < checkedOutBooks.size();count++){
        test = checkedOutBooks[count]->getIdCode();
        if(test==(b->getIdCode())){
            checkedOutBooks.erase(checkedOutBooks.begin()+count);
        }
    }
}

//Returns value stored in fineAmount
double Patron::getFineAmount(){
    fineAmount=ceilf(fineAmount * 100.0) / 100.0;
return fineAmount;
}

//Sets fine amount
void Patron::setFineAmount(double amount){
    fineAmount=amount;
}

//Sets patron ID Number
void Patron::setIdNum(string idn){
    idNum=idn;
}

//Sets patron name
void Patron::setName(string n){
    name=n;
}


//Changes fine by new amount
void Patron::amendFine(double amount){
    fineAmount+=amount;
}


