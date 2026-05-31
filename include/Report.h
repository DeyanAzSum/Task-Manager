#pragma once
#include <string>

class Project;

class Report {
private:
    std::string projectTitle;
    int totalTasks;
    int todoCnt;
    int inProgressCnt;
    int doneCnt;
    int totalMembers;

public:
    static Report generate(const Project& project);
    void print() const;

private:
    Report() = default;
};
