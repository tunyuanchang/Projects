/*Linux*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	// for bzero()
#include <unistd.h>	// for close()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define max 999
#define min 0

int main(int argc, char *argv[]){
	struct sockaddr_in ser_addr, cli_addr;
	int ser_addr_len = sizeof(ser_addr);
    int cli_addr_len = sizeof(cli_addr);
	int ser_socket, cli_socket;
	int ser_portnumber;

	if(argc == 2){
		ser_portnumber = atoi(argv[1]);
	}

   	ser_socket = socket(PF_INET, SOCK_STREAM, 0);
	if(ser_socket < 0){
        printf("Error creating socket.\n");
		exit(0);
	}

 	bzero(&ser_addr, ser_addr_len);
	ser_addr.sin_family = AF_INET;
  	ser_addr.sin_port = htons(ser_portnumber);
	ser_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind
	if(bind(ser_socket,(struct sockaddr *) &ser_addr, ser_addr_len) == -1){
        printf("Error binding.\n");
		close(ser_socket);
		exit(0);
	}

	// Listen
	if(listen(ser_socket, 3) == -1){
        printf("Error listening.\n");
		close(ser_socket);
		exit(0);
	}

	printf("Waiting...\n");
	if((cli_socket = accept(ser_socket, (struct sockaddr *)&cli_addr, &cli_addr_len)) == -1){
		printf("Accept failed.\n");
		close(ser_socket);
		exit(0);
	}
	printf("Client connect successfully.\n");

    // game
    char *start = "\
--------------------\n\
Game Start\n";
    char *next = "\
Answer Correct!\n\n\
--------------------\n\
Next Round\n\
--------------------\n\n\n";
    char *guess = "\
--------------------\n\
Guess a number:";

    char send_buf[250], recv_buf[250];
    char str[100];

    int left = min, right = max;
    int number, goal_number = rand() % (max - 1) + 1;
    int bytes_recv, bytes_send;

    // Start
    send_buf[0] = '\0';
	strcat(send_buf, start);
	strcat(send_buf, guess);
	bytes_send = send(cli_socket, send_buf, sizeof(send_buf), 0);
	if(bytes_send < 0) printf("Error sending packet.\n");

	// Communicate
  	while(1){
        bytes_recv = recv(cli_socket, recv_buf, sizeof(recv_buf), 0);
		if(bytes_recv < 0) printf("Error receiving packet.\n");

		printf("%s\n", recv_buf);
		if(strncmp(recv_buf, "quit", 4) == 0) break;

        number = atoi(recv_buf);

		if(strlen(recv_buf) != 0){
			if(number != goal_number){
				if(number > left && number < right){
					if(number > goal_number) right = number;
					else left = number;
				}
				send_buf[0] = '\0';
				sprintf(str, "\nLower than %d\nHigher than %d\n", right, left);
				strcat(send_buf, str);
				strcat(send_buf, guess);

				bytes_send = send(cli_socket, send_buf, sizeof(send_buf), 0);
				if(bytes_send < 0) printf("Error sending packet.\n");
			}else if(number == goal_number){
				send_buf[0] = '\0';
				strcat(send_buf, next);
				strcat(send_buf, start);
				strcat(send_buf, guess);

				bytes_send = send(cli_socket, send_buf, sizeof(send_buf), 0);
				if(bytes_send < 0) printf("Error sending packet.\n");

				left = min, right = max;
				goal_number = rand() % (max - 1) + 1;
			}
		}
    }
    close(cli_socket);
	printf("\nClose socket.\n");
    return 0;
}