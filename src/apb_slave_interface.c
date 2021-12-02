#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <arpa/inet.h>

unsigned int PWDATA = 0; // write bus
unsigned int PRDATA = 0; // read bus

typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;


#define SERVER_BACKLOG 1


int make_server_socket(int port) {
    int server_socket, addr_size;
	SA_IN server_addr;

	/*
	 * create socket
	 */

	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	//initialize address struct

	int serverport = port;	
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(serverport);

	bind(server_socket, (SA*) &server_addr, sizeof(server_addr));
	listen(server_socket, SERVER_BACKLOG);

    return server_socket;

}

void handle_signal(unsigned short pclock, unsigned short presetn, unsigned short pprot, unsigned short pselx, unsigned short penable, unsigned short pwrite) {
   

}

void write_no_wait_states() {

}

void idle_phase(){

}

void setup_phase() {

}

void access_phase() {

}

void main_loop_phase() {


}



void get_pwdata(char* data_buffer, char* pwdata) {

    int i;
    char result[33];
    memset(result, 0, 32);
    memset(pwdata, 0, 32);
    for (i = 32; i < 63; ++i) {

        result[i-32] = data_buffer[i];

    }
    
    result[31] = data_buffer[63];

    result[32] = '\0';

    printf("RESULT PWDATA: %s\n", result);

    memcpy(pwdata, result, 32);
}

void get_paddr(char* data_buffer, char* paddr) {

    int i;
    char result[33];
    memset(result, 0, 32);
    memset(paddr, 0, 32);
    for (i = 0; i < 31; ++i) {

        result[i] = data_buffer[i];

    }
    
    result[31] = data_buffer[31];
    result[32] = '\0';


    printf("RESULT PADDR: %s\n", result);
    
    memcpy(paddr, result, 32);


}


void start_phase() {


		/*
		 * Accept client
		 */

		int server_socket = make_server_socket(30123);
        int client_socket, client_addr;

        int addr_size = sizeof(SA_IN);
		printf("Waiting for connections...\n");
		fflush(stdout);
		client_socket = accept(server_socket, (SA*) &client_addr, (socklen_t*) &addr_size);

        printf("%s", "Connected!\n");
        fflush(stdout);
        
        // PADDR, PWDATA, PWRITE, PSEL, PENABLE, PREADY
        char first_cycle_buffer[32 + 32 + 1 + 1 + 1 + 1 ];

        int bytes_read = 0;

        int clock_source = 1;

        char pwdata[33], paddr[33];



        do {
            if (clock_source > 0) {
                int bits_read = read(client_socket, first_cycle_buffer, 32 + 32 + 1 + 1 + 1 + 1);

                
                //unsigned int my_signal = atoi(first_cycle_buffer);
                //unsigned int signal = first_cycle_buffer;

                
                char PREADY = (first_cycle_buffer[bits_read - 1]);

                char PENABLE = (first_cycle_buffer[bits_read - 2]);
                char PSEL = (first_cycle_buffer[bits_read - 3]);
                char PWRITE = (first_cycle_buffer[bits_read - 4]);
                
                




                printf("PWDATA: %s\n", pwdata);
                printf("PADDR: %s\n", paddr);

                get_pwdata(first_cycle_buffer, pwdata);
                
                get_paddr(first_cycle_buffer, paddr);

                //unsigned short PADDR = signal % 10;
                


                printf("PREADY %c\n", PREADY);
                printf("PENABLE %c\n", PENABLE);
                printf("PSEL %c\n", PSEL);
                printf("PWRITE %c\n", PWRITE);

                
                printf("PWDATA: %s\n", pwdata);
                printf("PWADDR: %s\n", paddr);

                printf("BUFFER:\n %s\n", first_cycle_buffer);


                fflush(stdout);

                //printf("MY SIGNAL:\n %d\n", my_signal);
            }
            clock_source = (clock_source + 1) % 2;

        } while (bytes_read > 0);


        close(client_socket);
        close(server_socket);

}
