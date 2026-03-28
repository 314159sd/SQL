#include <usr.h>

void LIB::Usr::info()
{
    LIB::Library::info();
}
void LIB::Usr::displayMenu()
{
    std::cout << "\n图书管理系统菜单" << std::endl;
    std::cout << "1. 查看图书列表" << std::endl;
    std::cout << "2. 添加图书" << std::endl;
    std::cout << "3. 修改图书信息" << std::endl;
    std::cout << "4. 删除图书" << std::endl;
    std::cout << "5. 查找图书" << std::endl;
    std::cout << "6. 查看订阅者信息" << std::endl;
    std::cout << "7. 查看借阅记录" << std::endl;
    std::cout << "8. 退出系统" << std::endl;
    std::cout << "请选择操作: ";
}

void LIB::Usr::viewBooks()
{
    // LIB::Usr lib = *this;
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

void LIB::Usr::addBook()
{
    try
    {
        std::string title, author, isbn, publisher, category;
        int publishyear, totalcopies, availablecopies;

        std::cout << "\n添加图书" << std::endl;
        std::cout << "请输入图书标题: ";
        std::cin.ignore();
        std::getline(std::cin, title);
        std::cout << "请输入作者: ";
        std::getline(std::cin, author);
        std::cout << "请输入ISBN: ";
        std::getline(std::cin, isbn);
        std::cout << "请输入出版社: ";
        std::getline(std::cin, publisher);
        std::cout << "请输入出版年份: ";
        std::cin >> publishyear;
        std::cout << "请输入分类: ";
        std::cin.ignore();
        std::getline(std::cin, category);
        std::cout << "请输入总库存: ";
        std::cin >> totalcopies;
        availablecopies = totalcopies;

        sql::PreparedStatement *pstmt = this->conn->prepareStatement(
            "INSERT INTO books (title, author, isbn, publisher, publishyear, category, totalcopies, availablecopies) "
            "VALUES (?, ?, ?, ?, ?, ?, ?, ?)");

        pstmt->setString(1, title);
        pstmt->setString(2, author);
        pstmt->setString(3, isbn);
        pstmt->setString(4, publisher);
        pstmt->setInt(5, publishyear);
        pstmt->setString(6, category);
        pstmt->setInt(7, totalcopies);
        pstmt->setInt(8, availablecopies);

        int rows = pstmt->executeUpdate();
        if (rows > 0)
        {
            std::cout << "图书添加成功！" << std::endl;
        }
        else
        {
            std::cout << "图书添加失败！" << std::endl;
        }

        delete pstmt;
    }
    catch (sql::SQLException &e)
    {
        std::cout << "添加图书失败: " << e.what() << std::endl;
    }
}

void LIB::Usr::updateBook()
{
    try
    {
        int bookid;
        std::cout << "\n修改图书信息" << std::endl;
        std::cout << "请输入要修改的图书ID: ";
        std::cin >> bookid;

        // 检查图书是否存在
        this->state = this->conn->createStatement();
        this->result = this->state->executeQuery("SELECT * FROM books WHERE bookid = " + std::to_string(bookid));

        if (!this->result->next())
        {
            std::cout << "图书不存在！" << std::endl;
            delete this->result;
            delete this->state;
            return;
        }

        delete this->result;
        delete this->state;

        std::string title, author, isbn, publisher, category;
        int publishyear, totalcopies, availablecopies;

        std::cout << "请输入新的图书标题: ";
        std::cin.ignore();
        std::getline(std::cin, title);
        std::cout << "请输入新的作者: ";
        std::getline(std::cin, author);
        std::cout << "请输入新的ISBN: ";
        std::getline(std::cin, isbn);
        std::cout << "请输入新的出版社: ";
        std::getline(std::cin, publisher);
        std::cout << "请输入新的出版年份: ";
        std::cin >> publishyear;
        std::cout << "请输入新的分类: ";
        std::cin.ignore();
        std::getline(std::cin, category);
        std::cout << "请输入新的总库存: ";
        std::cin >> totalcopies;
        std::cout << "请输入新的可借数量: ";
        std::cin >> availablecopies;

        sql::PreparedStatement *pstmt = this->conn->prepareStatement(
            "UPDATE books SET title = ?, author = ?, isbn = ?, publisher = ?, publishyear = ?, category = ?, totalcopies = ?, availablecopies = ? WHERE bookid = ?");

        pstmt->setString(1, title);
        pstmt->setString(2, author);
        pstmt->setString(3, isbn);
        pstmt->setString(4, publisher);
        pstmt->setInt(5, publishyear);
        pstmt->setString(6, category);
        pstmt->setInt(7, totalcopies);
        pstmt->setInt(8, availablecopies);
        pstmt->setInt(9, bookid);

        int rows = pstmt->executeUpdate();
        if (rows > 0)
        {
            std::cout << "图书信息修改成功！" << std::endl;
        }
        else
        {
            std::cout << "图书信息修改失败！" << std::endl;
        }

        delete pstmt;
    }
    catch (sql::SQLException &e)
    {
        std::cout << "修改图书失败: " << e.what() << std::endl;
    }
}

void LIB::Usr::deleteBook()
{
    try
    {
        int bookid;
        std::cout << "\n删除图书" << std::endl;
        std::cout << "请输入要删除的图书ID: ";
        std::cin >> bookid;

        sql::PreparedStatement *pstmt = this->conn->prepareStatement(
            "DELETE FROM books WHERE bookid = ?");

        pstmt->setInt(1, bookid);
        int rows = pstmt->executeUpdate();

        if (rows > 0)
        {
            std::cout << "图书删除成功！" << std::endl;
        }
        else
        {
            std::cout << "图书不存在或删除失败！" << std::endl;
        }

        delete pstmt;
    }
    catch (sql::SQLException &e)
    {
        std::cout << "删除图书失败: " << e.what() << std::endl;
    }
}

void LIB::Usr::searchBook()
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

void LIB::Usr::viewSubscriberInfo()
{
    try
    {
        this->result = this->state->executeQuery("SELECT * FROM readers");

        std::cout << "\n读者信息列表:" << std::endl;
        std::cout << "ID\t姓名\t联系电话\t邮箱\t\t\t注册时间" << std::endl;
        std::cout << "--------------------------------------------------------------------------------------------------------" << std::endl;

        while (this->result->next())
        {
            std::cout << this->result->getInt("readerid") << "\t"
                      << this->result->getString("name") << "\t"
                      << this->result->getString("phone") << "\t"
                      << this->result->getString("email") << "\t"
                      << this->result->getString("registerdate") << std::endl;
        }
    }
    catch (sql::SQLException &e)
    {
        std::cout << "查看订阅者信息失败: " << e.what() << std::endl;
    }
}

void LIB::Usr::viewBorrowRecords()
{
    try
    {
        this->result = this->state->executeQuery(
            "SELECT b.borrowid, b.bookid, bo.title, b.readerid, r.name, b.borrowdate, b.duedate, b.returndate, b.status "
            "FROM borrows b "
            "JOIN books bo ON b.bookid = bo.bookid "
            "JOIN readers r ON b.readerid = r.readerid");

        std::cout << "\n借阅记录列表:" << std::endl;
        std::cout << "借阅ID\t图书ID\t图书标题\t读者ID\t读者姓名\t借阅时间\t\t应还日期\t\t实际归还时间\t\t状态" << std::endl;
        std::cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;

        bool found = false;
        while (this->result->next())
        {
            found = true;
            std::cout << this->result->getInt("borrowid") << "\t"
                      << this->result->getInt("bookid") << "\t"
                      << this->result->getString("title") << "\t"
                      << this->result->getInt("readerid") << "\t"
                      << this->result->getString("name") << "\t"
                      << this->result->getString("borrowdate") << "\t"
                      << this->result->getString("duedate") << "\t"
                      << (this->result->isNull("returndate") ? "未归还" : this->result->getString("returndate")) << "\t"
                      << this->result->getString("status") << std::endl;
        }

        if (!found)
        {
            std::cout << "暂无借阅记录！" << std::endl;
        }
    }
    catch (sql::SQLException &e)
    {
        std::cout << "查看借阅记录失败: " << e.what() << std::endl;
    }
}
