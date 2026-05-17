#pragma once
#include <string>
#include <iostream>

class WorkItem {
protected:
    int id;
    std::string title;
    std::string description;

public:
    WorkItem(int id, const std::string& title, const std::string& description)
        : id(id), title(title), description(description) {}

    virtual ~WorkItem() = default;

    virtual void printDetails() const = 0;

    int getId() const { return id; }
    const std::string& getTitle() const { return title; }
    const std::string& getDescription() const { return description; }

    void setTitle(const std::string& t) { title = t; }
    void setDescription(const std::string& d) { description = d; }
};
