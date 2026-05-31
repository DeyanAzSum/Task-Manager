#include "Notification.h"
using namespace std;
#include <iostream>

Notification::Notification(int id, const string& message, const string& createdAt)
    : id(id), message(message), createdAt(createdAt), isRead(false) {}

int Notification::getId() const { return id; }
const string& Notification::getMessage() const { return message; }
const string& Notification::getCreatedAt() const { return createdAt; }
bool Notification::getIsRead() const { return isRead; }

void Notification::markAsRead() { isRead = true; }

void Notification::print() const {
    cout << "  [Notif #" << id << "] "
        << (isRead ? "[READ] " : "[UNREAD] ")
        << "(" << createdAt << ") " << message << "\n";
}
