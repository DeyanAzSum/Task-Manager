#pragma once
#include "WorkItem.h"
#include "Task.h"
#include "User.h"
#include "Notification.h"
#include <vector>
#include <memory>
#include <string>

class Project : public WorkItem {
private:
    std::vector<std::unique_ptr<Task>> tasks;
    std::vector<User*> members;
    int nextTaskId;

public:
    explicit Project(int id, const std::string& title, const std::string& description);

    Task* addTask(const std::string& title, const std::string& description, Priority priority, const std::string& dueDate);
    Task* findTask(int id) const;
    bool removeTask(int id);
    const std::vector<std::unique_ptr<Task>>& getTasks() const;

    void addMember(User* user);
    bool removeMember(int userId);
    User* findMember(int userId) const;
    const std::vector<User*>& getMembers() const;

    std::vector<Task*> searchTasks(const std::string& keyword) const;
    std::vector<Task*> filterByStatus(Status s) const;
    std::vector<Task*> filterByPriority(Priority p) const;
    std::vector<Task*> filterByAssignee(int userId) const;

    std::vector<Notification> checkDeadlines(const std::string& today, int nextId) const;

    void printDetails() const override;
};
