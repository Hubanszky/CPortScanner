#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>


int charToInt(char c[]){
	int num = atoi(c);
	return num;
}

void port_scanner( char tIP[], char First_Port[], char Last_Port[]){

    for (int i = charToInt(First_Port); i <= charToInt(Last_Port); i++){
        int Connection = socket(AF_INET , SOCK_STREAM , 0);
        struct sockaddr_in sa = { 0 };
        sa.sin_port = htons(i);
        sa.sin_family = AF_INET;
        sa.sin_addr.s_addr = inet_addr(tIP);

        if (Connection < 0){
            perror("\nSocket");
            exit(1);
        }

        int err = connect(Connection , (struct sockaddr*)&sa , sizeof sa);
        //not connected
        if( err < 0 )
        {
            //printf("%s %-5d %s\r" , hostname , i, strerror(errno));
            fflush(stdout);
        }
        //connected
        else
        {
            printf("%-5d open\n",  i);
        }
        close(Connection);
    }
}

int main(char argc, char *argv[]){
    if (argc < 4){
        printf ("Please enter the server IP address"
                " and range of ports to be scanned\n");
        printf ("USAGE: %s IPv4 First_Port Last_Port\n", 
                argv[0]);
        exit(1);
    }
    char tIP[16] = {0};
    strcpy(tIP, argv[1]); // Copy the IPv4 address
    char First_Port[6] = {0};
    strcpy(First_Port, argv[2]); // Copy the start_port
    char Last_Port[6] = {0};
    strcpy(Last_Port, argv[3]); // Copy the end_port

    port_scanner(tIP, First_Port, Last_Port);
    printf("\r");
    return 0;
}