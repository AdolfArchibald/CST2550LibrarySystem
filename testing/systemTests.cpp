#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../logic/person.h"
#include <iostream>

TEST_CASE("Testing Getters and Setters", "[person]") {
    std::cout << "TESTING\n" << std::endl;

    Librarian manager = Librarian(10, "Jack", "Narrow Street 7", "jack@librarymail.com", 5000);
    Member member1 = Member(10, "James", "Home Street", "james@mail.com");

    SECTION("Getters") {
        REQUIRE(manager.getName() == "Jack");
        REQUIRE(manager.getAddress() == "Narrow Street 7");
        REQUIRE(manager.getEmail() == "jack@librarymail.com");
        REQUIRE(manager.getSalary() == 5000);
        
        REQUIRE(member1.getMemberID() == "10");
        REQUIRE(member1.getName() == "James");
        REQUIRE(member1.getAddress() == "Home Street");
        REQUIRE(member1.getEmail() == "james@mail.com");
    }

    SECTION("Setters") {
        // Setting up a book vector to push into the member's borrowed books.
        Book testBook = Book(15, "testing", "Author", "Anderson");
        std::vector<Book> testBooks;
        testBooks.push_back(testBook);

        manager.setStaffID(15);
        manager.setName("Mooman");
        manager.setAddress("Broad Street");
        manager.setEmail("jack@testMail.com");
        manager.setSalary(10000);

        member1.setName("NewJames");
        member1.setAddress("Other Street");
        member1.setEmail("james@NewMail.com");
        
        // Make sure member's borrowed books are empty upon instantiation.
        REQUIRE((int) member1.getBooksBorrowed().size() == 0);
        member1.setBooksBorrowed(testBooks);

        REQUIRE(manager.getName() == "Mooman");
        REQUIRE(manager.getAddress() == "Broad Street");
        REQUIRE(manager.getEmail() == "jack@testMail.com");
        REQUIRE(manager.getSalary() == 10000);

        REQUIRE(member1.getName() == "NewJames");
        REQUIRE(member1.getAddress() == "Other Street");
        REQUIRE(member1.getEmail() == "james@NewMail.com");

        // Member books vector must reflect number of books they have.
        REQUIRE((int) member1.getBooksBorrowed().size() == 1);
    }
}

TEST_CASE("Book Management", "[librarian]") {

    SECTION("Borrowing Books") {
        std::cout << "Enter the data accurately for this test. Make careful note of instructions." << std::endl;
        std::cout << "Enter the numbers 10 10 10 when dates are requested.\n" << std::endl;

        Librarian manager = Librarian(10, "Jack", "Narrow Street 7", "jack@librarymail.com", 5000);
        Member member2 = Member(15, "Jane", "Some Address", "another@mail.com");

        // Add a member.
        manager.addMember();

        // Make sure the member is added.
        REQUIRE((int)manager.getMembers().size() == 1);

        // Issue an actual book to a member.
        manager.issueBook(std::stoi(manager.getMembers()[0].getMemberID()), 10);

        // Ensure the member got the book and that the book is correct and that adding a due date works.
        REQUIRE((int) manager.getMembers()[0].getBooksBorrowed().size() == 1);
        REQUIRE(manager.getMembers()[0].getBooksBorrowed()[0].getBookName() == "Children of Blood and Bone");
        REQUIRE(manager.getMembers()[0].getBooksBorrowed()[0].getDueDate().getYear() != 0);

        // Ensure that if the book is borrowed, it can't be issued again.
        std::cout << "\nTesting that members can't have more than one book..." << std::endl;
        manager.issueBook(std::stoi(member2.getMemberID()), 10);
        REQUIRE((int) member2.getBooksBorrowed().size() == 0);

        std::cout << "Correct output. Proceeding." << std::endl;
    }
    
    SECTION("Retruning Books") {
        std::cout << "\nEnter the data accurately for this test. Make careful note of instructions." << std::endl;
        std::cout << "Enter the numbers 10 10 10 when dates are requested.\n" << std::endl;

        Librarian manager = Librarian(10, "Jack", "Narrow Street 7", "jack@librarymail.com", 5000);

        std::cout << "Enter new member details for testing borrowing" << std::endl;
        manager.addMember();

        // Issue an actual book to the member.
        manager.issueBook(std::stoi(manager.getMembers()[0].getMemberID()), 10);

        // Return a book and make sure it leaves the member's collection.
        manager.returnBook(std::stoi(manager.getMembers()[0].getMemberID()), 10);
        REQUIRE((int) manager.getMembers()[0].getBooksBorrowed().size() == 0);
    }

    SECTION("Date ADT calculations", "[date]") {
        
        // Diff has to be 0 as book was returnd early.
        int diff1 = getDiffInDates(Date(10, 10, 2010), Date(20, 10, 2010));
        REQUIRE(diff1 == 0);

        int diff2 = getDiffInDates(Date(22, 10, 2010), Date(20, 10, 2010));
        REQUIRE(diff2 == 2);

        int diff3 = getDiffInDates(Date(10, 11, 2010), Date(10, 10, 2010));
        REQUIRE(diff3 == 30);

        int diff4 = getDiffInDates(Date(22, 10, 2011), Date(20, 10, 2010));
        REQUIRE(diff4 == 367);
    }
}