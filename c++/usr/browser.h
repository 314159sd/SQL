#pragma once
#include "library.h"

namespace LIB
{
    class Browser : Library
    {
    public:
        Browser(std::string &&ip_m, std::string &&usr_m, std::string &&passward_m) : Library(ip_m, usr_m, passward_m)
        {
            std::cout << "\n----------------------------图书管理系统----------------------------\n"
                      << std::endl;
        };
        ~Browser() = default;

        void displayMenu();
        void viewBooks();
        void searchBook();
        void browser_info();
        // void viewReaderInfo();
        void subscribeBook();
        void returnBook();
        void exitSystem() override
        {
            Library::exitSystem();
        };

        int currentReaderId;
    };
}
