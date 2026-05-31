#include "Enums.h"
using namespace std;

string priorityToString(Priority p) {
    switch (p) {
        case Priority::LOW: return "LOW";
        case Priority::MEDIUM: return "MEDIUM";
        case Priority::HIGH: return "HIGH";
    }
    return "UNKNOWN";
}

string statusToString(Status s) {
    switch (s) {
        case Status::TODO: return "TODO";
        case Status::IN_PROGRESS: return "IN_PROGRESS";
        case Status::DONE: return "DONE";
    }
    return "UNKNOWN";
}

string roleToString(Role r) {
    switch (r) {
        case Role::ADMIN:  return "ADMIN";
        case Role::MEMBER: return "MEMBER";
    }
    return "UNKNOWN";
}

Priority priorityFromInt(int n) {
    if (n == 3) return Priority::HIGH;
    if (n == 2) return Priority::MEDIUM;
    return Priority::LOW;
}

Status statusFromInt(int n) {
    if (n == 2) return Status::IN_PROGRESS;
    if (n == 3) return Status::DONE;
    return Status::TODO;
}
