#include "TaskManager.h"
using namespace std;
#include <algorithm>

TaskManager::TaskManager() : nextProjectId(1), nextUserId(1), nextNotifId(1) {}

TaskManager& TaskManager::getInstance() {
    static TaskManager instance;
    return instance;
}

User* TaskManager::createUser(const std::string& username,
                               const std::string& email, Role role) {
    users.push_back(std::make_unique<User>(nextUserId++, username, email, role));
    return users.back().get();
}

User* TaskManager::findUser(int id) const {
    for (const auto& u : users)
        if (u->getId() == id) return u.get();
    return nullptr;
}

User* TaskManager::findUserByName(const std::string& name) const {
    for (const auto& u : users)
        if (u->getUsername() == name) return u.get();
    return nullptr;
}

bool TaskManager::deleteUser(int id) {
    auto it = std::remove_if(users.begin(), users.end(),
        [id](const std::unique_ptr<User>& u){ return u->getId() == id; });
    if (it == users.end()) return false;
    users.erase(it, users.end());
    return true;
}

const std::vector<std::unique_ptr<User>>& TaskManager::getUsers() const { return users; }

Project* TaskManager::createProject(const std::string& title, const std::string& description) {
    projects.push_back(std::make_unique<Project>(nextProjectId++, title, description));
    return projects.back().get();
}

Project* TaskManager::findProject(int id) const {
    for (const auto& p : projects)
        if (p->getId() == id) return p.get();
    return nullptr;
}

bool TaskManager::deleteProject(int id) {
    auto it = std::remove_if(projects.begin(), projects.end(),
        [id](const std::unique_ptr<Project>& p){ return p->getId() == id; });
    if (it == projects.end()) return false;
    projects.erase(it, projects.end());
    return true;
}

const std::vector<std::unique_ptr<Project>>& TaskManager::getProjects() const {
    return projects;
}

void TaskManager::generateDeadlineNotifications(const std::string& today) {
    for (const auto& p : projects) {
        auto newNotifs = p->checkDeadlines(today, nextNotifId);
        for (auto& n : newNotifs) {
            nextNotifId++;
            notifications.push_back(n);
        }
    }
}

const std::vector<Notification>& TaskManager::getNotifications() const {
    return notifications;
}

void TaskManager::markNotificationRead(int id) {
    for (auto& n : notifications)
        if (n.getId() == id) { n.markAsRead(); return; }
}
