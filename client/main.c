#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

//code running in the Raspberry Pi 3.

int main(int argc, char **argv)
{
    struct sockaddr_rc addr = { 0 };
    int s, status;
    ///server's BLUETOOTH mac my laptop.
    char dest[18] = "94:65:9C:F7:E9:86";
    // allocate a socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    printf("socket is created\n");
    // set the connection parameters (who to connect to)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba( dest, &addr.rc_bdaddr );
    // connect to server
    printf("Trying to connect..\n");
    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));
    printf("Connection success\n");
    // send a message
    if( status == 0 ) {
        status = write(s, "hello!", 6);
    	printf("msg sent\n");
    }

    if( status < 0 ) 
	    perror("uh oh");
    close(s);

    return 0;
}
