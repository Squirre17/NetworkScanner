#include "TargetManager.hpp"
#define self (*this)

using std::stringstream;
TargetManager::TargetManager(string &addr_given, string &mask_given){

    u32 ip = 0;
    u32 mask = 0;

    stringstream ss_ip(addr_given + ".");
    stringstream ss_mask(mask_given + ".");

    u32 octet;
    u8 dot;

    // 127.0.0.1. add extra dot for following
    while (ss_ip >> octet >> dot) {
        ip = (ip << 8) | octet;
    }
    while (ss_mask >> octet >> dot) {
        mask = (mask << 8) | octet;
    }

    u32 network = ip & mask;
    u32 broadcast = network | ~mask;

    // traverse all possible subnet address
    vector<string> hosts;
    for (u32 i = network + 1; i < broadcast; ++i) {

        stringstream ss_host;

        for (int j = 0; j < 4; ++j) {
            ss_host << ((i >> (8 * (3 - j))) & 0xff);
            if (j != 3) {
                ss_host << ".";
            }
        }
        
        self.subnets.push_back(
            ss_host.str()
        );
        
        self.targets.push_back(
            Target(ss_host.str())
        );
    }
}

mutex result_mutex;
using std::lock_guard;

void TargetManager::scan_all_targets() {
    
    map<string, string> addr2result;
    vector<future<void>> futures;

    for(auto &target : self.targets) {
        auto future = async(std::launch::async, [&target, &addr2result]() {

            string report = target.test_all_ports()
                                  .generate_report();

            lock_guard<mutex> lock(result_mutex);
            addr2result[target.get_ip()] = report;
        });
        futures.push_back(std::move(future));
    }

    for (auto& future : futures) {
        future.wait();
    }

    cout << std::setw(25) << std::left << "Host Name"       
         << std::setw(15) << std::left << "IP Address" 
         << std::setw(10) << std::left << "Opened Port"       
         << endl;

    for(auto &subnet : self.subnets) {
        cout << addr2result[subnet];
    }


}