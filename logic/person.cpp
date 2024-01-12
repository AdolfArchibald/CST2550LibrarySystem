#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "person.h"
#include "date.h"

Person::Person(std::string name, std::string address, std::string email)
{
    this->name = name;
    this->address = address;
    this->email = email;
}

Person::~Person()
{
}

std::string Person::getAddress()
{
    return address;
}

std::string Person::getEmail()
{
    return email;
}

std::string Person::getName() 
{
    return name;
}

void Person::setAddress(std::string address)
{
    this->address = address;
}

void Person::setEmail(std::string email)
{
    this->email = email;
}

void Person::setName(std::string name)
{
    this->name = name;
}

Member::Member(int memberId, std::string name, std::string address, std::string email) : Person(name, address, email)
{
    this->memberId = memberId;
}

std::string Member::getMemberID()
{
    return std::to_string(memberId);
}

std::vector<Book> Member::getBooksBorrowed()
{
    return booksLoaned;
}

void Member::setBooksBorrowed(const std::vector<Book>& books)
{
    this->booksLoaned = books;
}

Librarian::Librarian(int staffId, std::string name, std::string address, std::string email, int salary) : Person(name, address, email)
{
    this->staffId = staffId;
    this->salary = salary;
}

void Librarian::addMember()
{   
    // Get the details of the member.
    std::string memberID, memberName, memberEmail, memberAddress;

    std::cout << "Please enter the member details below:" << std::endl;

    std::cout << "Member ID: ";
    std::cin >> memberID;

    std::cout << "Member Name: ";
    std::cin >> memberName;

    std::cout << "Member Email: ";
    std::cin >> memberEmail;

    std::cout << "Member Address: ";
    std::cin >> memberAddress;

    // After getting all the details, push the new member to the members vector.
    try {
        members.push_back(Member(std::stoi(memberID), memberName, memberAddress, memberEmail));
    }
    catch (const std::invalid_argument& e) {
        std::cout << "\nMember ID needs to be an integer. Please try adding a member again.\n" << std::endl;
        return;
    }
    
    // Display the new member, with the details to the librarian.
    std::cout << "\nNew Member Created. Details are as follows:\n\n";
    std::cout << "Member ID:       " << memberID << std::endl;
    std::cout << "Member Name:     " << memberName << std::endl;
    std::cout << "Member Email:    " << memberEmail << std::endl;
    std::cout << "Member Address:  " << memberAddress << std::endl;
}

void Librarian::issueBook(int memberID, int bookID)
{
    // Loop through all the members in the members array.
    for (auto& member : members) {

        // Identify the member that wants to borrow a book using their ID.
        // Note the memberID is converted from a string to int as the getMemberID method has to return a string.
        if (std::stoi(member.getMemberID()) == memberID) {

            // Open the file.
            std::ifstream file;
            file.open("library_books.csv");

            // Variables to store the values from each line.
            std::string line;
            std::string bookId, bookName, pageCount, authorFirst, authorLast, bookType;
            
            // Looping through all the lines until the desired book ID is reached.
            while (std::getline(file, line)) {

                // Split the line into values using stringstream and grab the book ID for identification.
                std::istringstream ss(line);
                std::getline(ss, bookId, ',');

                // If the book ID gets a match, add the book object to the member's list.
                if (bookId == std::to_string(bookID)) {
                    
                    // Get all the book information for the correct book.
                    std::getline(ss, bookName, ',');
                    std::getline(ss, pageCount, ',');
                    std::getline(ss, authorFirst, ',');
                    std::getline(ss, authorLast, ',');
                    std::getline(ss, bookType, ',');
                    
                    // Instantiate the book using the information.
                    Book borrowedBook = Book(std::stoi(bookId), bookName, authorFirst, authorLast);

                    for (auto& memberNew : members) {
                        for (auto& bookNew : memberNew.getBooksBorrowed()) {
                            if (bookNew.getBookID() == borrowedBook.getBookID()) {
                                std::cout << "The book is already borrowed. Please come back later." << std::endl;
                                return;
                            }
                        }
                    }

                    // Ask the librarian to enter the due date for the book.
                    std::string day, month, year;
                    std::cout << "Enter the requested information in number form eg. 2023 07 16:" << std::endl;
                    std::cout << "\n";

                    std::cout << "Enter the year the book has to be returned: ";
                    std::cin >> year;

                    std::cout << "Enter the month the book has to be returned: ";
                    std::cin >> month;

                    std::cout << "Enter the day the book has to be returned: ";
                    std::cin >> day;

                    // Set the due date and add the book to the member's book list.
                    try {
                        int intDay, intMonth, intYear;
                        intDay = std::stoi(day);
                        intMonth = std::stoi(month);
                        intYear = std::stoi(year);

                        borrowedBook.setDueDate(Date(intDay, intMonth, intYear));

                        std::vector<Book> memberBooks = member.getBooksBorrowed();
                        memberBooks.push_back(borrowedBook);
                        member.setBooksBorrowed(memberBooks);

                        // Inform the librarian the book was issued and close the file.
                        std::cout << "\nSuccessfully issued the book " << bookName << " (ID: " << bookID << ")." << std::endl;
                        file.close();
                        return;
                    }
                    catch (const std::invalid_argument& e) {
                        std::cout << "Invalid entries for the date. Please retry." << std::endl;
                        return;
                    }
                }
            }
            std::cout << "Invalid Book ID. Please make sure the book ID entered is correct." << std::endl;
            return;
        }
    }
    std::cout << "Invalid member ID. Please make sure the entered member ID exists." << std::endl;
    return;
}

void Librarian::returnBook(int memberID, int bookID)
{
    for (int i = 0; i < (int) members.size(); i++) {
        if (members[i].getMemberID() == std::to_string(memberID)) {
            
            std::vector<Book> memberBooks;
            std::vector<Book> returnedBooks;

            for (auto& book : members[i].getBooksBorrowed()) {
                if (book.getBookID() != std::to_string(bookID)) {
                    memberBooks.push_back(book);
                }
                else {
                    returnedBooks.push_back(book);
                }
            }

            if ((int) returnedBooks.size() == 0) {
                std::cout << members[i].getName() << " does not have the book with ID " << std::to_string(bookID) << std::endl;
                std::cout << "Please enter a book ID pertaining to the member." << std::endl;
                return;
            }

            calcFine(memberID, bookID);
            members[i].setBooksBorrowed(memberBooks);
            std::cout << "Returned the book with name: " << returnedBooks[0].getBookName() << " (ID: " << std::to_string(bookID) << ")." << std::endl;
            return;
        }
    }
    std::cout << "The given member ID has no associated member." << std::endl;
    return;
}

void Librarian::calcFine(int memberID, int bookID)
{
    // Identify the book in the member's borrowed books.
    for (auto& member : members) {
        if (member.getMemberID() == std::to_string(memberID)) {
            for (auto& book : member.getBooksBorrowed()) {
                if (book.getBookID() == std::to_string(bookID)) {

                    // Calculate how long it took for the book to be returned.
                    // Ask the librarian for the current date before proceeding.
                    std::string day, month, year;
                    std::cout << "Enter the requested information in number form eg. 2023 07 16" << std::endl;

                    std::cout << "Enter the current year: ";
                    std::cin >> year;

                    std::cout << "Enter the current month: ";
                    std::cin >> month;

                    std::cout << "Enter the current day: ";
                    std::cin >> day;
                    
                    try {
                        int diff = getDiffInDates(Date(std::stoi(day), std::stoi(month), std::stoi(year)), book.getDueDate());

                        // Issue a fine using the fine amount.
                        if (diff > 0) {
                            int dailyFineAmount = 1;
                            int totalFine = dailyFineAmount * diff;

                            std::cout << "\nThe books was " << std::to_string(diff) << " days late." << std::endl;
                            std::cout << "The member has to pay a fine amounting to: £" << std::to_string(totalFine) << ".00" << std::endl;
                        }
                        else {
                            std::cout << "\nThe member returned the book within the given period." << std::endl;
                        }
                    }
                    catch (const std::invalid_argument& e) {
                        std::cout << "\nInvalid entries for the date. Please try entering the date again.\n" << std::endl;
                        calcFine(memberID, bookID);
                    }
                }
            }
        }
    }
}

void Librarian::displayBorrowedBooks(int memberID)
{
    for(auto& member : members) {
        if (std::stoi(member.getMemberID()) == memberID) {
            
            // Display the member's books (if there are any).
            if (member.getBooksBorrowed().size() > 0) {
                std::cout << "The member's borrowed books are:" << std::endl;
                int number = 1;

                for (auto& book : member.getBooksBorrowed()) {
                std::cout << std::to_string(number) << ".) " << "ID: " << book.getBookID() << "    Name: " << book.getBookName() << std::endl;
                number += 1;
                }
                return;
            }
            else {
                std::cout << "The member currently has no borrowed books.";
                return;
            }
        }
    }
    std::cout << "The specified member does not exist." << std::endl;
}

int Librarian::getstaffID()
{
    return staffId;
}

int Librarian::getSalary()
{
    return salary;
}

void Librarian::setStaffID(int staffID)
{
    this->staffId = staffID;
}

void Librarian::setSalary(int salary)
{
    this->salary = salary;
}
