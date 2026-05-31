#pragma once
#include "Project.h"
#include "Notification.h"
#include <vector>
#include <memory>
#include <string>

class TaskManager {
private:
    std::vector<std::unique_ptr<Project>> projects;
    std::vector<std::unique_ptr<User>> users;
    std::vector<Notification> notifications;
    int nextProjectId;
    int nextUserId;
    int nextNotifId;

    TaskManager();

public:
    static TaskManager& getInstance();
    TaskManager(const TaskManager&) = delete;
    TaskManager& operator=(const TaskManager&) = delete;

    User* createUser(const std::string& username, const std::string& email, Role role);
    User* findUser(int id) const;
    User* findUserByName(const std::string& name) const;
    bool deleteUser(int id);
    const std::vector<std::unique_ptr<User>>& getUsers() const;

    Project* createProject(const std::string& title, const std::string& description);
    Project* findProject(int id) const;
    bool deleteProject(int id);
    const std::vector<std::unique_ptr<Project>>& getProjects() const;

    void generateDeadlineNotifications(const std::string& today);
    const std::vector<Notification>& getNotifications() const;
    void markNotificationRead(int id);
};
