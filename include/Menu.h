#pragma once
#include "TaskManager.h"
#include <string>

int readInt(const std::string& prompt);
std::string readLine(const std::string& prompt);
Priority readPriority();
Status readStatus();

void menuUsers();
void menuTasks(Project* proj, User* currentUser);
void menuProjects(User* currentUser);
void menuNotifications(User* currentUser);
void menuSearch(User* currentUser);
