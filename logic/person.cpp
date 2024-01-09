#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "person.h"

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

void Member::setBooksBorrowed(Book book)
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
    // Set up variables for all the details to be entered.
    int idOfMember;
    std::string memberName, memberAddress, memberEmail;

    std::cout << "Please enter the member ID: " << std::endl;
    std::cin >> idOfMember;

    std::cout << "Please enter the member name: " << std::endl;
    std::cin >> memberName;

    std::cout << "Please enter the member Address: " << std::endl;
    std::cin >> memberAddress;

    std::cout << "Please enter the member email: " << std::endl;
    std::cin >> memberEmail;

    // After getting all the details, push the new member to the members vector.
    members.push_back(Member(idOfMember, memberName, memberAddress, memberEmail));
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

                    // Set up the three days to add to the current date for the due date.
                    int threeDays = 3 * 24 * 60 * 60;
                    Date date = Date(threeDays);

                    // Set the due date and add the book to the member's book list.
                    borrowedBook.setDueDate(date);
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
    for (auto& element : members) {

        // Identify the member that wants to return a book using their ID.
        // Note the memberID is converted from a string to int as the getMemberID method has to return a string.
        if (std::stoi(element.getMemberID()) == memberID) {
            
            // Loop through the user books and look for the matching book ID.
            // Return the book if there is a match and check if a fine needs to be added.
            // TODO: LEt the librarian know if the book ID isn't borrowed.
            for (auto& userBook : element.getBooksBorrowed()) {
                if (userBook.getBookID() == std::to_string(bookID)) {
                    
                    // Calculate how long it took for the book to be returned.
                    Date date = Date(0);
                    double timeDiff = date.calcTimeDiff(userBook.getDueDate().getTimeToMonitor(), date.getCurrentDateAndTime());
                    int threeDays = 3 * 24 * 60 * 60;

                    // If the time difference between lending and currentDate > 3, calculate a fine for the member.
                    // TODO fix this.
                    if (timeDiff > threeDays)  {
                        calcFine(std::stoi(element.getMemberID()));
                    }
                }
            }
        }
    }
}

void Librarian::calcFine(int memberID)
{
    int fine = 0;
    while (timeDiff > 0) {
    // Add to the fine and subtract one day (in seconds) per iteration.
    fine += 1;
    timeDiff -= 24 * 60 * 60;
    }
    // Provide user feedback.
    if (fine > 0) {
        std::cout << "The member owes fines amounting to: " << std::to_string(fine) << std::endl;
    }
    else {
        std::cout << "The member owes no fines." << std::endl;
    }
}
