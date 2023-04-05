#ifndef __TARGET_MANAGER_H__
#define __TARGET_MANAGER_H__
#include "Common.hpp"
#include "Target.hpp"

// generate all targets
class TargetManager {
    private:
        string addr;
        string mask;
        vector<string> subnets;
        vector<Target> targets;
    public:
        TargetManager(string &addr, string &mask);
        void scan_all_targets();
};


#endif