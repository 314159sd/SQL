#include <browser.h>

int main()
{
    try
    {
        LIB::Browser customer{"127.0.0.1", "root", "Sd3.14159"};

        int choice;
        do
        {
            customer.displayMenu();
            std::cin >> choice;
            switch (choice)
            {
            case 1:
                customer.viewBooks();
                break;
            case 2:
                customer.searchBook();
                break;
            case 3:
                customer.subscribeBook();
                break;
            case 4:
                customer.returnBook();
                break;
            case 5:
                customer.browser_info();
                break;
            case 6:
                customer.viewReaderInfo();
                break;
            case 7:
                customer.exitSystem();
                break;
            default:
                break;
            }
        } while (choice < 7);
    }
    catch (sql::SQLException &e)
    {
        std::cout << "数据库错误: " << e.what() << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "错误: " << e.what() << std::endl;
    }
    return 0;
}