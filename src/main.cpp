#include "Menu.h"
#include <iostream>

using namespace std;
int main() {
    TaskManager& tm = TaskManager::getInstance();
    tm.createUser("admin", "admin@example.com", Role::ADMIN);

    cout << "========================================\n" << "   Task & Project Manager  v2.0\n" << "========================================\n";

    User* currentUser = nullptr;
    while (!currentUser) {
        string uname = readLine("Login (username): ");
        currentUser = tm.findUserByName(uname);
        if (!currentUser)
            cout << "Not found. Default admin: admin\n";
    }
    cout << "  Welcome, " << currentUser->getUsername()
            << " [" << roleToString(currentUser->getRole()) << "]\n";

    while (true) {
        cout << "\n========== MAIN MENU ==========\n"
                << "1. Users\n2. Projects & Tasks\n"
                << "3. Search & Filter\n4. Notifications\n"
                << "0. Exit\n> ";
        int ch = readInt("");
        if (ch == 0) { cout << "Goodbye.\n"; break; }
        if (ch == 1) menuUsers();
        if (ch == 2) menuProjects(currentUser);
        if (ch == 3) menuSearch(currentUser);
        if (ch == 4) menuNotifications(currentUser);
    }
    return 0;
}
