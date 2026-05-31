#pragma once
#include "Enums.h"
#include <string>

class User {
private:
    int         id;
    std::string username;
    std::string email;
    Role        role;

public:
    User(int id, const std::string& username, const std::string& email, Role role);

    int getId() const;
    const std::string& getUsername() const;
    const std::string& getEmail() const;
    Role getRole() const;

    void setUsername(const std::string& u);
    void setEmail(const std::string& e);
    void setRole(Role r);
    void print() const;
};
