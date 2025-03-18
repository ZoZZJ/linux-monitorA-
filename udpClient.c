#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "192.168.179.1"  // 服务器 IP 地址
#define SERVER_PORT 8888              // 服务器端口
#define BUFFER_SIZE 1024              // 缓冲区大小

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // 创建 UDP socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 填充服务器信息
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    float value = 1.0; // 初始值为 1.0

    // 发送数据
    while (1) {
        // 格式化浮点数并发送
        snprintf(buffer, sizeof(buffer), "%.2f", value);
        ssize_t sent_bytes = sendto(sock, buffer, strlen(buffer), 0,
                                     (const struct sockaddr *)&server_addr,
                                     sizeof(server_addr));

        if (sent_bytes < 0) {
            perror("sendto failed");
            close(sock);
            exit(EXIT_FAILURE);
        }
        printf("Sent: %s\n", buffer);

        // 减少值并检查是否需要重置
        value -= 0.1;
        if (value < -999) {
            value = 999.0; // 重置到 1.0
        }

        usleep(1000);
    }

    // 关闭 socket
    close(sock);
    return 0;
}

