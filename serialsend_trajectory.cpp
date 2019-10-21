#include <stdio.h>
#include <string.h>

//Linux Headers
#include <unistd.h> //unix standard function defs read() write() open
#include <fcntl.h> // File control definitions
#include <errno.h> //Error functions
#include <termios.h> //POSIX Terminal Controls


int open_port(string port_name, int baudrate){

  int ser_port = open(port_name, O_RDWR);


	if(ser_port < 0){ // If open fails
		printf("Error %i from open %s\n", errno, strerror(errno));
	}

  struct termios tty;

  memset(&tty, 0, sizeof tyy);

  if(tcgetattr(ser_port, &tty) != 0){
    printf("Error %i from tcggetattr: %s\n", errno, strerror(errno));
  }

  //Set Serial Comms to arduino defaults
  tty.c_cflag &= ~PARENB; //disable parity bit
  tty.c_cflag &= ~CSTOPB; //one stop bit
  tty.c_cflag |= CS8; //8 bits per byte



	return(ser_port);
}
