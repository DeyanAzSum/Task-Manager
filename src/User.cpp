#include "User.h"
using namespace std;
#include <iostream>

User::User(int id, const std::string& username, const std::string& email, Role role)
    : id(id), username(username), email(email), role(role) {}

int User::getId() const { return id; }
const std::string& User::getUsername() const { return username; }
const std::string& User::getEmail() const { return email; }
Role User::getRole() const { return role; }

void User::setUsername(const std::string& u) { username = u; }
void User::setEmail(const std::string& e) { email = e; }
void User::setRole(Role r) { role = r; }

void User::print() const {
    std::cout << "[User #" << id << "] " << username << " <" << email << "> | Role: " << roleToString(role) << "\n";
}
