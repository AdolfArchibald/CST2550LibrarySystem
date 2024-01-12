#ifndef _BOOK_H_
#define _BOOK_H_

#include <string>
#include <ctime>
#include "person.h"
#include "date.h"

class Member;

class Book {

    private:
        int bookID;
        std::string bookName;
        std::string authorFirstName;
        std::string authorLastName;
        std::string bookType;
        Date dueDate{0, 0, 0};
        Member* borrower;
    
    public:
        Book(int bookID, std::string bookName, std::string authorFirstName, std::string authorLastName);

        std::string getBookID();
        std::string getBookName();
        std::string getAuthorFirstName();
        std::string getAuthorLastName();

        Date getDueDate();

        void setDueDate(Date dueDate);
        void returnBook();
        void borrowBook(Member borrower, Date dueDate);
};

#endif