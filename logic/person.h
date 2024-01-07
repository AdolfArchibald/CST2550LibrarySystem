#ifndef _PERSON_H_
#define _PERSON_H_

#include <string>
#include <vector>
#include "book.h"

class Person {

    private:
        std::string name;
        std::string address;
        std::string email;

    public:
        Person(std::string name, std::string address, std::string email);
        virtual ~Person();

        std::string getName();
        std::string getAddress();
        std::string getEmail();

        void setName(std::string name);
        void setAddress(std::string address);
        void setEmail(std::string email);
};

class Member : public Person {

    private:
        int memberId;
        std::vector<Book> booksLoaned;

    public:
        Member(int memberId, std::string name, std::string address, std::string email);

        std::string getMember();
        std::vector<Book> getBooksBorrowed();
        
        void setBooksBorrowed(const Book& book);
};

class Librarian : public Person {

    private:
        int staffId;
        int salary;

    public:
        Librarian(int staffId, std::string name, std::string address, std::string email, std::string salary);

        void addMember();
        void issueBook(int memberID, int bookID);
        void returnBook(int memberID, int bookID);
        void displayBorrowedBooks(int memberID);
        void calcFine(int memberID);

        int getstaffID();
        int getSalary();

        void setStaffID(int staffID);
        void setSalary(int salary);
};

#endif