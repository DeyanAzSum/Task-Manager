#include "Task.h"
using namespace std;
#include "User.h"
#include <iostream>
#include <algorithm>

StatusChange::StatusChange(Status o, Status n, const std::string& by)
    : oldStatus(o), newStatus(n), changedBy(by) {}

Task::Task(int id, const string& title, const string& description, Priority priority, const std::string& dueDate)
    : WorkItem(id, title, description), priority(priority), status(Status::TODO), dueDate(dueDate), assignee(nullptr), nextCommentId(1) {}

Priority Task::getPriority() const { return priority; }
Status Task::getStatus() const { return status; }
const std::string& Task::getDueDate()   const { return dueDate; }
User* Task::getAssignee()  const { return assignee; }
const std::vector<StatusChange>&             Task::getHistory()  const { return history; }
const std::vector<std::unique_ptr<Comment>>& Task::getComments() const { return comments; }

void Task::setPriority(Priority p) { priority = p; }
void Task::setDueDate(const std::string& d) { dueDate = d; }
void Task::assign(User* user) { assignee = user; }

void Task::changeStatus(Status newStatus, const std::string& changedBy) {
    history.emplace_back(status, newStatus, changedBy);
    status = newStatus;
}

Comment* Task::addComment(const std::string& content, const std::string& authorName, const std::string& timestamp) {
    comments.push_back(std::make_unique<Comment>(nextCommentId++, content, authorName, timestamp));
    return comments.back().get();
}

bool Task::deleteComment(int commentId) {
    auto it = std::remove_if(comments.begin(), comments.end(), [commentId](const std::unique_ptr<Comment>& c){ return c->getId() == commentId; });
    if (it == comments.end()) return false;
    comments.erase(it, comments.end());
    return true;
}

void Task::printDetails() const {
    std::cout << "  [Task #" << id << "] " << title << "\n"
            << "    Desc     : " << description << "\n"
            << "    Priority : " << priorityToString(priority) << "\n"
            << "    Status   : " << statusToString(status) << "\n"
            << "    Due      : " << dueDate << "\n"
            << "    Assignee : "
            << (assignee ? assignee->getUsername() : "(none)") << "\n"
            << "    Comments : " << comments.size() << "\n";
}

void Task::printHistory() const {
    if (history.empty()) { std::cout << "    (no status changes)\n"; return; }
    for (const auto& h : history)
        std::cout << "    " << statusToString(h.oldStatus)
                << " -> " << statusToString(h.newStatus)
                << "  by " << h.changedBy << "\n";
}

void Task::printComments() const {
    if (comments.empty()) { std::cout << "    (no comments)\n"; return; }
    for (const auto& c : comments) c->print();
}
