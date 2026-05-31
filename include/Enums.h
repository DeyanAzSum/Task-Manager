#pragma once
#include <string>

enum class Priority { LOW, MEDIUM, HIGH };
enum class Status { TODO, IN_PROGRESS, DONE };
enum class Role { ADMIN, MEMBER };

std::string priorityToString(Priority p);
std::string statusToString(Status s);
std::string roleToString(Role r);
Priority priorityFromInt(int n);
Status statusFromInt(int n);
