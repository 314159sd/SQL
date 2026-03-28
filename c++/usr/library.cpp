#include <library.h>

LIB::Library::Library(std::string ip_m, std::string usr_m, std::string passward_m) : ip(ip_m), usr(usr_m), passward(passward_m)
{
    // std::cout << "begin" << std::endl;
    // info();
    ip = "tcp://" + ip + ":3306";
    driver = sql::mysql::get_mysql_driver_instance();

    conn = driver->connect(ip, usr, passward);
    std::cout << "连接完成！" << std::endl;
    conn->setSchema("LIBRARY_SYSTEM");
}
LIB::Library::Library() : Library("localhost", "root", "") {}

void LIB::Library::info()
{
    std::cout << "ip: " << ip << std::endl;
    std::cout << "usr: " << usr << std::endl;
    std::cout << "passward: " << passward << std::endl;
}

bool LIB::Library::pass()
{
    std::cout << "请输入密码： ";
    std::cin >> pass_enter;
    return pass_enter == passward;
}

void LIB::Library::exitSystem()
{
    std::cout << "退出系统..." << std::endl;
}
