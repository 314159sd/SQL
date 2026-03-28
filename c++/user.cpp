#include <usr.h>

int main()
{
    try
    {
        LIB::Usr usr{"127.0.0.1", "root", "Sd3.14159"};
        int choice;

        do
        {
            usr.displayMenu();
            std::cin >> choice;

            switch (choice)
            {
            case 1:
                usr.viewBooks();
                break;
            case 2:
                usr.addBook();
                break;
            case 3:
                usr.updateBook();
                break;
            case 4:
                usr.deleteBook();
                break;
            case 5:
                usr.searchBook();
                break;
            case 6:
                usr.viewSubscriberInfo();
                break;
            case 7:
                usr.viewBorrowRecords();
                break;
            case 8:
                usr.exitSystem();
                break;
            default:
                std::cout << "无效的选择，请重新输入！" << std::endl;
                break;
            }
        } while (choice != 8);
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