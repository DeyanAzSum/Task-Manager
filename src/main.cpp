#include "Menu.h"
#include <iostream>

int main() {
    TaskManager& tm = TaskManager::getInstance();

    tm.createUser("admin", "admin@example.com", Role::ADMIN);

    std::cout << "========================================\n"
              << "   Task & Project Manager  v1.0\n"
              << "========================================\n";

    User* currentUser = nullptr;
    while (!currentUser) {
        std::string uname = readLine("Login as (username): ");
        currentUser = tm.findUserByName(uname);
        if (!currentUser)
            std::cout << "  User not found. (Default admin username: admin)\n";
    }
    std::cout << "  Welcome, " << currentUser->getUsername()
              << " [" << roleToString(currentUser->getRole()) << "]\n";

    while (true) {
        std::cout << "\nMAIN MENU\n"
                  << "1. Users\n2. Projects & Tasks\n0. Exit\n> ";
        int ch = readInt("");
        if (ch == 0) { std::cout << "Goodbye.\n"; break; }
        if (ch == 1) menuUsers();
        if (ch == 2) menuProjects(currentUser);
    }

    return 0;
}
