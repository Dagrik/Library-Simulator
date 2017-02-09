//
//  Joshua Sears
//  10 Mar 15
//  CS 161-405
//  Final Project
//  This file contains the member functions for the Book class.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "Book.hpp"
#include "Patron.hpp"

//Default constructor
Book::Book(){
    setIdCode(" ");
    setTitle(" ");
    setAuthor(" ");
    setLocation(ON_SHELF);
    setCheckedOutBy(NULL);
    setRequestedBy(NULL);
    setDateCheckedOut(0);
}

//constructor
Book::Book(string idc, string t, string a){
    setIdCode(idc);
    setTitle(t);
    setAuthor(a);
    setLocation(ON_SHELF);
    setCheckedOutBy(NULL);
    setRequestedBy(NULL);
    setDateCheckedOut(0);
    
}

//returns book id
string Book::getIdCode(){
    return idCode;
}

//returns book title
string Book::getTitle(){
    return title;
}

//returns book author
string Book::getAuthor(){
    return author;
}

//sets book id code
void Book::setIdCode(string id){
    idCode = id;
}

//set book title
void Book::setTitle(string t){
    title = t;
}

//set boot author
void Book::setAuthor(string a){
    author = a;
}

//returns books location
Locale Book::getLocation(){
    return location;
}

//sets book location
void Book::setLocation(Locale lo){
    location=lo;
}

//returns who checked out book
Patron* Book::getCheckedOutBy(){
    return checkedOutBy;
}

//sets who checks out book
void Book::setCheckedOutBy(Patron* p){
    checkedOutBy = p;
}

//returns who requested book
Patron* Book::getRequestedBy(){
    return requestedBy;
}

//sets who requested book
void Book::setRequestedBy(Patron* p){
    requestedBy = p;
}

//returns the date book was checked out
int Book::getDateCheckedOut(){
    return dateCheckedOut;
}

//sets the date book was checked out
void Book::setDateCheckedOut(int d){
    dateCheckedOut = d;
}