#include "Report.h"
using namespace std;
#include "Project.h"
#include <iostream>
#include <iomanip>

Report Report::generate(const Project& project) {
    Report r;
    r.projectTitle  = project.getTitle();
    r.totalTasks = 0;
    r.todoCnt = 0;
    r.inProgressCnt = 0;
    r.doneCnt = 0;
    r.totalMembers = static_cast<int>(project.getMembers().size());

    for (const auto& t : project.getTasks()) {
        r.totalTasks++;
        switch (t->getStatus()) {
            case Status::TODO: r.todoCnt++;
            break;
            case Status::IN_PROGRESS: r.inProgressCnt++; 
            break;
            case Status::DONE: r.doneCnt++; 
            break;
        }
    }
    return r;
}

void Report::print() const {
    double pct = totalTasks > 0
        ? (100.0 * doneCnt / totalTasks)
        : 0.0;

    cout << "\n========== REPORT: " << projectTitle << " ==========\n"
            << "  Members       : " << totalMembers  << "\n"
            << "  Total tasks   : " << totalTasks    << "\n"
            << "  TODO          : " << todoCnt       << "\n"
            << "  IN_PROGRESS   : " << inProgressCnt << "\n"
            << "  DONE          : " << doneCnt       << "\n"
            << "  Completion    : " << std::fixed << std::setprecision(1)
            << pct << "%\n"
            << "=============================================\n";
}
