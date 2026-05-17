#pragma once
#include "Enums.h"
#include <string>
#include <iostream>

class User {
private:
    int id;
    std::string username;
    std::string email;
    Role role;

public:
    User(int id, const std::string& username, const std::string& email, Role role)
        : id(id), username(username), email(email), role(role) {}

    int getId() const { return id; }
    const std::string& getUsername() const { return username; }
    const std::string& getEmail() const { return email; }
    Role getRole() const { return role; }

    void setUsername(const std::string& u) { username = u; }
    void setEmail(const std::string& e) { email = e; }
    void setRole(Role r) { role = r; }

    void print() const {
        std::cout << "  [User #" << id << "] " << username
                  << " <" << email << "> | Role: " << roleToString(role) << "\n";
    }
};
