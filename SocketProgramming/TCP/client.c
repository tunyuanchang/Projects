/*Linux*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	// for bzero()
#include <unistd.h>	// for close()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
	struct sockaddr_in ser_addr;
	int ser_addr_len = sizeof(ser_addr);
	int ser_socket;
	int ser_portnumber;
	char ser_IP[20];
		
	if(argc == 3){
		strcpy(ser_IP, argv[1]);
		ser_portnumber = atoi(argv[2]);
	}

	// Create socket
	ser_socket = socket(PF_INET, SOCK_STREAM, 0);
	if(ser_socket == -1){
		printf("Error creating socket.\n");
		exit(0);
	}

	// Set the server info
	bzero(&ser_addr, ser_addr_len);
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(ser_portnumber);
	ser_addr.sin_addr.s_addr = inet_addr(ser_IP);

	// Connect to server
	if(connect(ser_socket, (struct sockaddr *)&ser_addr, ser_addr_len) == -1){
		printf("Error connecting to server.\n");
		close(ser_socket);
		exit(0);
	}

	int bytes_send, bytes_recv;
	char send_buf[250], recv_buf[250];

	// Communicate
	while(1){
		bytes_recv = recv(ser_socket, recv_buf, sizeof(recv_buf), 0);
		if(bytes_recv < 0) printf("Error recving packet.\n");

		printf("%s\n", recv_buf);

		send_buf[0] = '\0';
		fflush(stdin);  //clear buff
		scanf(" %[^\n]", send_buf);  //input

		if(strlen(send_buf) == 0) continue;

		bytes_send = send(ser_socket, send_buf, sizeof(send_buf), 0);
		if(bytes_send < 0) printf("Error sending packet.\n");

		if(strncmp(send_buf, "quit", 4) == 0) break;
	}
    close(ser_socket);
	printf("\nClose socket.\n");
	return 0;
}