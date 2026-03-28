
#include "browser.h"

void LIB::Browser::displayMenu()
{
    std::cout << "\n图书管理系统菜单" << std::endl;
    std::cout << "1. 查看图书列表" << std::endl;
    std::cout << "2. 查找图书" << std::endl;
    std::cout << "3. 订阅图书" << std::endl;
    std::cout << "4. 归还图书" << std::endl;
    std::cout << "5. 填写读者信息" << std::endl;
    std::cout << "6. 退出系统" << std::endl;
    std::cout << "请选择操作: ";
}
void LIB::Browser::viewBooks()
{
    try
    {
        this->state = this->conn->createStatement();
        this->result = this->state->executeQuery("SELECT * FROM books");

        std::cout << "\n图书列表:" << std::endl;
        std::cout << "ID\t标题\t作者\tISBN\t\t出版社\t\t年份\t分类\t总库存\t可借数量" << std::endl;
        std::cout << "--------------------------------------------------------------------------------------------------------" << std::endl;

        while (this->result->next())
        {
            std::cout << this->result->getInt("bookid") << "\t"
                      << this->result->getString("title") << "\t"
                      << this->result->getString("author") << "\t"
                      << this->result->getString("isbn") << "\t"
                      << this->result->getString("publisher") << "\t"
                      << this->result->getInt("publishyear") << "\t"
                      << this->result->getString("category") << "\t"
                      << this->result->getInt("totalcopies") << "\t"
                      << this->result->getInt("availablecopies") << std::endl;
        }

        delete this->result;
        delete this->state;
    }
    catch (sql::SQLException &e)
    {
        std::cout << "查询图书失败: " << e.what() << std::endl;
    }
}

void LIB::Browser::searchBook()
{
    try
    {
        int searchType;
        std::cout << "\n查找图书" << std::endl;
        std::cout << "1. 按标题查找" << std::endl;
        std::cout << "2. 按作者查找" << std::endl;
        std::cout << "3. 按ISBN查找" << std::endl;
        std::cout << "请选择查找方式: ";
        std::cin >> searchType;

        std::cin.ignore();
        std::string keyword;
        std::string query;

        switch (searchType)
        {
        case 1:
            std::cout << "请输入图书标题: ";
            std::getline(std::cin, keyword);
            query = "SELECT * FROM books WHERE title LIKE '%" + keyword + "%'";
            break;
        case 2:
            std::cout << "请输入作者姓名: ";
            std::getline(std::cin, keyword);
            query = "SELECT * FROM books WHERE author LIKE '%" + keyword + "%'";
            break;
        case 3:
            std::cout << "请输入ISBN: ";
            std::getline(std::cin, keyword);
            query = "SELECT * FROM books WHERE isbn = '" + keyword + "'";
            break;
        default:
            std::cout << "无效的选择！" << std::endl;
            return;
        }

        this->state = this->conn->createStatement();
        this->result = this->state->executeQuery(query);

        std::cout << "\n查找结果:" << std::endl;
        std::cout << "ID\t标题\t\t\t作者\t\tISBN\t\t出版社\t\t年份\t分类\t总库存\t可借数量" << std::endl;
        std::cout << "--------------------------------------------------------------------------------------------------------" << std::endl;

        bool found = false;
        while (this->result->next())
        {
            found = true;
            std::cout << this->result->getInt("bookid") << "\t"
                      << this->result->getString("title") << "\t"
                      << this->result->getString("author") << "\t"
                      << this->result->getString("isbn") << "\t"
                      << this->result->getString("publisher") << "\t"
                      << this->result->getInt("publishyear") << "\t"
                      << this->result->getString("category") << "\t"
                      << this->result->getInt("totalcopies") << "\t"
                      << this->result->getInt("availablecopies") << std::endl;
        }

        if (!found)
        {
            std::cout << "未找到匹配的图书！" << std::endl;
        }

        delete this->result;
        delete this->state;
    }
    catch (sql::SQLException &e)
    {
        std::cout << "查找图书失败: " << e.what() << std::endl;
    }
}

void LIB::Browser::browser_info()
{
    try
    {
        std::string name, phone, email;
        std::cout << "\n填写读者信息" << std::endl;
        std::cout << "请输入姓名: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        std::cout << "请输入联系电话: ";
        std::getline(std::cin, phone);
        std::cout << "请输入邮箱: ";
        std::getline(std::cin, email);

        this->result = this->state->executeQuery("SELECT * FROM readers WHERE email = '" + email + "'");

        if (this->result->next())
        {
            std::cout << "该邮箱已注册！" << std::endl;
            return;
        }

        // 添加读者信息
        sql::PreparedStatement *pstmt = this->conn->prepareStatement(
            "INSERT INTO readers (name, phone, email) VALUES (?, ?, ?)");

        pstmt->setString(1, name);
        pstmt->setString(2, phone);
        pstmt->setString(3, email);

        int rows = pstmt->executeUpdate();

        if (rows > 0)
        {
            this->result = this->state->executeQuery("SELECT LAST_INSERT_ID() as readerid");
            if (this->result->next())
            {
                this->currentReaderId = this->result->getInt("readerid");
                std::cout << "读者信息添加成功！读者ID: " << this->currentReaderId << std::endl;
            }
        }
        else
        {
            std::cout << "读者信息添加失败！" << std::endl;
        }

        delete pstmt;
    }
    catch (sql::SQLException &e)
    {
        std::cout << "添加读者信息失败: " << e.what() << std::endl;
    }
}

// void LIB::Browser::viewReaderInfo()
// {
//     try
//     {
//         if (this->currentReaderId == 0)
//         {
//             std::cout << "\n请先填写读者信息！" << std::endl;
//             return;
//         }
//         this->result = this->state->executeQuery("SELECT * FROM readers WHERE readerid = " + std::to_string(this->currentReaderId));

//         if (this->result->next())
//         {
//             std::cout << "\n读者信息:" << std::endl;
//             std::cout << "读者ID: " << this->result->getInt("readerid") << std::endl;
//             std::cout << "姓名: " << this->result->getString("name") << std::endl;
//             std::cout << "联系电话: " << this->result->getString("phone") << std::endl;
//             std::cout << "邮箱: " << this->result->getString("email") << std::endl;
//             std::cout << "注册时间: " << this->result->getString("registerdate") << std::endl;
//         }
//         else
//         {
//             std::cout << "读者信息不存在！" << std::endl;
//         }
//     }
//     catch (sql::SQLException &e)
//     {
//         std::cout << "查看读者信息失败: " << e.what() << std::endl;
//     }
// }

void LIB::Browser::subscribeBook()
{
    try
    {
        if (this->currentReaderId == 0)
        {
            std::cout << "\n请先填写读者信息！" << std::endl;
            return;
        }

        int bookid;
        std::cout << "\n订阅图书" << std::endl;
        std::cout << "请输入要订阅的图书ID: ";
        std::cin >> bookid;

        // 检查图书是否存在且可借数量大于0
        this->state = this->conn->createStatement();
        this->result = this->state->executeQuery("SELECT availablecopies FROM books WHERE bookid = " + std::to_string(bookid));

        if (!this->result->next())
        {
            std::cout << "图书不存在！" << std::endl;
            delete this->result;
            delete this->state;
            return;
        }

        int available = this->result->getInt("availablecopies");
        if (available <= 0)
        {
            std::cout << "该图书已无可用副本！" << std::endl;
            delete this->result;
            delete this->state;
            return;
        }

        delete this->result;
        delete this->state;

        // 开始事务
        this->conn->setAutoCommit(false);

        try
        {
            // 更新可借数量
            sql::PreparedStatement *pstmt1 = this->conn->prepareStatement(
                "UPDATE books SET availablecopies = availablecopies - 1 WHERE bookid = ?");
            pstmt1->setInt(1, bookid);
            int rows1 = pstmt1->executeUpdate();
            delete pstmt1;

            if (rows1 > 0)
            {
                // 添加借阅记录
                sql::PreparedStatement *pstmt2 = this->conn->prepareStatement(
                    "INSERT INTO borrows (bookid, readerid, duedate) VALUES (?, ?, DATE_ADD(NOW(), INTERVAL 30 DAY))");
                pstmt2->setInt(1, bookid);
                pstmt2->setInt(2, this->currentReaderId);
                int rows2 = pstmt2->executeUpdate();
                delete pstmt2;

                if (rows2 > 0)
                {
                    this->conn->commit();
                    std::cout << "图书订阅成功！" << std::endl;
                }
                else
                {
                    this->conn->rollback();
                    std::cout << "添加借阅记录失败！" << std::endl;
                }
            }
            else
            {
                this->conn->rollback();
                std::cout << "更新图书状态失败！" << std::endl;
            }
        }
        catch (sql::SQLException &e)
        {
            this->conn->rollback();
            throw e;
        }

        this->conn->setAutoCommit(true);
    }
    catch (sql::SQLException &e)
    {
        std::cout << "订阅图书失败: " << e.what() << std::endl;
    }
}

void LIB::Browser::returnBook()
{
    try
    {
        if (this->currentReaderId == 0)
        {
            std::cout << "\n请先填写读者信息！" << std::endl;
            return;
        }

        int bookid;
        std::cout << "\n归还图书" << std::endl;
        std::cout << "请输入要归还的图书ID: ";
        std::cin >> bookid;

        // 检查是否有未归还的借阅记录
        this->state = this->conn->createStatement();
        this->result = this->state->executeQuery(
            "SELECT * FROM borrows WHERE bookid = " + std::to_string(bookid) +
            " AND readerid = " + std::to_string(this->currentReaderId) +
            " AND status = 'borrowed'");

        if (!this->result->next())
        {
            std::cout << "没有找到该图书的借阅记录！" << std::endl;
            delete this->result;
            delete this->state;
            return;
        }

        int borrowid = this->result->getInt("borrowid");
        delete this->result;
        delete this->state;

        // 开始事务
        this->conn->setAutoCommit(false);

        try
        {
            // 更新可借数量
            sql::PreparedStatement *pstmt1 = this->conn->prepareStatement(
                "UPDATE books SET availablecopies = availablecopies + 1 WHERE bookid = ?");
            pstmt1->setInt(1, bookid);
            int rows1 = pstmt1->executeUpdate();
            delete pstmt1;

            if (rows1 > 0)
            {
                // 更新借阅记录
                sql::PreparedStatement *pstmt2 = this->conn->prepareStatement(
                    "UPDATE borrows SET returndate = NOW(), status = 'returned' WHERE borrowid = ?");
                pstmt2->setInt(1, borrowid);
                int rows2 = pstmt2->executeUpdate();
                delete pstmt2;

                if (rows2 > 0)
                {
                    this->conn->commit();
                    std::cout << "图书归还成功！" << std::endl;
                }
                else
                {
                    this->conn->rollback();
                    std::cout << "更新借阅记录失败！" << std::endl;
                }
            }
            else
            {
                this->conn->rollback();
                std::cout << "更新图书状态失败！" << std::endl;
            }
        }
        catch (sql::SQLException &e)
        {
            this->conn->rollback();
            throw e;
        }

        this->conn->setAutoCommit(true);
    }
    catch (sql::SQLException &e)
    {
        std::cout << "归还图书失败: " << e.what() << std::endl;
    }
}
