#pragma once
#include "WorkItem.h"
#include "Enums.h"
#include "Comment.h"
#include <string>
#include <vector>
#include <memory>

class User;

struct StatusChange {
    Status oldStatus;
    Status newStatus;
    std::string changedBy;
    StatusChange(Status o, Status n, const std::string& by);
};

class Task : public WorkItem {
private:
    Priority priority;
    Status status;
    std::string dueDate;
    User* assignee;
    std::vector<StatusChange> history;
    std::vector<std::unique_ptr<Comment>> comments;
    int nextCommentId;

public:
    Task(int id, const std::string& title, const std::string& description, Priority priority, const std::string& dueDate);

    Priority getPriority()  const;
    Status getStatus() const;
    const std::string& getDueDate() const;
    User* getAssignee() const;
    const std::vector<StatusChange>& getHistory() const;
    const std::vector<std::unique_ptr<Comment>>& getComments() const;

    void setPriority(Priority p);
    void setDueDate(const std::string& d);
    void assign(User* user);

    void changeStatus(Status newStatus, const std::string& changedBy);
    Comment* addComment(const std::string& content, const std::string& authorName, const std::string& timestamp);
    bool deleteComment(int commentId);

    void printDetails() const override;
    void printHistory() const;
    void printComments() const;
};
