

#ifndef PATRON_HPP
#define PATRON_HPP


#include <string>
#include <vector>
using namespace std;

class Book;  // forward declaration

class Patron
{
private:
    std::string idNum;
    std::string name;
    std::vector<Book*> checkedOutBooks;
    double fineAmount;
public:
    Patron();
    Patron(std::string idn, std::string n);
    std::string getIdNum();
    std::string getName();
    std::vector<Book*> getCheckedOutBooks();
    void addBook(Book* b);
    void removeBook(Book* b);
    double getFineAmount();
    void setIdNum(string idn);
    void setName(string n);
    void setFineAmount(double amount);
    void amendFine(double amount);
  
};

#endif
