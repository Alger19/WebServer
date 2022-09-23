/*
This file contains the header files required & macros for the http server
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>

#include <pthread.h>

// define personal server name
#define SERVER_STRING "Server : Alger Http Server / Version 1.0.0\r\n"
#define ISspace(x) isspace((int)(x))

// buffer array size
#define BUF_SIZE 1024

// 1 : debug mode, print information
// 0 : normal mode
static int debug = 1;

// define listen queue length
#define LISTEN_QUEUE 128