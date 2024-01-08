#include <iostream>
#include "book.h"
#include "person.h"
#include "date.h"

Book::Book(int bookID, std::string bookName, std::string authorFirstName, std::string authorLastName)
{
    this->bookID = bookID;
    this->bookName = bookName;
    this->authorFirstName = authorFirstName;
    this->authorLastName = authorLastName;
}

std::string Book::getBookID()
{
    return std::to_string(bookID);
}

std::string Book::getBookName()
{
    return bookName;
}

std::string Book::getAuthorFirstName()
{
    return authorFirstName;
}

std::string Book::getAuthorLastName()
{
    return authorLastName;
}

Date Book::getDueDate()
{
    return dueDate;
}

void Book::setDueDate(Date dueDate)
{
    this->dueDate = dueDate;
}

void Book::returnBook()
{
    this->borrower = Member(0, "", "", "");
}

void Book::borrowBook(Member borrower, Date dueDate)
{
    // Check if the book is not already borrowed
    if (this->borrower.getMemberID() == "0") {
        this->borrower = borrower;
        this->dueDate = dueDate;
        borrower.setBooksBorrowed(*this);
    } else {
        // Let the user know that the book is not currently available
        std::cout << "The book is not available as someone else currently has it.";
    }
}
