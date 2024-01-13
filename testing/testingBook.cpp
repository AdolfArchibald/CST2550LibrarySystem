#include <iostream>
#include "../logic/book.h"
#include "../logic/person.h"
#include "../logic/date.h"

Book::Book(int bookID, std::string bookName, std::string authorFirstName, std::string authorLastName)
{
    this->bookID = bookID;
    this->bookName = bookName;
    this->borrower = nullptr;
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
    this->borrower = nullptr;
}

void Book::borrowBook(Member& borrower, Date dueDate)
{
    // Check if the book is not already borrowed
    if (this->borrower == nullptr) {
        this->borrower = &borrower;
        this->dueDate = dueDate;
        
        // Add the book to the user's books.
        std::vector<Book> memberBooks = borrower.getBooksBorrowed();
        this->setDueDate(dueDate);
        memberBooks.push_back(*this);

        borrower.setBooksBorrowed(memberBooks);
        std::cout << "\nSuccessfully issued the book " << bookName << " (ID: " << bookID << ")." << std::endl;

    } 
    else {
        // Let the user know that the book is not currently available
        std::cout << "The book is not available as someone else currently has it.";
    }
}
