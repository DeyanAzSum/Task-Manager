#include "WorkItem.h"
using namespace std;

WorkItem::WorkItem(int id, const std::string& title, const std::string& description)
    : id(id), title(title), description(description) {}

int WorkItem::getId() const { return id; }
const std::string& WorkItem::getTitle() const { return title; }
const std::string& WorkItem::getDescription() const { return description; }
void WorkItem::setTitle(const std::string& t) { title = t; }
void WorkItem::setDescription(const std::string& d) { description = d; }
