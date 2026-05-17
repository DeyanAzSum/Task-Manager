#pragma once
#include "Project.h"
#include "User.h"
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

class TaskManager {
private:
    std::vector<std::unique_ptr<Project>> projects;
    std::vector<std::unique_ptr<User>>    users;
    int nextProjectId;
    int nextUserId;

    TaskManager() : nextProjectId(1), nextUserId(1) {}

public:
    static TaskManager& getInstance() {
        static TaskManager instance;
        return instance;
    }
    TaskManager(const TaskManager&)            = delete;
    TaskManager& operator=(const TaskManager&) = delete;

    User* createUser(const std::string& username, const std::string& email, Role role) {
        users.push_back(std::make_unique<User>(nextUserId++, username, email, role));
        return users.back().get();
    }

    User* findUser(int id) const {
        for (const auto& u : users)
            if (u->getId() == id) return u.get();
        return nullptr;
    }

    User* findUserByName(const std::string& name) const {
        for (const auto& u : users)
            if (u->getUsername() == name) return u.get();
        return nullptr;
    }

    bool deleteUser(int id) {
        auto it = std::remove_if(users.begin(), users.end(),
            [id](const std::unique_ptr<User>& u){ return u->getId() == id; });
        if (it == users.end()) return false;
        users.erase(it, users.end());
        return true;
    }

    const std::vector<std::unique_ptr<User>>& getUsers() const { return users; }

    Project* createProject(const std::string& title, const std::string& description) {
        projects.push_back(std::make_unique<Project>(nextProjectId++, title, description));
        return projects.back().get();
    }

    Project* findProject(int id) const {
        for (const auto& p : projects)
            if (p->getId() == id) return p.get();
        return nullptr;
    }

    bool deleteProject(int id) {
        auto it = std::remove_if(projects.begin(), projects.end(),
            [id](const std::unique_ptr<Project>& p){ return p->getId() == id; });
        if (it == projects.end()) return false;
        projects.erase(it, projects.end());
        return true;
    }

    const std::vector<std::unique_ptr<Project>>& getProjects() const { return projects; }
};
