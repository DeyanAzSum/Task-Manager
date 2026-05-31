#pragma once
#include <string>

class Notification {
private:
    int id;
    std::string message;
    std::string createdAt;
    bool isRead;

public:
    Notification(int id, const std::string& message, const std::string& createdAt);

    int getId() const;
    const std::string& getMessage() const;
    const std::string& getCreatedAt() const;
    bool getIsRead() const;

    void markAsRead();
    void print() const;
};
