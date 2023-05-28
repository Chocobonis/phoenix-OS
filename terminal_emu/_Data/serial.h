#include <fcntl.h>    //
#include <errno.h>    // THESE ARE THE LIBRARIES THAT WILL BE USED
#include <termios.h>  // FOR THE TERMINAL COMMUNICATION WITH SERIAL PORTS
#include <unistd.h>   //

#include "auxiliar.h"

std::string _OUT [28];

class _SERIAL_TERM_ {
    public:
        int _SERIAL_PORT_;
        int _drw_pointer = 0;
        struct termios tty;
        _SERIAL_TERM_(int); // INITIALIZE
        void fire_confg();  // CREATE CONFIG
        void fire_Print(std::string _msg);
        void fire_input(std::string _inp);
};

_SERIAL_TERM_ :: _SERIAL_TERM_(int _s){
    _SERIAL_PORT_ = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
    if(_SERIAL_PORT_ < 0){
        fire_Print("Could not connect ignite monitor to /dev/ttyUSB0");
        printf("Error %i from open: %s\n", errno, strerror(errno));
    }
    if(tcgetattr(_SERIAL_PORT_, &tty) != 0) {
        fire_Print("Serial communication failed on tcgetattr config.");
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    }
    fire_confg();
}

void _SERIAL_TERM_ :: fire_confg(){
  /*
   THIS IS THE TERMIOS BASIC CONFIGURATION
   I'D LIKE TO THANK mbedded.ninja FOR HIS ARTICLE
   TEACHING HOW TO CONFIGURATE THIS, IT WAS LITERALLY PAIN
   AND I COULDN'T FIND A GOOD INFORMATION SOURCE
   https://blog.mbedded.ninja/ <- visit his website
  */
  tty.c_cflag &= ~PARENB;
  tty.c_cflag &= ~CSTOPB; 
  tty.c_cflag &= ~CSIZE; 
  tty.c_cflag |= CS8; 
  tty.c_cflag &= ~CRTSCTS; 
  tty.c_cflag |= CREAD | CLOCAL; 

  tty.c_lflag &= ~ICANON;
  tty.c_lflag &= ~ECHO; 
  tty.c_lflag &= ~ECHOE; 
  tty.c_lflag &= ~ECHONL; 
  tty.c_lflag &= ~ISIG;
  tty.c_iflag &= ~(IXON | IXOFF | IXANY); 
  tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);

  tty.c_oflag &= ~OPOST;
  tty.c_oflag &= ~ONLCR; 

  tty.c_cc[VTIME] = 0;  
  tty.c_cc[VMIN] = 0;

  cfsetispeed(&tty, B9600);
  cfsetospeed(&tty, B9600);
  if (tcsetattr(_SERIAL_PORT_, TCSANOW, &tty) != 0) {
    fire_Print("Termios failed to configure basic settings :(");
    printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
  }
}

void _SERIAL_TERM_ :: fire_Print(std::string _msg){
    _OUT[_drw_pointer] =  _msg;
    _drw_pointer++;
    //std::cout<<"draw pointer"<<_drw_pointer<<std::endl;
    if(_drw_pointer >= 28){
        for(int i = 0; i < 28; i++){
            _OUT[i] = "";
        }
        _drw_pointer = 0;
    }
}

void _SERIAL_TERM_ :: fire_input(std::string _inp){
    unsigned char msg[256];                 // INITIALLIZE OUR BUFFER TO SEND THE DATA
    strcpy( (char*) msg, _inp.c_str() ); // COPY OUR COMMAND INTO THE BUFFER
    printf("{INPUT} write bytes. sent message: %s\n", msg);
    write(_SERIAL_PORT_, msg, sizeof(msg)); // WRITE TO THE SERIAL PORT (AS A FILE)
    memset(&msg, '\0', sizeof(msg));        // CLEAN MEMORY
    char _output[1024];                     // INITIALIZE OUTPUT BUFFER
    memset(&_output, '\0', sizeof(_output));// CLEAN OUTPUT BUFFER
    int num_bytes = read(_SERIAL_PORT_, &_output, sizeof(_output));  // READ THE BUFFER OUTPUT
    if (num_bytes < 0) {                                             // IF THERE ARE 0 BYTES IN OUTPUT
      fire_Print("ERROR: could not read output from serial port...");// PRINT ERROR
      printf("Error reading: %s", strerror(errno));                  // LOG ERR MESSAGE
    }
    std::string _out = atos(_output);
    printf("{OUTPUT} Read %i bytes. Received message: %s\n", num_bytes, _output);
    fire_Print(_out);
    //fire_Print(_inp);                       // PRINT OUTPUT
}

_SERIAL_TERM_ *_term = new _SERIAL_TERM_(9600);

std::string _my_input = "";
void FIRE_INPUT_KEYBOARD (unsigned char key, int x, int y){
    if(key != 13){
        _my_input += key;
    }else{
        _term->fire_input(_my_input);
        _my_input = "";
    }
}