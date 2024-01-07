#ifndef _BOOK_H_
#define _BOOK_H_

#include <string>
#include <ctime>
#include "person.h"

class Book {

    private:
        int bookID;
        std::string bookName;
        std::string authorFirstName;
        std::string authorLastName;
        std::string bookType;
        std::time_t dueDate;
        Member borrower;
    
    public:
        Book(int bookID, std::string bookName, std::string authorFirstName, std::string authorLastName);

        std::string getBookID();
        std::string getBookName();
        std::string getAuthorFirstName();
        std::string getAuthorLastName();

        std::time_t getDueDate();

        void setDueDate(std::time_t dueDate);
        void returnBook();
        void borrowBook(Member Borrower, std::time_t dueDate);
};

#endif