#include <stdio.h>
#include <cstring>
#include <cerrno>
#include <iostream>
#include <fstream>
#include <string>

//Linux Headers
#include <unistd.h> //unix standard function defs read() write() open
#include <fcntl.h> // File control definitions
#include <errno.h> //Error functions
#include <termios.h> //POSIX Terminal Controls

// C library headers
#include <stdio.h>
//#include <string.h>



#define MSG_SIZE 19 //sum of 4 char long angles and delimiters




using namespace std;

// void write2port(int ser_port, string message){
//   unsigned char msg_arr[MSG_SIZE];
//   write(ser_port, message, sizeof(msg_arr));
// }

int main(){

  int arduino_usb = open("/dev/ttyACM0", O_RDWR);

  struct termios tty;
  struct termios tty_old;

  if ( tcgetattr ( arduino_usb, &tty ) != 0 ) {
   std::cout << "Error " << errno << " from tcgetattr: " << std::strerror(errno) << std::endl;
  }

  tty_old = tty;

  cfsetospeed (&tty, (speed_t)B115200);
  cfsetispeed (&tty, (speed_t)B115200);

  tty.c_cflag &= ~PARENB;

  unsigned char msg[MSG_SIZE];
  int settle_time = 4; //implement a send back to confirm stabilization
  int init_time = 5;

  write(arduino_usb, "0512,0512,0512,0512", sizeof(msg));
  sleep(init_time);
  printf("initialized\n");
  write(arduino_usb, "0600,0600,0600,0600", sizeof(msg));
  sleep(settle_time);
  write(arduino_usb, "0800,0800,0800,0800", sizeof(msg));
  sleep(settle_time);
  write(arduino_usb, "0600,0600,0600,0600", sizeof(msg));
  sleep(settle_time);
  write(arduino_usb, "0512,0512,0512,0512", sizeof(msg));
  sleep(settle_time);
  write(arduino_usb, "0512,580,0512,430", sizeof(msg));
  sleep(settle_time);
  write(arduino_usb, "0512,612,0512,412", sizeof(msg));
  sleep(settle_time);
  write(arduino_usb, "0512,412,0512,612", sizeof(msg));
  sleep(settle_time);
  write(arduino_usb, "0512,0512,0512,0512", sizeof(msg));





  // write(arduino_usb, "0512,0512,0512,0512", sizeof(msg));
  // write(arduino_usb, "0512,612,0512,412", sizeof(msg));
  // write(arduino_usb, "0612,0512,0412,0512", sizeof(msg));


  // int n = read(arduino_usb,&string_buff,256);
  // std::cout<<string_buff;



  //}


  // char c = 'a';
  //  while(c != 'q'){
  //    cin >> c;
  //    int n = read(arduino_usb,&string_buff,256);
  //    std::cout<<string_buff;
  //  }

  close(arduino_usb);
  printf("done\n");
  return 0;
}
