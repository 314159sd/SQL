#pragma once

#include <library.h>

namespace LIB
{
    class Usr : Library
    {

    public:
        Usr(std::string &&ip_m, std::string &&usr_m, std::string &&passward_m) : Library(ip_m, usr_m, passward_m)
        {
            info();
            std::cout << "\n--------------------------图书管理系统（管理员）--------------------------\n"
                      << std::endl;
        };
        ~Usr() = default;

        void info();
        void displayMenu() override;
        void exitSystem()
        {
            Library::exitSystem();
        };
        void viewBooks();
        void addBook();
        void updateBook();
        void deleteBook();
        void searchBook();
        void viewSubscriberInfo();
        void viewBorrowRecords();
    };
}