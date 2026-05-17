#pragma once
#include "WorkItem.h"
#include "Enums.h"
#include "User.h"
#include <string>
#include <vector>
#include <iostream>

struct StatusChange {
    Status oldStatus;
    Status newStatus;
    std::string changedBy;

    StatusChange(Status o, Status n, const std::string& by)
        : oldStatus(o), newStatus(n), changedBy(by) {}
};

class Task : public WorkItem {
private:
    Priority priority;
    Status status;
    std::string dueDate;
    User* assignee;
    std::vector<StatusChange> history;

public:
    Task(int id, const std::string& title, const std::string& description,
         Priority priority, const std::string& dueDate)
        : WorkItem(id, title, description),
          priority(priority), status(Status::TODO),
          dueDate(dueDate), assignee(nullptr) {}

    Priority getPriority() const { return priority; }
    Status getStatus()   const { return status; }
    const std::string& getDueDate()  const { return dueDate; }
    User* getAssignee() const { return assignee; }
    const std::vector<StatusChange>& getHistory() const { return history; }

    void setPriority(Priority p) { priority = p; }
    void setDueDate(const std::string& d) { dueDate = d; }

    void assign(User* user) { assignee = user; }

    void changeStatus(Status newStatus, const std::string& changedBy) {
        history.emplace_back(status, newStatus, changedBy);
        status = newStatus;
    }

    void printDetails() const override {
        std::cout << "  [Task #" << id << "] " << title << "\n"
                  << "    Desc     : " << description << "\n"
                  << "    Priority : " << priorityToString(priority) << "\n"
                  << "    Status   : " << statusToString(status) << "\n"
                  << "    Due      : " << dueDate << "\n"
                  << "    Assignee : "
                  << (assignee ? assignee->getUsername() : "(none)") << "\n";
    }

    void printHistory() const {
        if (history.empty()) {
            std::cout << "    (no status changes)\n";
            return;
        }
        for (const auto& h : history) {
            std::cout << "    " << statusToString(h.oldStatus)
                      << " -> " << statusToString(h.newStatus)
                      << "  by " << h.changedBy << "\n";
        }
    }
};
