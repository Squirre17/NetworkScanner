#include "Target.hpp"
#define self (*this)

Target::Target(string ip) {

    self.ip = ip;
    self.bs.reset();
}

// test whether this port is open
bool Target::test_one(i32 port) {

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        cerr << "Failed to create socket" << endl;
        exit(1);
    }

    struct sockaddr_in target_addr;
    std::memset(&target_addr, '\x00', sizeof(target_addr));

    target_addr.sin_family = AF_INET;
    target_addr.sin_port = htons(port);
    inet_pton(AF_INET, self.ip.c_str(), &target_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr*)&target_addr, sizeof(target_addr)) != 0) {
        // std::cerr << "[-] Failed to connect to the server" << std::endl;
        close(sockfd);
        return false;
    }
    else {
        close(sockfd);
        return true;
    }
}
Target& Target::test_all_ports() {

    for(usize p = 0; p < self.MAX_PORT_COUNT; p++) {
        bool is_open = test_one(p);
        if(is_open) {
            self.bs.set(p);
        }
    }

    return self;// TODO: here why not allow return self
}

string Target::generate_report() {

    std::stringstream ss;

    for(usize p = 0; p < self.MAX_PORT_COUNT; p++) {

        if(self.bs[p]) {

            struct in_addr addr;
            inet_pton(AF_INET, self.ip.c_str(), &addr);


            struct hostent* host = gethostbyaddr(&addr, sizeof(addr), AF_INET);
            if(host == nullptr){
                cerr << "err ip is " << self.ip << endl;
                throw std::logic_error("Function not implemented");
            }

            ss << std::setw(25) << std::left << host->h_name
               << std::setw(15) << std::left << self.ip
               << std::setw(10) << std::left << p
               << endl;
        }
    }

    return ss.str();
}

string &Target::get_ip() {
    return self.ip;
}