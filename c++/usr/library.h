#pragma once

#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <cstring>

namespace LIB
{
    class Library
    {
        std::string ip;
        std::string usr;
        std::string passward;
        std::string pass_enter;

    public:
        Library(std::string ip_m, std::string usr_m, std::string passward_m) ;
        Library() ;

        // Library &operator=(Library &) = delete;
        ~Library() = default;

        void info();
        bool pass();
        virtual void displayMenu() = 0;
        virtual void exitSystem();
        
        

        sql::mysql::MySQL_Driver *driver;
        sql::Connection *conn;
        sql::Statement *state;
        sql::ResultSet *result;
    };

}