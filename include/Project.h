#pragma once
#include "WorkItem.h"
#include "Task.h"
#include "User.h"
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

class Project : public WorkItem {
private:
    std::vector<std::unique_ptr<Task>> tasks;
    std::vector<User*> members;
    int nextTaskId;

public:
    explicit Project(int id, const std::string& title, const std::string& description)
        : WorkItem(id, title, description), nextTaskId(1) {}

    Task* addTask(const std::string& title, const std::string& description,
                  Priority priority, const std::string& dueDate) {
        tasks.push_back(std::make_unique<Task>(nextTaskId++, title, description, priority, dueDate));
        return tasks.back().get();
    }

    Task* findTask(int id) const {
        for (const auto& t : tasks)
            if (t->getId() == id) return t.get();
        return nullptr;
    }

    bool removeTask(int id) {
        auto it = std::remove_if(tasks.begin(), tasks.end(),
            [id](const std::unique_ptr<Task>& t){ return t->getId() == id; });
        if (it == tasks.end()) return false;
        tasks.erase(it, tasks.end());
        return true;
    }

    const std::vector<std::unique_ptr<Task>>& getTasks() const { return tasks; }

    void addMember(User* user) {
        for (auto* m : members)
            if (m->getId() == user->getId()) return;
        members.push_back(user);
    }

    bool removeMember(int userId) {
        auto it = std::remove_if(members.begin(), members.end(),
            [userId](User* u){ return u->getId() == userId; });
        if (it == members.end()) return false;
        members.erase(it, members.end());
        return true;
    }

    User* findMember(int userId) const {
        for (auto* m : members)
            if (m->getId() == userId) return m;
        return nullptr;
    }

    const std::vector<User*>& getMembers() const { return members; }

    void printDetails() const override {
        std::cout << "[Project #" << id << "] " << title << "\n"
                  << "  Desc   : " << description << "\n"
                  << "  Tasks  : " << tasks.size() << "\n"
                  << "  Members: " << members.size() << "\n";
    }
};
