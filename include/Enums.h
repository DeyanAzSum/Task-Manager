#pragma once
#include <string>

enum class Priority { LOW, MEDIUM, HIGH };
enum class Status   { TODO, IN_PROGRESS, DONE };
enum class Role     { ADMIN, MEMBER };

inline std::string priorityToString(Priority p) {
    switch (p) {
        case Priority::LOW:    return "LOW";
        case Priority::MEDIUM: return "MEDIUM";
        case Priority::HIGH:   return "HIGH";
    }
    return "UNKNOWN";
}

inline std::string statusToString(Status s) {
    switch (s) {
        case Status::TODO:        return "TODO";
        case Status::IN_PROGRESS: return "IN_PROGRESS";
        case Status::DONE:        return "DONE";
    }
    return "UNKNOWN";
}

inline std::string roleToString(Role r) {
    switch (r) {
        case Role::ADMIN:  return "ADMIN";
        case Role::MEMBER: return "MEMBER";
    }
    return "UNKNOWN";
}
