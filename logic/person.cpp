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

void Member::setBooksBorrowed(const Book& book)
{
    booksLoaned.push_back(book);
}

Librarian::Librarian(int staffId, std::string name, std::string address, std::string email, int salary) : Person(name, address, email)
{
    this->staffId = staffId;
    this->salary = salary;
}

void Librarian::addMember()
{   
    std::string memberID, memberName, memberEmail, memberAddress;

    std::cout << "Please enter the member details below:" << std::endl;

    std::cout << "Member ID: ";
    std::cin >> memberID;
    std::cout << "\n";

    std::cout << "Member Name: ";
    std::cin >> memberName;
    std::cout << "\n";

    std::cout << "Member Email: ";
    std::cin >> memberEmail;
    std::cout << "\n";

    std::cout << "Member Address: ";
    std::cin >> memberAddress;
    std::cout << "\n";

    // After getting all the details, push the new member to the members vector.
    members.push_back(Member(std::stoi(memberID), memberName, memberAddress, memberEmail));
}

// TODO: Inform the librarian that their member and book ID is valid or invalid.
void Librarian::issueBook(int memberID, int bookID)
{
    // Loop through all the members in the members array.
    for (auto& element : members) {

        // Identify the member that wants to borrow a book using their ID.
        // Note the memberID is converted from a string to int as the getMemberID method has to return a string.
        if (std::stoi(element.getMemberID()) == memberID) {

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

                    // Ask the librarian to enter the due date for the book.
                    int day, month, year;
                    std::cout << "Enter the requested information in number form eg. 2023 07 16" << std::endl;

                    std::cout << "Enter the year the book has to be returned: ";
                    std::cin >> year;
                    std::cout << "\n";

                    std::cout << "Enter the month the book has to be returned: ";
                    std::cin >> month;
                    std::cout << "\n";

                    std::cout << "Enter the day the book has to be returned: ";
                    std::cin >> day;
                    std::cout << "\n";

                    // Set the due date and add the book to the member's book list.
                    borrowedBook.setDueDate(Date(day, month, year));
                    element.setBooksBorrowed(Book(std::stoi(bookId), bookName, authorFirst, authorLast));

                    // Close the file after successfully getting the book information.
                    file.close();
                }
            }
        }
    }
}

void Librarian::returnBook(int memberID, int bookID)
{
    // Loop through all the members in the members array.
    for (auto& member : members) {

        // Identify the member that wants to return a book using their ID.
        // Note the memberID is converted from a string to int as the getMemberID method has to return a string.
        if (std::stoi(member.getMemberID()) == memberID) {
            
            // Loop through the user books and look for the matching book ID.
            // Return the book if there is a match and check if a fine needs to be added.
            // TODO: LEt the librarian know if the book ID isn't borrowed.
            for (auto& userBook : member.getBooksBorrowed()) {
                if (userBook.getBookID() == std::to_string(bookID)) {
                    calcFine(std::stoi(member.getMemberID()), std::stoi(userBook.getBookID()));
                    // TODO: Remove the book from member.
                    std::cout << "Successfully returned the book: " << userBook.getBookName() << std::endl;
                }
            }
        }
    } 
}

// Added a parameter to this method to be able to calculate the fine.
void Librarian::calcFine(int memberID, int bookID)
{
    // Identify the book in the member's borrowed books.
    for (auto& member : members) {
        if (member.getMemberID() == std::to_string(memberID)) {
            for (auto& book : member.getBooksBorrowed()) {
                if (book.getBookID() == std::to_string(bookID)) {

                    // Calculate how long it took for the book to be returned.
                    // Ask the librarian for the current date before proceeding.
                    int day, month, year;
                    std::cout << "Enter the requested information in number form eg. 2023 07 16" << std::endl;

                    std::cout << "Enter the current year: ";
                    std::cin >> year;
                    std::cout << "\n";

                    std::cout << "Enter the current month: ";
                    std::cin >> month;
                    std::cout << "\n";

                    std::cout << "Enter the current day: ";
                    std::cin >> day;
                    std::cout << "\n";
                    
                    int diff = getDiffInDates(Date(day, month, year), book.getDueDate());

                    // Issue a fine using the fine aount 
                    if (diff < 0) {
                        diff *= -1;
                        int dailyFineAmount = 1;
                        int totalFine = dailyFineAmount * diff;

                        std::cout << "The books was " << std::to_string(diff) << " days late." << std::endl;
                        std::cout << "The member has to pay a fine amounting to: £" << std::to_string(totalFine) << ".00" << std::endl;
                    }
                    else {
                        std::cout << "The member returned the book within the given period." << std::endl;
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
            std::cout << "The member's borrowed books are:" << std::endl;
            int number = 1;

            for (auto& book : member.getBooksBorrowed()) {
                std::cout << std::to_string(number) << ".) " << "ID: " << book.getBookID() << "    Name: " << book.getBookName() << std::endl;
                number += 1;
            }
        }
    }
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
