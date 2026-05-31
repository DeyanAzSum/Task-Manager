#pragma once
#include <string>

class Comment {
private:
    int id;
    std::string content;
    std::string authorName;
    std::string createdAt;

public:
    Comment(int id, const std::string& content, const std::string& authorName, const std::string& createdAt);

    int getId() const;
    const std::string& getContent() const;
    const std::string& getAuthorName() const;
    const std::string& getCreatedAt() const;

    void setContent(const std::string& c);
    void print() const;
};
