#include "Comment.h"
#include <iostream>

using namespace std;

Comment::Comment(int id, const string& content, const string& authorName, const string& createdAt)
    : id(id), content(content), authorName(authorName), createdAt(createdAt) {}

int Comment::getId() const { return id; }
const string& Comment::getContent() const { return content; }
const string& Comment::getAuthorName() const { return authorName; }
const string& Comment::getCreatedAt() const { return createdAt; }

void Comment::setContent(const string& c) { content = c; }

void Comment::print() const {
    cout << "[Comment #" << id << "] " << authorName << " (" << createdAt << "): " << content << "\n";
}
