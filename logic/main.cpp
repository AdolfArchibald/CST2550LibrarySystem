#include "person.h"
#include <iostream>

int main() {

    Librarian manager = Librarian(1, "Andrew", "12 Broad Road Meadows Estate", "andrew@thislibrary.com", 500);

    while (true) {

        std::string choice;

        std::cout << "Please select what you want to do:" << std::endl;
        std::cout << "1.) Add a member" << std::endl;
        std::cout << "2.) Issue a book to a member" << std::endl;
        std::cout << "3.) Return a book" << std::endl;
        std::cout << "4.) Display Books Borrowed by a member" << std::endl;

        std::cin >> choice;

        if (choice == "1") {
            manager.addMember();
            std::cout << "\n\n";
        }

        else if (choice == "2") {

            std::string memberID, bookID;

            std::cout << "Enter the member ID: ";
            std::cin >> memberID;
            std::cout << "/n";

            std::cout << "Enter the book ID: ";
            std::cin >> bookID;
            std::cout <<"/n";

            manager.issueBook(std::stoi(memberID), std::stoi(bookID));
            std::cout << "\n\n";
        }

        else if (choice == "3") {
            
            std::string memberID, bookID;

            std::cout << "Enter the member ID: ";
            std::cin >> memberID;
            std::cout << "/n";

            std::cout << "Enter the book ID: ";
            std::cin >> bookID;
            std::cout <<"/n";

            manager.returnBook(std::stoi(memberID), std::stoi(bookID));
            std::cout << "\n\n";
        }

        else if (choice == "4") {

            std::string memberID;

            std::cout << "Enter the member ID: ";
            std::cin >> memberID;
            std::cout << "/n";

            manager.displayBorrowedBooks(std::stoi(memberID));
            std::cout << "\n\n";
        }

        else {
            std::cout << "Please enter a valid number.\n" << std::endl;
        }
    }
    return 0;
}