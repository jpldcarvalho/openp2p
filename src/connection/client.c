#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "client.h"

static client cli;

void init_client(char *d_address, int d_port) {
  struct sockaddr_in serv_addr;
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(d_port);
	serv_addr.sin_addr.s_addr = inet_addr(d_address);

	while(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0) {
    printf("Cannot connect to %s:%d\n", d_address, d_port);
    sleep(5);
	}

  cli.dest_address = d_address;
  cli.dest_port = d_port;
  cli.socket = sockfd;
}

void send_msg(char *data, size_t data_size) {
	write(cli.socket, data, data_size);
}

void destroy_client() {
  close(cli.socket);
  cli.dest_address = NULL;
  cli.dest_port = 0;
  cli.socket = 0;
}
