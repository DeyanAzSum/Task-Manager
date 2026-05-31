#pragma once
#include <string>

class WorkItem {
protected:
    int id;
    std::string title;
    std::string description;

public:
    WorkItem(int id, const std::string& title, const std::string& description);
    virtual ~WorkItem() = default;

    virtual void printDetails() const = 0;

    int getId() const;
    const std::string& getTitle() const;
    const std::string& getDescription() const;
    void setTitle(const std::string& t);
    void setDescription(const std::string& d);
};
