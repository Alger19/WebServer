#include "Headers.h"

/*------------------------*/
// Definations of Functions
/*------------------------*/
void *echo_func(int *arg);
void error_handling(const char *sc);
/*------------------------*/
// MAIN Entry Function
/*------------------------*/
int main(void)
{
    int serv_sock = -1;           // server socket
    struct sockaddr_in serv_addr; // server address struct
    socklen_t serv_addr_len = sizeof(serv_addr);

    u_short port = 8000; // Default Listen Port number

    // 线程锁

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serv_addr, serv_addr_len);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, serv_addr_len) == -1)
        error_handling("bind error!");
    if (listen(serv_sock, LISTEN_QUEUE) == -1)
        error_handling("listen error!");

    printf("http running on port %d\n", port);
    printf("--------------Waiting For CLient Connection-----------------");
    printf("\n");

    // Main Loop, Client Connection
    int done = 1;
    while (done)
    {
        int clnt_sock = -1;           // client socket
        struct sockaddr_in clnt_addr; // client socket address struct
        socklen_t clnt_addr_len = sizeof(clnt_addr);

        char clnt_ip[64];

        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_len);
        if (clnt_sock == -1)
            error_handling("accept error");
        else
            printf("---New Connection: \n");

        // print client information IP address & port number
        printf("Client IP Address : %s\t port: %d\n",
               inet_ntop(AF_INET, &clnt_addr.sin_addr.s_addr, clnt_ip, sizeof(clnt_ip)),
               ntohs(clnt_addr.sin_port));

        // Create a new thread for a new client
        pthread_t id;
        pthread_create(&id, NULL, echo_func, (int *)clnt_sock);
        pthread_detach(id);
    }

    close(serv_sock); // end of loop
    return 0;
}

/*------------------------*/
// For testing socket setup
/*------------------------*/
void *echo_func(int *arg)
{
    int clnt_sock = (intptr_t)arg;
    char buf[BUF_SIZE];
    int str_len;
    while ((str_len = read(clnt_sock, buf, BUF_SIZE)) != 0)
    {
        // print messages from clients on screen
        buf[str_len] = '\0';
        printf("Message from Client: %s\n", buf);
        write(clnt_sock, buf, str_len);
    }

    close(clnt_sock);
}

/*------------------------*/
// prints an error message to stderr
/*------------------------*/
void error_handling(const char *sc)
{
    perror(sc);
    exit(1);
}