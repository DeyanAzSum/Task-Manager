#include "Project.h"
using namespace std;
#include <iostream>
#include <algorithm>

Project::Project(int id, const string& title, const string& description)
    : WorkItem(id, title, description), nextTaskId(1) {}

Task* Project::addTask(const std::string& title, const std::string& description, Priority priority, const std::string& dueDate) {
    tasks.push_back(make_unique<Task>(nextTaskId++, title, description, priority, dueDate));
    return tasks.back().get();
}

Task* Project::findTask(int id) const {
    for (const auto& t : tasks)
        if (t->getId() == id) return t.get();
    return nullptr;
}

bool Project::removeTask(int id) {
    auto it = remove_if(tasks.begin(), tasks.end(),
        [id](const unique_ptr<Task>& t){ return t->getId() == id; });
    if (it == tasks.end()) return false;
    tasks.erase(it, tasks.end());
    return true;
}

const vector<unique_ptr<Task>>& Project::getTasks() const { return tasks; }

void Project::addMember(User* user) {
    for (auto* m : members)
        if (m->getId() == user->getId()) return;
    members.push_back(user);
}

bool Project::removeMember(int userId) {
    auto it = remove_if(members.begin(), members.end(),
        [userId](User* u){ return u->getId() == userId; });
    if (it == members.end()) return false;
    members.erase(it, members.end());
    return true;
}

User* Project::findMember(int userId) const {
    for (auto* m : members)
        if (m->getId() == userId) return m;
    return nullptr;
}

const vector<User*>& Project::getMembers() const { return members; }

vector<Task*> Project::searchTasks(const string& keyword) const {
    vector<Task*> result;
    for (const auto& t : tasks) {
        bool inTitle = t->getTitle().find(keyword) != string::npos;
        bool inDesc  = t->getDescription().find(keyword) != string::npos;
        if (inTitle || inDesc) result.push_back(t.get());
    }
    return result;
}

vector<Task*> Project::filterByStatus(Status s) const {
    vector<Task*> result;
    for (const auto& t : tasks)
        if (t->getStatus() == s) result.push_back(t.get());
    return result;
}

vector<Task*> Project::filterByPriority(Priority p) const {
    vector<Task*> result;
    for (const auto& t : tasks)
        if (t->getPriority() == p) result.push_back(t.get());
    return result;
}

vector<Task*> Project::filterByAssignee(int userId) const {
    vector<Task*> result;
    for (const auto& t : tasks)
        if (t->getAssignee() && t->getAssignee()->getId() == userId)
            result.push_back(t.get());
    return result;
}

vector<Notification> Project::checkDeadlines(const string& today, int nextId) const {
    vector<Notification> notifs;
    for (const auto& t : tasks) {
        if (t->getStatus() == Status::DONE) continue;
        const string& due = t->getDueDate();
        if (due.empty()) continue;

        string msg;
        if (due < today)
            msg = "OVERDUE: Task #" + to_string(t->getId())
                + " \"" + t->getTitle() + "\" was due on " + due;
        else if (due == today)
            msg = "DUE TODAY: Task #" + to_string(t->getId())
                + " \"" + t->getTitle() + "\"";

        if (!msg.empty())
            notifs.emplace_back(nextId++, msg, today);
    }
    return notifs;
}

void Project::printDetails() const {
    cout << "[Project #" << id << "] " << title << "\n"
            << "Desc: " << description << "\n"
            << "Tasks: " << tasks.size() << "\n"
            << "Members: " << members.size() << "\n";
}
