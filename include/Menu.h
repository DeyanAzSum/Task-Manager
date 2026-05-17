#pragma once
#include "TaskManager.h"
#include <iostream>
#include <string>
#include <limits>

inline int readInt(const std::string& prompt) {
    int v;
    while (true) {
        std::cout << prompt;
        if (std::cin >> v) { std::cin.ignore(); return v; }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  Invalid input. Try again.\n";
    }
}

inline std::string readLine(const std::string& prompt) {
    std::string s;
    std::cout << prompt;
    std::getline(std::cin, s);
    return s;
}

inline Priority readPriority() {
    std::cout << "  Priority (1=LOW, 2=MEDIUM, 3=HIGH): ";
    int c = readInt("");
    if (c == 3) return Priority::HIGH;
    if (c == 2) return Priority::MEDIUM;
    return Priority::LOW;
}

inline Status readStatus() {
    std::cout << "  Status (1=TODO, 2=IN_PROGRESS, 3=DONE): ";
    int c = readInt("");
    if (c == 2) return Status::IN_PROGRESS;
    if (c == 3) return Status::DONE;
    return Status::TODO;
}

void menuUsers() {
    TaskManager& tm = TaskManager::getInstance();
    while (true) {
        std::cout << "\n=== USER MANAGEMENT ===\n"
                  << "1. List users\n2. Create user\n3. Edit user\n"
                  << "4. Delete user\n0. Back\n> ";
        int ch = readInt("");
        if (ch == 0) break;

        if (ch == 1) {
            if (tm.getUsers().empty()) { std::cout << "  No users.\n"; continue; }
            for (const auto& u : tm.getUsers()) u->print();

        } else if (ch == 2) {
            std::string uname = readLine("  Username: ");
            std::string email = readLine("  Email   : ");
            std::cout << "  Role (1=ADMIN, 2=MEMBER): ";
            int r = readInt("");
            Role role = (r == 1) ? Role::ADMIN : Role::MEMBER;
            User* u = tm.createUser(uname, email, role);
            std::cout << "  Created "; u->print();

        } else if (ch == 3) {
            int id = readInt("  User ID: ");
            User* u = tm.findUser(id);
            if (!u) { std::cout << "  Not found.\n"; continue; }
            std::string uname = readLine("  New username (enter to keep): ");
            if (!uname.empty()) u->setUsername(uname);
            std::string email = readLine("  New email (enter to keep)   : ");
            if (!email.empty()) u->setEmail(email);
            std::cout << "  Role (1=ADMIN, 2=MEMBER, 0=keep): ";
            int r = readInt("");
            if (r == 1) u->setRole(Role::ADMIN);
            else if (r == 2) u->setRole(Role::MEMBER);
            std::cout << "  Updated "; u->print();

        } else if (ch == 4) {
            int id = readInt("  User ID: ");
            std::cout << (tm.deleteUser(id) ? "  Deleted.\n" : "  Not found.\n");
        }
    }
}

void menuTasks(Project* proj, User* currentUser) {
    TaskManager& tm = TaskManager::getInstance();
    while (true) {
        std::cout << "\n--- TASKS in [" << proj->getTitle() << "] ---\n"
                  << "1. List tasks\n2. Create task\n3. Edit task\n"
                  << "4. Delete task\n5. Assign task to user\n"
                  << "6. Change task status\n7. View status history\n"
                  << "0. Back\n> ";
        int ch = readInt("");
        if (ch == 0) break;

        if (ch == 1) {
            if (proj->getTasks().empty()) { std::cout << "  No tasks.\n"; continue; }
            for (const auto& t : proj->getTasks()) t->printDetails();

        } else if (ch == 2) {
            std::string title = readLine("  Title      : ");
            std::string desc  = readLine("  Description: ");
            Priority prio     = readPriority();
            std::string due   = readLine("  Due date   : ");
            Task* t = proj->addTask(title, desc, prio, due);
            std::cout << "  Created task #" << t->getId() << "\n";

        } else if (ch == 3) {
            int id = readInt("  Task ID: ");
            Task* t = proj->findTask(id);
            if (!t) { std::cout << "  Not found.\n"; continue; }
            std::string title = readLine("  New title (enter to keep)      : ");
            if (!title.empty()) t->setTitle(title);
            std::string desc = readLine("  New description (enter to keep) : ");
            if (!desc.empty()) t->setDescription(desc);
            std::cout << "  Priority (1=LOW,2=MEDIUM,3=HIGH, 0=keep): ";
            int p = readInt("");
            if (p == 1) t->setPriority(Priority::LOW);
            else if (p == 2) t->setPriority(Priority::MEDIUM);
            else if (p == 3) t->setPriority(Priority::HIGH);
            std::string due = readLine("  New due date (enter to keep)    : ");
            if (!due.empty()) t->setDueDate(due);
            std::cout << "  Updated.\n"; t->printDetails();

        } else if (ch == 4) {
            int id = readInt("  Task ID: ");
            std::cout << (proj->removeTask(id) ? "  Deleted.\n" : "  Not found.\n");

        } else if (ch == 5) {
            int tid = readInt("  Task ID: ");
            Task* t = proj->findTask(tid);
            if (!t) { std::cout << "  Task not found.\n"; continue; }
            int uid = readInt("  User ID to assign (0 = unassign): ");
            if (uid == 0) { t->assign(nullptr); std::cout << "  Unassigned.\n"; continue; }
            User* u = proj->findMember(uid);
            if (!u) { std::cout << "  User is not a member of this project.\n"; continue; }
            t->assign(u);
            std::cout << "  Assigned task #" << tid << " to " << u->getUsername() << "\n";

        } else if (ch == 6) {
            int id = readInt("  Task ID: ");
            Task* t = proj->findTask(id);
            if (!t) { std::cout << "  Not found.\n"; continue; }
            Status s = readStatus();
            t->changeStatus(s, currentUser->getUsername());
            std::cout << "  Status updated to " << statusToString(s) << "\n";

        } else if (ch == 7) {
            int id = readInt("  Task ID: ");
            Task* t = proj->findTask(id);
            if (!t) { std::cout << "  Not found.\n"; continue; }
            std::cout << "  Status history for task #" << id << ":\n";
            t->printHistory();
        }
    }
}

void menuProjects(User* currentUser) {
    TaskManager& tm = TaskManager::getInstance();
    while (true) {
        std::cout << "\n=== PROJECT MANAGEMENT ===\n"
                  << "1. List projects\n2. Create project\n3. Edit project\n"
                  << "4. Delete project\n5. Add member to project\n"
                  << "6. Manage tasks in project\n0. Back\n> ";
        int ch = readInt("");
        if (ch == 0) break;

        if (ch == 1) {
            if (tm.getProjects().empty()) { std::cout << "  No projects.\n"; continue; }
            for (const auto& p : tm.getProjects()) p->printDetails();

        } else if (ch == 2) {
            if (currentUser->getRole() != Role::ADMIN) {
                std::cout << "  Access denied. ADMIN only.\n"; continue;
            }
            std::string title = readLine("  Title      : ");
            std::string desc  = readLine("  Description: ");
            Project* p = tm.createProject(title, desc);
            std::cout << "  Created project #" << p->getId() << "\n";

        } else if (ch == 3) {
            if (currentUser->getRole() != Role::ADMIN) {
                std::cout << "  Access denied. ADMIN only.\n"; continue;
            }
            int id = readInt("  Project ID: ");
            Project* p = tm.findProject(id);
            if (!p) { std::cout << "  Not found.\n"; continue; }
            std::string title = readLine("  New title (enter to keep)      : ");
            if (!title.empty()) p->setTitle(title);
            std::string desc = readLine("  New description (enter to keep) : ");
            if (!desc.empty()) p->setDescription(desc);
            std::cout << "  Updated.\n"; p->printDetails();

        } else if (ch == 4) {
            if (currentUser->getRole() != Role::ADMIN) {
                std::cout << "  Access denied. ADMIN only.\n"; continue;
            }
            int id = readInt("  Project ID: ");
            std::cout << (tm.deleteProject(id) ? "  Deleted.\n" : "  Not found.\n");

        } else if (ch == 5) {
            if (currentUser->getRole() != Role::ADMIN) {
                std::cout << "  Access denied. ADMIN only.\n"; continue;
            }
            int pid = readInt("  Project ID: ");
            Project* p = tm.findProject(pid);
            if (!p) { std::cout << "  Project not found.\n"; continue; }
            int uid = readInt("  User ID to add: ");
            User* u = tm.findUser(uid);
            if (!u) { std::cout << "  User not found.\n"; continue; }
            p->addMember(u);
            std::cout << "  Added " << u->getUsername() << " to project.\n";

        } else if (ch == 6) {
            int id = readInt("  Project ID: ");
            Project* p = tm.findProject(id);
            if (!p) { std::cout << "  Not found.\n"; continue; }
            menuTasks(p, currentUser);
        }
    }
}
