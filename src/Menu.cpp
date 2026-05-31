#include "Menu.h"
#include "Report.h"
#include <iostream>
#include <limits>
using namespace std;

int readInt(const string& prompt) {
    int v;
    while (true) {
        cout << prompt;
        if (cin >> v) { cin.ignore(); return v; }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Invalid input. Try again.\n";
    }
}

string readLine(const string& prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

Priority readPriority() {
    int c = readInt("Priority (1=LOW, 2=MEDIUM, 3=HIGH): ");
    return priorityFromInt(c);
}

Status readStatus() {
    int c = readInt("Status (1=TODO, 2=IN_PROGRESS, 3=DONE): ");
    return statusFromInt(c);
}

void menuUsers() {
    TaskManager& tm = TaskManager::getInstance();
    while (true) {
        cout << "\n=== USER MANAGEMENT ===\n" << "1. List\n2. Create\n3. Edit\n4. Delete\n0. Back\n> ";
        int ch = readInt("");
        if (ch == 0) break;

        if (ch == 1) {
            if (tm.getUsers().empty()) { cout << "No users.\n"; continue; }
            for (const auto& u : tm.getUsers()) u->print();

        } else if (ch == 2) {
            string uname = readLine("Username: ");
            string email = readLine("Email: ");
            int r = readInt("  Role (1=ADMIN, 2=MEMBER): ");
            Role role = (r == 1) ? Role::ADMIN : Role::MEMBER;
            User* u = tm.createUser(uname, email, role);
            cout << "Created "; u->print();

        } else if (ch == 3) {
            int id = readInt("User ID: ");
            User* u = tm.findUser(id);
            if (!u) { cout << "Not found.\n"; continue; }
            string uname = readLine("New username (enter=keep): ");
            if (!uname.empty()) u->setUsername(uname);
            string email = readLine("New email (enter=keep): ");
            if (!email.empty()) u->setEmail(email);
            int r = readInt("  Role (1=ADMIN, 2=MEMBER, 0=keep): ");
            if (r == 1) u->setRole(Role::ADMIN);
            else if (r == 2) u->setRole(Role::MEMBER);
            cout << "Updated ";
            u->print();

        } else if (ch == 4) {
            int id = readInt("User ID: ");
            cout << (tm.deleteUser(id) ? "Deleted.\n" : "Not found.\n");
        }
    }
}

void menuTasks(Project* proj, User* currentUser) {
    while (true) {
        cout << "\n--- TASKS in [" << proj->getTitle() << "] ---\n"
                  << "1. List\n2. Create\n3. Edit\n4. Delete\n"
                  << "5. Assign to user\n6. Change status\n7. Status history\n"
                  << "8. Comments\n0. Back\n> ";
        int ch = readInt("");
        if (ch == 0) break;

        if (ch == 1) {
            if (proj->getTasks().empty()) { cout << "  No tasks.\n"; continue; }
            for (const auto& t : proj->getTasks()) t->printDetails();

        } else if (ch == 2) {
            string title = readLine("Title: ");
            string desc = readLine("Description: ");
            Priority prio = readPriority();
            string due = readLine("  Due (YYYY-MM-DD): ");
            Task* t = proj->addTask(title, desc, prio, due);
            cout << "Created task #" << t->getId() << "\n";

        } else if (ch == 3) {
            int id = readInt("  Task ID: ");
            Task* t = proj->findTask(id);
            if (!t) { cout << "  Not found.\n"; continue; }
            string title = readLine("  New title (enter=keep)      : ");
            if (!title.empty()) t->setTitle(title);
            string desc = readLine("  New description (enter=keep) : ");
            if (!desc.empty()) t->setDescription(desc);
            int p = readInt("Priority (1=LOW,2=MEDIUM,3=HIGH, 0=keep): ");
            if (p >= 1 && p <= 3) t->setPriority(priorityFromInt(p));
            string due = readLine("  New due date (enter=keep)    : ");
            if (!due.empty()) t->setDueDate(due);
            cout << "Updated.\n"; t->printDetails();

        } else if (ch == 4) {
            int id = readInt("  Task ID: ");
            cout << (proj->removeTask(id) ? "  Deleted.\n" : "  Not found.\n");

        } else if (ch == 5) {
            int tid = readInt("  Task ID: ");
            Task* t = proj->findTask(tid);
            if (!t) { cout << "Task not found.\n"; continue; }
            int uid = readInt("User ID (0=unassign): ");
            if (uid == 0) { t->assign(nullptr); cout << "Unassigned.\n"; continue; }
            User* u = proj->findMember(uid);
            if (!u) { cout << "User is not a project member.\n"; continue; }
            t->assign(u);
            cout << "Assigned to " << u->getUsername() << "\n";

        } else if (ch == 6) {
            int id = readInt("Task ID: ");
            Task* t = proj->findTask(id);
            if (!t) { cout << "Not found.\n"; continue; }
            Status s = readStatus();
            t->changeStatus(s, currentUser->getUsername());
            cout << "  Status -> " << statusToString(s) << "\n";

        } else if (ch == 7) {
            int id = readInt("Task ID: ");
            Task* t = proj->findTask(id);
            if (!t) { cout << "Not found.\n"; continue; }
            cout << "History for task #" << id << ":\n";
            t->printHistory();

        } else if (ch == 8) {
            int id = readInt("  Task ID: ");
            Task* t = proj->findTask(id);
            if (!t) { cout << "  Not found.\n"; continue; }
            while (true) {
                cout << "\n  -- Comments: " << t->getTitle() << " --\n" << "  1. List  2. Add  3. Delete  0. Back\n  > ";
                int cc = readInt("");
                if (cc == 0) break;
                if (cc == 1) {
                    t->printComments();
                } else if (cc == 2) {
                    string content = readLine("Comment: ");
                    string ts = readLine("Date (YYYY-MM-DD): ");
                    t->addComment(content, currentUser->getUsername(), ts);
                    cout << "Comment added.\n";
                } else if (cc == 3) {
                    int cid = readInt("Comment ID: ");
                    cout << (t->deleteComment(cid) ? "Deleted.\n" : "Not found.\n");
                }
            }
        }
    }
}

void menuProjects(User* currentUser) {
    TaskManager& tm = TaskManager::getInstance();
    while (true) {
        std::cout << "\n=== PROJECTS ===\n"
                  << "1. List\n2. Create\n3. Edit\n4. Delete\n"
                  << "5. Add member\n6. Manage tasks\n7. Generate report\n"
                  << "0. Back\n> ";
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
            std::string title = readLine("  New title (enter=keep)      : ");
            if (!title.empty()) p->setTitle(title);
            std::string desc  = readLine("  New description (enter=keep) : ");
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
            int uid = readInt("  User ID: ");
            User* u = tm.findUser(uid);
            if (!u) { std::cout << "  User not found.\n"; continue; }
            p->addMember(u);
            std::cout << "  Added " << u->getUsername() << " to project.\n";

        } else if (ch == 6) {
            int id = readInt("  Project ID: ");
            Project* p = tm.findProject(id);
            if (!p) { std::cout << "  Not found.\n"; continue; }
            menuTasks(p, currentUser);

        } else if (ch == 7) {
            int id = readInt("  Project ID: ");
            Project* p = tm.findProject(id);
            if (!p) { std::cout << "  Not found.\n"; continue; }
            Report::generate(*p).print();
        }
    }
}

void menuNotifications(User* ) {
    TaskManager& tm = TaskManager::getInstance();
    while (true) {
        std::cout << "\n=== NOTIFICATIONS ===\n"
                  << "1. List all\n2. Check deadlines (enter today's date)\n"
                  << "3. Mark as read\n0. Back\n> ";
        int ch = readInt("");
        if (ch == 0) break;

        if (ch == 1) {
            if (tm.getNotifications().empty()) { std::cout << "  No notifications.\n"; continue; }
            for (const auto& n : tm.getNotifications()) n.print();

        } else if (ch == 2) {
            std::string today = readLine("  Today's date (YYYY-MM-DD): ");
            tm.generateDeadlineNotifications(today);
            std::cout << "  Done. Check notification list.\n";

        } else if (ch == 3) {
            int id = readInt("  Notification ID: ");
            tm.markNotificationRead(id);
            std::cout << "  Marked as read.\n";
        }
    }
}

void menuSearch(User*) {
    TaskManager& tm = TaskManager::getInstance();
    while (true) {
        cout << "\n=== SEARCH & FILTER ===\n"
            << "1. Search by keyword (all projects)\n"
            << "2. Filter by status\n"
            << "3. Filter by priority\n"
            << "4. Filter by assignee\n"
            << "0. Back\n> ";
        int ch = readInt("");
        if (ch == 0) break;

        if (ch == 1) {
            string kw = readLine("  Keyword: ");
            bool found = false;
            for (const auto& p : tm.getProjects()) {
                auto results = p->searchTasks(kw);
                if (!results.empty()) {
                    std::cout << "\n  Project: " << p->getTitle() << "\n";
                    for (auto* t : results) t->printDetails();
                    found = true;
                }
            }
            if (!found) std::cout << "  No results.\n";

        } else if (ch == 2) {
            Status s = readStatus();
            bool found = false;
            for (const auto& p : tm.getProjects()) {
                auto results = p->filterByStatus(s);
                if (!results.empty()) {
                    std::cout << "\n  Project: " << p->getTitle() << "\n";
                    for (auto* t : results) t->printDetails();
                    found = true;
                }
            }
            if (!found) std::cout << "  No results.\n";

        } else if (ch == 3) {
            Priority pr = readPriority();
            bool found = false;
            for (const auto& p : tm.getProjects()) {
                auto results = p->filterByPriority(pr);
                if (!results.empty()) {
                    std::cout << "\n  Project: " << p->getTitle() << "\n";
                    for (auto* t : results) t->printDetails();
                    found = true;
                }
            }
            if (!found) std::cout << "  No results.\n";

        } else if (ch == 4) {
            int uid = readInt("  User ID: ");
            bool found = false;
            for (const auto& p : tm.getProjects()) {
                auto results = p->filterByAssignee(uid);
                if (!results.empty()) {
                    std::cout << "\n  Project: " << p->getTitle() << "\n";
                    for (auto* t : results) t->printDetails();
                    found = true;
                }
            }
            if (!found) std::cout << "  No results.\n";
        }
    }
}
