#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
int main() {
struct sockaddr_in {
 short sin_family;
 unsigned short sin_port;
 struct in_addr sin_addr;
 char sin_zero[8];
};
struct in_addr {
 unsigned long s_addr;
};

int s = socket(AF_INET, SOCK_DGRAM, 0); // UDP
if(s == -1) {
    std::cout << "Socket error\n";
    return 1;
}

sockaddr_in * self_addr = new (sockaddr_in);
self_addr->sin_family = AF_INET; // интернет протокол IPv4
self_addr->sin_port = htons(44214);
self_addr->sin_addr.s_addr = inet_addr("127.0.0.1");

sockaddr_in * srv_addr = new (sockaddr_in);
srv_addr->sin_family = AF_INET; // интернет протокол IPv4
srv_addr->sin_port = htons(44214);
srv_addr->sin_addr.s_addr = inet_addr("127.0.0.1");

int rc = connect(s,(const sockaddr*)srv_addr, sizeof(sockaddr_in));
if (rc == -1) {
    std::cout << "Error: failed connect to server.\n";
    return 1;
}
else {
    std::cout << "We are connect to server!\n";
    char connection_msg[50] = "Hello, it's client!";
    send(s, connection_msg, sizeof(connection_msg), 0);
    char daytime[50];
    recv(s, daytime, sizeof(daytime), 0);
    std::cout << "Daytime from server: " << daytime << std::endl;
    std::cout << "Session close!" << std::endl;
    close(s);
    return 0;
}
}
